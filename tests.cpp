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
#include "longtermscheduler.h"
#include "simulationCPU.h"
#include <iostream>
#include <stdlib.h>

void testReadyQueue(){
	// test the readyqueue to see if it works.
	process * p = new process();
	process * p2 = new process();
	process * p3 = new process();
	int instr = p->next();
	while (instr!=process::END_OF_FILE) {
		cout << instr;
		instr = p->next();
	}
	cout << endl;
	instr = p2->next();
	while (instr!=process::END_OF_FILE) {
		cout << instr;
		instr = p2->next();
	}
	cout << endl;
	cout << (p!=p2 ? "true" : "false") << endl;
	p2->numTimeouts = 1;
	readyqueue r;
	cout << (r.size()==0 ? "true" : "false") << endl;
	cout << (r.empty() ? "true" : "false") << endl;
	r.push(p2);
	cout << (r.size()==1 && !r.empty() ? "true" : "false") << endl;
	r.push(p);
	r.push(p3);
	cout << (r.front()==p ? "true" : "false") << endl;
 	r.pop();
	cout << (r.front()!=p ? "true" : "false") << endl;
	r.pop();
 	cout << (r.front()==p2 ? "true" : "false") << endl;
	r.pop();
	delete p;
	delete p2;
}

void testLTS() {
	readyqueue r;
	longTermScheduler((void *)&r);
	while (!r.empty()) {
		process * p = r.front();
		r.pop();
		int instr = p->next();
		while (instr!=process::END_OF_FILE) {
			cout << instr;
			instr = p->next();
		}
		cout << endl;
		delete p;
	}
}

void testCPU(){
	
}