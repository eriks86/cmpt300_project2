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
#include <stdlib.h>

//This is a multi-level queue of processes implemented as a linked list.
class readyqueue 
{
private:
	int size; //tells the number of processes waiting
	struct node { //a node in the list, as seen in CMPT 225
		process * p;
		node * previous;
		node * next;
	};
	//There are three sub-queues, each with a head and a tail. 0 is the top one. 
	//When a process times out from the CPU, it goes down a level.
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