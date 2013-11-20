// ------------------------------------------
// CMPT 300 Project 2
// process.cpp (file 3 of 9)
//
// Erik Schultz, eriks@sfu.ca, 301034882
// Ian Stewart, iastewar@sfu.ca, 301190316
// Yixuan Li, yixuanl@sfu.ca, 301191905
// ------------------------------------------

#include "readyqueue.h"
#include "process.h"
#include <stdlib.h>

// default constructor
readyqueue::readyqueue()
{
	size = 0;
}

int readyqueue::getSize() {
	return size;
}

//push at the tail
void readyqueue::push(process * p) {
	int level = (p->numTimeouts>=2 ? 2 : p->numTimeouts);
	node * myNode = new node;
	myNode->p = p;
	myNode->next = NULL;
	if (queueHead[level]==NULL) {
		myNode->previous = NULL;
		queueHead[level] = myNode;
		queueTail[level] = myNode;
	} else {
		myNode->previous = queueTail[level];
		queueTail[level]->next = myNode;
		queueTail[level] = myNode;
	}
	size++;
}
