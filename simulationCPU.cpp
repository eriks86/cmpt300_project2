// ------------------------------------------
// CMPT 300 Project 2
// simulationCPU.h (file 9 of 9)
//
// Erik Schultz, eriks@sfu.ca, 301034882
// Ian Stewart, iastewar@sfu.ca, 301190316
// Yixuan Li, yixuanl@sfu.ca, 301191905
// ------------------------------------------

#include "simulationCPU.h"
#include "process.h"
#include "schedulers.h"
#include "blockedqueue.h"
#include "readyqueue.h"
#include <iostream>
#include <cstdlib>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

using namespace std;

extern readyqueue r;
extern blockedqueue b;

void * simulationCPU::initializeCPUS(void* arg){
	cout << "created a CPU" << endl;
}

static void * simulationCPU::runProcess(void * arg) {
	process p = *(process *)arg; 
	int counter = 0;
	int next = p.next();
	while (next!=process::END_OF_FILE) {
		if (next==process::IO) {
			b.Block(&p);
			return 0;
		}
		counter++;
		if (counter==TIME_QUANTUM) {
			p.numTimeouts++;
			r.push(&p);
			return 0;
		}
	}
	delete &p;
	return 0;
}

// default constructor
simulationCPU::simulationCPU()
{
}

// default deconstructor
simulationCPU::~simulationCPU()
{	
}