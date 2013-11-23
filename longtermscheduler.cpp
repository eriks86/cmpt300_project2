#include "process.h"
#include "readyqueue.h"
#include "blockedqueue.h"
#include "tests.h"
#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

readyqueue r;
blockedqueue b;
simulationCPU cpus [3];
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
		pthread_create(&CPUthreads[i], NULL, cpu[i].runProcess, (void *)r.pop());
		pthread_create(&schedulerThreads[i], NULL, shortTermScheduler, (void *)&i);
	}
}

void * shortTermScheduler (void * arg) {
	int i = *(int *)arg;
	pthread_join(&CPUthreads[i], NULL);
	pthread_create(&CPUthreads[i], NULL, cpu[i].runProcess, (void *)r.pop());
}