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

#include "process.h"
#include "readyqueue.h"
#include "blockedqueue.h"
#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include <math.h>

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
const int TIME_QUANTUM = 16;
const int MAX_MULTIPROGRAM = 16;
const int TERMINATE_NOW = 5;            	// arbitrary number of processes to be run in our simulation so
                                            // it doesn't run indefinitely. 
const int CONTEXT_SWITCH = 100;				// microseconds it takes for a context switch

#endif // SCHEDULERS_H