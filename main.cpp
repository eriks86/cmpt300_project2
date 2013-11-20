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
#include <iostream>

using namespace std;

int main(){
	process * p = new process();
	int next = p->next();
	while (next != process::END_OF_FILE) {
        cout << next;
		next = p->next();
	}
	cin.get();
	delete p;
	return 0;
}
