// ------------------------------------------
// CMPT 300 Project 2
// schedulers.cpp (file 9 of 9)
//
// Erik Schultz, eriks@sfu.ca, 301034882
// Ian Stewart, iastewar@sfu.ca, 301190316
// Yixuan Li, yixuanl@sfu.ca, 301191905
// ------------------------------------------

#include "schedulers.h"
#include "process.h"
#include "readyqueue.h"
#include "blockedqueue.h"
#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include <math.h>

readyqueue r;
blockedqueue b;
pthread_t CPUthreads [3];
pthread_t schedulerThreads [3];
pthread_t io;
pthread_mutex_t mutexNumProcesses = PTHREAD_MUTEX_INITIALIZER;
int numProcesses = 0;

// function: longTermScheduler()
//  purpose: creates processes and pushes them to the ready queue
void longTermScheduler() 
{
	while (numProcesses <= TERMINATE_NOW)                                            // only simulate up to TERMINATE_NOW
	{
		if (r.size()>=MAX_MULTIPROGRAM)
		{ 
			// we don't want too many processes in the ready queue
			// the LTS will not schedule more than MAX_MULTIPROGRAM processes in the queue
			// but if stuff migrates there from the blocked queue then it may end up having more.
			pthread_yield();
			usleep(500); 															
			continue;
		}
		process * p = new process();
		r.push(p);
		usleep(rand()/(RAND_MAX/500));                                               // avoid flooding ready queue
	}
}

// function: shortTermInitialize(void * arg)
//  purpose: initializes our simulation CPUs and STSs
void * shortTermInitialize(void * arg) 
{
	for (int i=0; i<3; i++) 
	{
		pthread_create(&CPUthreads[i], NULL, CPURunProcess, (void *)new process());        // run 3 CPU threads
	}
	for (int i=0; i<3; i++)
	{   // We want all the CPURunProcesses to be created before the short term schedulers 
		// so that they each at least have a chance to run
		pthread_create(&schedulerThreads[i], NULL, shortTermScheduler, (void *)&i);  // run 3 STS threads for each CPU
	}
}

// function: shortTermScheduler (void * arg)
//  purpose: continually check whether each thread is done or not
void * shortTermScheduler (void * arg) 
{
	int i = *(int *)arg;
	while (numProcesses <= TERMINATE_NOW) 
	{
		pthread_join(CPUthreads[i], NULL); 											 // try to join the thread
		pthread_create(&CPUthreads[i], NULL, CPURunProcess, (void *)r.pop());        // send a process to a CPU
		pthread_yield();
	}
	return 0;
}

// function: CPURunProcess (void * arg)
//  purpose: simulates a process running on a CPU. iterates through process' instructions[]
void * CPURunProcess (void * arg) 
{
	process * p = (process *)arg;
	pthread_mutex_lock(&mutexNumProcesses);
	numProcesses++; // this is a critical section as discussed in class
	cout << "CPURunProcess has ran: " << numProcesses << " processes" << endl;
	pthread_mutex_unlock(&mutexNumProcesses);
	int counter = 1;
	int next = p->next();
	
	while (next!=process::END_OF_FILE) 
	{
		if (next==process::IO) 
		{ 
			// this simulates a trap to IO. We want to block the process and resume it later
			b.block(p); 
			return 0;
		}
		counter++;
		if (counter==(pow(2.0, (double)(p->numTimeouts))*TIME_QUANTUM)) 
		{	// a process from level 1 gets TIME_QUANTUM instructions, 
			// one from level 2 gets twice that, level three twice that, etc.
			
			// this simulates a timing out of the process. We want to add it back to the ready queue.
			p->numTimeouts++;
			r.push(p);
			return 0;
		}
		next = p->next();
		pthread_yield(); // maybe someone else wants a chance
	}
	// we reach this point in the code if the process has reached the end of its file
	return 0;
}

// function: IODevice (void * arg)
//  purpose: simulates I/O operations unblocking processes from the blocked queue
void * IODevice (void * arg) 
{
	while (numProcesses <= TERMINATE_NOW) 
	{
		while (b.size()==0) 
		{
			usleep(1000);
			pthread_yield();
		}
		r.push(b.IOFinish(rand()%b.size()));
		usleep(rand()%1000); 
	}
	return 0;
}