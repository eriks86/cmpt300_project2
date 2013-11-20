// ------------------------------------------
// CMPT 300 Project 2
// process.h (file 2 of 9)
//
// Erik Schultz, eriks@sfu.ca, 301034882
// Ian Stewart, iastewar@sfu.ca, 301190316
// Yixuan Li, yixuanl@sfu.ca, 301191905
// ------------------------------------------

#ifndef READYQUEUE_H
#define READYQUEUE_H
#include "process.h"
#include <stdlib.h>

class readyqueue 
{
private:
	int size;
	struct node {
		process * p;
		node * previous;
		node * next;
	};
	node * queueHead[3];
	node * queueTail[3];
public:
	readyqueue();
	virtual ~readyqueue();
	void push(process * p);
	process * pop(void);
	int getSize(void);
};

#endif