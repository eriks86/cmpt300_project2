// ------------------------------------------
// CMPT 300 Project 2
// tests.cpp (file 3 of 11)
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
#include "schedulers.h"
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
	cout << (r.pop()==p ? "true" : "false") << endl;
	cout << (r.pop()!=p ? "true" : "false") << endl;
 	cout << (r.pop()==p2 ? "true" : "false") << endl;
	delete p;
	delete p2;
	delete p3;
}

void testLTS() {
	/* commented out until schedulers.cpp implemented
	readyqueue r;
	longTermScheduler((void *)&r);
	while (!r.empty()) 
	{
		process * p = r.pop();
		int instr = p->next();
		while (instr!=process::END_OF_FILE) 
		{
			cout << instr;
			instr = p->next();
		}
		cout << endl;
		delete p;
	}
	*/
}

void testCPU()
{
	/* commented out until schedulers.cpp implemented
	simulationCPU myCPU;
	process * p = new process();
	void * something = myCPU.runProcess((void *)p);
	cout << *(long *)something;
	//delete p; //not sure why this was bad.
	*/
}