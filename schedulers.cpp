// ------------------------------------------
// CMPT 300 Project 2
// schedulers.cpp (file 9 of 9)
//
// Erik Schultz, eriks@sfu.ca, 301034882
// Ian Stewart, iastewar@sfu.ca, 301190316
// Yixuan Li, yixuanl@sfu.ca, 301191905
// ------------------------------------------

#include "schedulers.h"

readyqueue r;
blockedqueue b;
pthread_t CPUthreads [3];
pthread_t schedulerThreads [3];
pthread_t io;
pthread_mutex_t mutexNumProcesses = PTHREAD_MUTEX_INITIALIZER; // don't increment process::numProcesses twice to the same value
pthread_mutex_t output = PTHREAD_MUTEX_INITIALIZER; // only output one thing at a time or it will be garbled
int numCPUProcesses = 0; // number of processes that pass through the CPUs
int numLTSProcesses = 0; // number of processes that pass through the long-term scheduler

// function: longTermScheduler()
//  purpose: creates processes and pushes them to the ready queue
void longTermScheduler() 
{
	while (numLTSProcesses <= TERMINATE_NOW)                                            // only simulate up to TERMINATE_NOW
	{
		if (r.size()>=MAX_MULTIPROGRAM)
		{ 
			// we don't want too many processes in the ready queue
			// the LTS will not schedule more than MAX_MULTIPROGRAM processes in the queue
			// but if stuff migrates there from the blocked queue then it may end up having more.
			pthread_yield(); 															
			continue;
		}
		process * p = new process();
		r.push(p);
		numLTSProcesses++;
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
	while (true) 
	{
		pthread_join(CPUthreads[i], NULL); 											 // try to join the thread
		if (numLTSProcesses <= TERMINATE_NOW || r.size()!=0 || b.size()!=0)
		{
			pthread_create(&CPUthreads[i], NULL, CPURunProcess, (void *)r.pop());        // send a process to a CPU
			pthread_mutex_lock(&output);
			cout << "Scheduled a process on CPU " << i << endl;
			pthread_mutex_unlock(&output);
		}
		else {
			break;
		}
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
	numCPUProcesses++; // this is a critical section as discussed in class
	pthread_mutex_lock(&output);
	cout << "CPURunProcess has ran: " << numCPUProcesses << " times" << endl;
	pthread_mutex_unlock(&output);
	pthread_mutex_unlock(&mutexNumProcesses);
	int counter = 1;
	int next = p->next();
	
	while (next!=process::END_OF_FILE) 
	{
		if (next==process::IO) 
		{ 
			// this simulates a trap to IO. We want to block the process and resume it later
			b.block(p); 
			usleep(CONTEXT_SWITCH); // simulates a context switch
			return 0;
		}
		counter++;
		if (counter==(pow(2.0, (double)(p->numTimeouts))*TIME_QUANTUM)) 
		{	// a process from level 1 gets TIME_QUANTUM instructions, 
			// one from level 2 gets twice that, level three twice that, etc.
			
			// this simulates a timing out of the process. We want to add it back to the ready queue.
			if (p->numTimeouts < 3) 
			{
				p->numTimeouts++;
			}
			r.push(p);
			usleep(CONTEXT_SWITCH);
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
	while (numLTSProcesses <= TERMINATE_NOW || r.size()!=0 || b.size()!=0) 
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