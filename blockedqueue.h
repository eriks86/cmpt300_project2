// ------------------------------------------
// CMPT 300 Project 2
// blockedqueue.h (file 6 of 9)
//
// Erik Schultz, eriks@sfu.ca, 301034882
// Ian Stewart, iastewar@sfu.ca, 301190316
// Yixuan Li, yixuanl@sfu.ca, 301191905
// ------------------------------------------

#ifndef BLOCKEDQUEUE_H
#define BLOCKEDQUEUE_H

#include "process.h"
#include <queue>
#include <vector>
#include <pthread.h>

using namespace std;

/*/ class:   blockedqueue
	purpose: this is a single-level queue of processes (see process.h)
	         implemented with a vector and a queue.
/*/

class blockedqueue
{
    public:
        void block(process* a);					// method to block a process
        process * IOFinish(int position);		// unblock a process
		unsigned int size();					// size of the queue
		blockedqueue();
		~blockedqueue();
    private:
		pthread_mutex_t myMutex;
        queue<process*> ready;
        vector<process*> notready;
};

#endif // BLOCKEDQUEUE_H
