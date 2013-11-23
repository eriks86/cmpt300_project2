// ------------------------------------------
// CMPT 300 Project 2
// blockedqueue.cpp (file 9 of 11)
//
// Erik Schultz, eriks@sfu.ca, 301034882
// Ian Stewart, iastewar@sfu.ca, 301190316
// Yixuan Li, yixuanl@sfu.ca, 301191905
// ------------------------------------------

#include "blockedqueue.h"
#include <pthread.h>

	blockedqueue::blockedqueue()
	{
		myMutex = PTHREAD_MUTEX_INITIALIZER;
	}
	
	blockedqueue::~blockedqueue() 
	{
		pthread_mutex_destroy(&myMutex);
	}

    //Put blocked process into the vector that contains
    //processes that's waiting for I/O
    void blockedqueue::Block(process* a)
    {
		pthread_mutex_lock(&myMutex);
        notready.push_back(a);
		pthread_mutex_unlock(&myMutex);
    }

    //When a process recieves it's I/O, move it from the vector
    //into the queue of processes that can be unblocked
    void blockedqueue::IOFinish(int position)
    {
		pthread_mutex_lock(&myMutex);
        process* temp = notready[position];
        notready.erase(notready.begin()+position);
        ready.push(temp);
		pthread_mutex_unlock(&myMutex);
    }

    //Take the first process of the queue and unblock it
    process* blockedqueue::Unblock()
    {
		pthread_mutex_lock(&myMutex);
        process* temp = ready.front();
        ready.pop();
		pthread_mutex_unlock(&myMutex);
        return temp;
    }


