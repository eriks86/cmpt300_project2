// ------------------------------------------
// CMPT 300 Project 2
// schedulers.h (file 8 of 9)
//
// Erik Schultz, eriks@sfu.ca, 301034882
// Ian Stewart, iastewar@sfu.ca, 301190316
// Yixuan Li, yixuanl@sfu.ca, 301191905
// ------------------------------------------

#ifndef SCHEDULERS_H
#define SCHEDULERS_H

/*/ files:    schedulers.h, schedulers.cpp
	purpose:  encapsulate our scheduler implementation into a seperate file.
	function: create processes in our MLFQ, simulate running a process on a CPU,
	          simulate I/O blocking, simulate a process becoming unblocked and 
			  returning to the MLFQ.
/*/

void longTermScheduler ();                  // creates processes to be run and pushes the to the ready queue
void * shortTermInitialize (void * arg);    // initializes CPUs and STSs
void * shortTermScheduler (void * arg);     // continually check if threads are done or not
void * CPURunProcess (void * arg);			// simulates running a process from the ready queue
void * IODevice (void * arg);			    // simulates unblocking processes in the blocked queue
const int TIME_QUANTUM = 64;
const int MAX_MULTIPROGRAM = 16;
const int TERMINATE_NOW = 64;               // arbitrary number of processes to be run in our simulation so
                                            // it doesn't run indefinitely. the actual number of processes may be
											// greater than this number since all threads don't terminate at once.

#endif // SCHEDULERS_H