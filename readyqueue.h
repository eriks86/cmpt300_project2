// ------------------------------------------
// CMPT 300 Project 2
// readyqueue.h (file 4 of 9)
//
// Erik Schultz, eriks@sfu.ca, 301034882
// Ian Stewart, iastewar@sfu.ca, 301190316
// Yixuan Li, yixuanl@sfu.ca, 301191905
// ------------------------------------------

#ifndef READYQUEUE_H
#define READYQUEUE_H

#include "process.h"
#include <stdlib.h>
#include <pthread.h>
#include <queue>

/*/ class:   readyqueue
	purpose: this is a multi-level queue of processes (see process.h)
	         implemented as a linked list.
/*/

class readyqueue 
{
private:
	std::queue<process *> queues [3];
	pthread_mutex_t myMutex;
	pthread_mutexattr_t recursive;
	pthread_cond_t emptyQ;
public:
	readyqueue();
	~readyqueue();
	void push(process * p);				// method to add a process to the ready queue
	process * pop(void);			    // method to get a process from the ready queue and delete it
	unsigned int size(void);		    // method to get the current size of the ready queue
	bool empty(void);                   // method to check if the queue is empty
};

#endif // READYQUEUE_H