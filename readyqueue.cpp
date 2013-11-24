// ------------------------------------------
// CMPT 300 Project 2
// readyqueue.cpp (file 5 of 9)
//
// Erik Schultz, eriks@sfu.ca, 301034882
// Ian Stewart, iastewar@sfu.ca, 301190316
// Yixuan Li, yixuanl@sfu.ca, 301191905
// ------------------------------------------

#include "readyqueue.h"

readyqueue::readyqueue() 
{
	pthread_mutexattr_init(&recursive);
	pthread_mutexattr_settype(&recursive, PTHREAD_MUTEX_RECURSIVE);
	pthread_mutex_init(&myMutex, &recursive);
	// allow the same thread to hold the same mutex more than once in a recursive function call
	// instead of blocking itself
	emptyQ = PTHREAD_COND_INITIALIZER;
}

readyqueue::~readyqueue() 
{
	pthread_mutex_destroy(&myMutex);
	pthread_cond_destroy(&emptyQ);
	pthread_mutexattr_destroy(&recursive);
}

// public method: readyqueue::size() 
//      function: returns the size of the ready queue
unsigned int readyqueue::size() 
{
	pthread_mutex_lock(&myMutex);
	unsigned int temp = queues[0].size() + queues[1].size() + queues[2].size();
	pthread_mutex_unlock(&myMutex);
	return temp;
}

// public method: readyqueue::push(process * p) 
//      function: add a process to queue
void readyqueue::push(process * p) 
{
	//the level of a process in the multi-level feedback queue 
	//corresponds to the number of times it has timed out.
	pthread_mutex_lock(&myMutex);
	int level = (p->numTimeouts>=2 ? 2 : p->numTimeouts);
	queues[level].push(p);
	pthread_mutex_unlock(&myMutex);
	pthread_cond_signal(&emptyQ);
}

// public method: readyqueue::pop() 
//      function: add a process to queue
process * readyqueue::pop() 
{
	pthread_mutex_lock(&myMutex);
	while (empty()) 		        // wait until the queue is not empty to pop()
	{
		pthread_cond_wait(&emptyQ, &myMutex);
	}
	process * temp;
	if (!queues[0].empty())         // pop() a process from the 1st priority level
	{
		temp = queues[0].front();
		queues[0].pop();
	} else if (!queues[1].empty())  // pop() a process from the 2nd priority level
	{
		temp = queues[1].front();
		queues[1].pop();
	} else                          // pop() a process from the 3rd priority level
	{
		temp = queues[2].front();
		queues[2].pop();
	}
	pthread_mutex_unlock(&myMutex);
	return temp;
}

// public method: readyqueue::empty() 
//      function: returns true if nothing is in the queue
bool readyqueue::empty() 
{
	pthread_mutex_lock(&myMutex);
	bool temp = size()==0;
	pthread_mutex_unlock(&myMutex);
	return temp;
}
