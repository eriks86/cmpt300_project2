// ------------------------------------------
// CMPT 300 Project 2
// blockedqueue.cpp (file 7 of 9)
//
// Erik Schultz, eriks@sfu.ca, 301034882
// Ian Stewart, iastewar@sfu.ca, 301190316
// Yixuan Li, yixuanl@sfu.ca, 301191905
// ------------------------------------------

#include "blockedqueue.h"

blockedqueue::blockedqueue()
{
	myMutex = PTHREAD_MUTEX_INITIALIZER;
}
	
blockedqueue::~blockedqueue() 
{
	pthread_mutex_destroy(&myMutex);
}

// public method: blockedqueue::size()
//      function: returns the size of the blocked queue	
unsigned int blockedqueue::size()
{
	pthread_mutex_lock(&myMutex);
	unsigned int temp = notready.size();
	pthread_mutex_unlock(&myMutex);
	return temp;
}

// public method: blockedqueue::block(process* a)
//      function: add a blocked process to the vector of blocked processes
void blockedqueue::block(process* a)
{
	pthread_mutex_lock(&myMutex);
    notready.push_back(a);
	pthread_mutex_unlock(&myMutex);
}

// public method: blockedqueue::IOFinish(int position)
//      function: when a process receives I/O, erase it from the vector and return it
process * blockedqueue::IOFinish(int position)
{
	pthread_mutex_lock(&myMutex);
    process* temp = notready[position];
    notready.erase(notready.begin()+position);
	pthread_mutex_unlock(&myMutex);
	return temp;
}