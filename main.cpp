// ------------------------------------------
// CMPT 300 Project 2
// main.cpp (file 1 of 9)
//
// Erik Schultz, eriks@sfu.ca, 301034882
// Ian Stewart, iastewar@sfu.ca, 301190316
// Yixuan Li, yixuanl@sfu.ca, 301191905
// ------------------------------------------

#include "schedulers.h"
#include <iostream>
#include <stdlib.h>
#include <pthread.h>

using namespace std;

/*/ implementation overview

	*main() is used to run the simulation of processes (see process.h)
	 in our multi-level feedback queue (see readyqueue.h).
		
	*if an I/O operation occurs and then our processes are sent 
	 to a 'blocked' queue (see blockedqueue.h). blocked processes
	 that become unblocked are sent back to the MLFQ.
						 
	*we have used mutexes to fake monitors for IPC situations. 
/*/

int main()
{
	srand(time(0)); 												        // seed all the rand()s once and only once
	
	pthread_t initializer;
	pthread_t io;
	
	pthread_create(&initializer, NULL, shortTermInitialize, NULL);           
	pthread_create(&io, NULL, IODevice, NULL);								
	
	longTermScheduler();
	
	pthread_join(initializer, NULL);										
	pthread_join(io, NULL);													
	
	cout << "END OF SIMULATION" << endl;
	return 0;
}
