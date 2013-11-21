// ------------------------------------------
// CMPT 300 Project 2
// readyqueue.cpp (file 3 of 9)
//
// Erik Schultz, eriks@sfu.ca, 301034882
// Ian Stewart, iastewar@sfu.ca, 301190316
// Yixuan Li, yixuanl@sfu.ca, 301191905
// ------------------------------------------

#include "readyqueue.h"
#include "process.h"
#include <stdlib.h>
#include <queue>

unsigned int readyqueue::size() {
	return queues[0].size() + queues[1].size() + queues[2].size();
}

//push at the tail
void readyqueue::push(process * p) {
	//the level of a process in the multi-level feedback queue 
	//corresponds to the number of times it has timed out.
	int level = (p->numTimeouts>=2 ? 2 : p->numTimeouts);
	queues[level].push(p);
}

//Deletes the front of the queue. Does not return it.
void readyqueue::pop() {
	if (!queues[0].empty()) {
		queues[0].pop();
	} else if (!queues[1].empty()) {
		queues[1].pop();
	} else {
		queues[2].pop();
	}
}

//Returns the front of the queue. Does not delete it.
process * readyqueue::front() {
	if (!queues[0].empty()) {
		return queues[0].front();
	} else if (!queues[1].empty()) {
		return queues[1].front();
	} else {
		return queues[2].front();
	}
}

//returns true if nothing is in the queue
bool readyqueue::empty() {
	return size()==0;
}
