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

void* testWait(void*){
	cout << "A CPU has been brought online" << endl;
}

// default constructor
simulationCPU::simulationCPU()
{
	pthread_t simCPU;
	pthread_create(&simCPU, NULL, &testWait, NULL);
}

// default deconstructor
simulationCPU::~simulationCPU()
{
    pthread_exit(NULL);
}