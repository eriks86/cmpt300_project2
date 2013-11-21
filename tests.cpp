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
#include <iostream>
#include <stdlib.h>

void testReadyQueue(){
	// test the readyqueue to see if it works.
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