// ------------------------------------------
// CMPT 300 Project 2
// readyqueue.h (file 2 of 9)
//
// Erik Schultz, eriks@sfu.ca, 301034882
// Ian Stewart, iastewar@sfu.ca, 301190316
// Yixuan Li, yixuanl@sfu.ca, 301191905
// ------------------------------------------

#ifndef READYQUEUE_H
#define READYQUEUE_H
#include "process.h"
#include <queue>
#include <stdlib.h>
#include <pthread.h>

//This is a multi-level queue of processes implemented as a linked list.
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
	void push(process * p);
	process * pop(void);
	unsigned int size(void);
	bool empty(void);
};

#endif