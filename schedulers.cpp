// ------------------------------------------
// CMPT 300 Project 2
// schedulers.cpp (file 11 of 11)
//
// Erik Schultz, eriks@sfu.ca, 301034882
// Ian Stewart, iastewar@sfu.ca, 301190316
// Yixuan Li, yixuanl@sfu.ca, 301191905
// ------------------------------------------

#include "process.h"
#include "readyqueue.h"
#include "blockedqueue.h"
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
	cout << "longTermScheduler: line 25\n";// REMOVE: debugging purposes
	while (true) {
		if (r.size()>=MAX_MULTIPROGRAM) { 
			//we don't want too many processes in the ready queue
			//the LTS will not schedule more than MAX_MULTIPROGRAM processes in the queue
			//but if stuff migrates there from the blocked queue then it may end up having more.
			pthread_yield();
			usleep(500); //500 microsecond sleep
			continue;
		}
		process * p = new process();
		r.push(p);
		usleep(rand()/(RAND_MAX/500));
		//sleep for between 0 and 500 microseconds. Not sure if this is enough.
		//so that we don't flood the ready queue
	}
}

// this just gets some stuff rolling.
void * shortTermInitialize(void * arg) {
	for (int i=0; i<3; i++) {
		//cout << "shortTermInitialize: line 46\n"; // REMOVE: debugging purposes // run 3 CPUs
		pthread_create(&CPUthreads[i], NULL, CPURunProcess, (void *)r.pop());
		// create a STS for each CPU
		pthread_create(&schedulerThreads[i], NULL, shortTermScheduler, (void *)&i);
		//cout << "shortTermInitialize: line 50\n"; // REMOVE: debugging purposes
	}
	//cout << "shortTermInitialize: line 52\n"; // REMOVE: debugging purposes
}

// we want to continually check whether each thread is done or not
void * shortTermScheduler (void * arg) {
	//cout << "shortTermScheduler: line 57\n";// REMOVE: debugging purposes
	int i = *(int *)arg;
	//cout << "shortTermScheduler: line 59\n";// REMOVE: debugging purposes
	while (true) {
		//cout << "shortTermScheduler: line 61\n";// REMOVE: debugging purposes
		pthread_join(CPUthreads[i], NULL); //try to join the thread
		cout << "shortTermScheduler: line 63\n";// REMOVE: debugging purposes
		process * readyProcess = r.pop();
		cout << readyProcess;
		pthread_create(&CPUthreads[i], NULL, CPURunProcess, (void *)readyProcess);
		cout << "shortTermScheduler: line 67\n";// REMOVE: debugging purposes
		//when the thread is done, make it again
		pthread_yield();
		//cout << "shortTermScheduler: line 68\n";// REMOVE: debugging purposes
	}
}

//this function simulates the running of a CPU. It goes through the process's instructions.
void * CPURunProcess (void * arg) {
	cout << "CPURunProcess: line 76\n";// REMOVE: debugging purposes
	process p = *(process *)arg; 	   // =============================== IAN: take a look here, my best guess for segfault
	cout << "CPURunProcess: line 78\n";// REMOVE: debugging purposes
	int counter = 0;
	int next = p.next();
	while (next!=process::END_OF_FILE) {
		if (next==process::IO) { 
			//cout << "CPURunProcess: line 76\n";// REMOVE: debugging purposes
			//this simulates a trap to IO. We want to block the process and resume it later
			//b.Block(&p); 
			///////////////TODO FINISH BLOCKED QUEUE LOGIC////////////////////
			return 0;
		}
		counter++;
		if (counter==TIME_QUANTUM) {
			//cout << "CPURunProcess: line 84\n";// REMOVE: debugging purposes
			//this simulates a timing out of the process. We want to add it back to the ready queue.
			p.numTimeouts++;
			r.push(&p);
			return 0;
		}
		next = p.next();
	}
	//we reach this point in the code if the process has reached the end of its file
	//delete &p;
	//gives an error
	//////////TODO FIND OUT IF THIS CAUSES A MEMORY LEAK AND IF SO HOW TO FIX IT///////////
	cout << "CPURunProcess: line 97\n";// REMOVE: debugging purposes
	return 0;
}