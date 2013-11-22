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

#define NUM_OF_CPU 3

using namespace std;

void *initializeCPUS(void *thread_id){
	// function called to create 3 CPU threads
	long tid;
	tid = (long)thread_id;
	printf("xxx created a CPU with thread ID: %d", tid);
	//cout << "created a CPU with thread ID: " << tid << endl;
}

// default constructor
simulationCPU::simulationCPU()
{
	pthread_t threads[NUM_OF_CPU];
    int temp;
    int i;
    for(i=0; i < NUM_OF_CPU; i++){
		temp = pthread_create(&threads[i], NULL, initializeCPUS, (void *)i); // TO-DO: fix cast int->pointer warning
		if(temp){
			cout << "Error:unable to create thread," << temp << endl;
			exit(-1);
		}
	}
}

// default deconstructor
simulationCPU::~simulationCPU()
{	
	// CPU threads run until program is exited
    pthread_exit(NULL);
}