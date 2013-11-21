// ------------------------------------------
// CMPT 300 Project 2
// main.cpp (file 1 of 9)
//
// Erik Schultz, eriks@sfu.ca, 301034882
// Ian Stewart, iastewar@sfu.ca, 301190316
// Yixuan Li, yixuanl@sfu.ca, 301191905
// ------------------------------------------

#include "process.h"
#include "readyqueue.h"
#include "blockedqueue.h"
#include <iostream>
#include <unistd.h>
#include <stdlib.h>

using namespace std;

//adds processes to the ready queue
void * longTermScheduler(void * arg) { //argument to pthread_create
	readyqueue * r = (readyqueue *)arg;
	srand(time(0));
	while (true) {
		if (r->size()>=16) {
			continue;
			//release some sort of mutex here
		}
		process * p = new process();
		r->push(p);
		usleep(rand()/(RAND_MAX/500));
		//sleep for between 0 and 500 microseconds. Not sure if this is enough.
	}
	return 0;
}

int main(){
	//test the readyqueue to see if it works.
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
	return 0;
}
