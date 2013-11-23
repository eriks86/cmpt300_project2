#include "process.h"
#include "readyqueue.h"
#include "blockedqueue.h"
//#include "tests.h"
#include "schedulers.h"
#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

readyqueue r;
blockedqueue b;
pthread_t CPUthreads [3];
pthread_t schedulerThreads [3];

void longTermScheduler() {
	while (true) {
		if (r.size()>=16) {
			//we don't want too many processes in the ready queue
			pthread_yield();
			usleep(500);
			continue;
		}
		process * p = new process();
		r.push(p);
		usleep(rand()/(RAND_MAX/500));
		//sleep for between 0 and 500 microseconds. Not sure if this is enough.
		//so that we don't flood the ready queue
	}
}

//this just gets some stuff rolling.
void * shortTermInitialize(void * arg) {
	for (int i=0; i<3; i++) {
		pthread_create(&CPUthreads[i], NULL, CPURunProcess, (void *)r.pop());
		//run 3 CPUs
		pthread_create(&schedulerThreads[i], NULL, shortTermScheduler, (void *)&i);
		//create a STS for each CPU
	}
}

//we want to continually check whether each thread is done or not
void * shortTermScheduler (void * arg) {
	int i = *(int *)arg;
	while (true) {
		pthread_join(CPUthreads[i], NULL); //try to join the thread
		pthread_create(&CPUthreads[i], NULL, CPURunProcess, (void *)r.pop());
		//when the thread is done, make it again
		pthread_yield();
	}
}

//this function simulates the running of a CPU. It goes through the process's instructions.
void * CPURunProcess (void * arg) {
	process p = *(process *)arg; 
	int counter = 0;
	int next = p.next();
	while (next!=process::END_OF_FILE) {
		if (next==process::IO) { 
			//this simulates a trap to IO. We want to block the process and resume it later
			b.Block(&p);
			return 0;
		}
		counter++;
		if (counter==TIME_QUANTUM) {
			//this simulates a timing out of the process. We want to add it back to the ready queue.
			p.numTimeouts++;
			r.push(&p);
			return 0;
		}
	}
	//we reach this point in the code if the process has reached the end of its file
	//delete &p;
	//gives an error
	return 0;
}