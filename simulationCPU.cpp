// ------------------------------------------
// CMPT 300 Project 2
// simulationCPU.h (file 9 of 9)
//
// Erik Schultz, eriks@sfu.ca, 301034882
// Ian Stewart, iastewar@sfu.ca, 301190316
// Yixuan Li, yixuanl@sfu.ca, 301191905
// ------------------------------------------

#include "simulationCPU.h"
#include <iostream>
#include <cstdlib>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

using namespace std;

void *initializeCPUS(void*){
	cout << "created a CPU" << endl;
}

void * runProcess(void * arg) {
	process p = *(process *)arg;
	int counter = 0;
	int next = p.next();
	while (next!=process::END_OF_FILE) {
		if (next==process::IO) {
			return (void*)&BLOCKED;
		}
		counter++;
		if (counter==TIME_QUANTUM) {
			p.numTimeouts++;
			return (void *)&TIMED_OUT;
		}
	}
	return (void *)&DONE;
}

// default constructor
simulationCPU::simulationCPU()
{
	/*pthread_t simCPU;
    int temp;
	temp = pthread_create(&simCPU, NULL, initializeCPUS, NULL); 
	if(temp){
		cout << "Error:unable to create thread," << temp << endl;
		exit(-1);
	}*/

	cout << "created a CPU" << endl;
}

// default deconstructor
simulationCPU::~simulationCPU()
{	
	// CPU threads run until program is exited
    //pthread_exit(NULL);
}