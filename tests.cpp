// ------------------------------------------
// CMPT 300 Project 2
// tests.cpp (file 11 of 11)
//
// Erik Schultz, eriks@sfu.ca, 301034882
// Ian Stewart, iastewar@sfu.ca, 301190316
// Yixuan Li, yixuanl@sfu.ca, 301191905
// ------------------------------------------

#include "tests.h"
#include "process.h"
#include "readyqueue.h"
#include "blockedqueue.h"
#include "tests.h"
#include <iostream>
#include <stdlib.h>

void testReadyQueue(){
	// test the readyqueue to see if it works.
	process * p = new process();
	process * p2 = new process();
	p2->numTimeouts = 1;
	readyqueue r;
	r.push(p2);
	r.push(p);
	cout << (r.front()==p ? "true" : "false") << endl;
	r.pop();
	cout << (r.front()==p2 ? "true" : "false");
	delete p;
	delete p2;
	cin.get();
}