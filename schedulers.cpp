#include "process.h"
#include "readyqueue.h"
#include "blockedqueue.h"
#include "tests.h"
//#include "simulationCPU.h"
#include "schedulers.h"
#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

readyqueue r;
blockedqueue b;
pthread_t CPUthreads [3];
pthread_t schedulerThreads [3];

void longTermScheduler() { //argument to pthread_create
	while (true) {
		if (r.size()>=16) {
			//continue;
			break;
			//release some sort of mutex here
		}
		process * p = new process();
		r.push(p);
		//emptyReadyQ.signal();
		usleep(rand()/(RAND_MAX/500));
		//sleep for between 0 and 500 microseconds. Not sure if this is enough.
		//so that we don't flood the ready queue
	}
}

void * shortTermInitialize(void * arg) {
	for (int i=0; i<3; i++) {
		pthread_create(&CPUthreads[i], NULL, CPURunProcess, (void *)r.pop());
		pthread_create(&schedulerThreads[i], NULL, shortTermScheduler, (void *)&i);
	}
}

void * shortTermScheduler (void * arg) {
	int i = *(int *)arg;
	while (true) {
		pthread_join(CPUthreads[i], NULL);
		pthread_create(&CPUthreads[i], NULL, CPURunProcess, (void *)r.pop());
	}
}

void * CPURunProcess (void * arg) {
	process p = *(process *)arg; 
	int counter = 0;
	int next = p.next();
	while (next!=process::END_OF_FILE) {
		if (next==process::IO) {
			b.Block(&p);
			return 0;
		}
		counter++;
		if (counter==TIME_QUANTUM) {
			p.numTimeouts++;
			r.push(&p);
			return 0;
		}
	}
	//delete &p; //this is when the process has terminated
	return 0;
}