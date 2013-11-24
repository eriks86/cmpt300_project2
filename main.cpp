// ------------------------------------------
// CMPT 300 Project 2
// main.cpp (file 1 of 11)
//
// Erik Schultz, eriks@sfu.ca, 301034882
// Ian Stewart, iastewar@sfu.ca, 301190316
// Yixuan Li, yixuanl@sfu.ca, 301191905
// ------------------------------------------

#include <iostream>
#include <stdlib.h>
#include <pthread.h>
#include "tests.h"
#include "schedulers.h"

using namespace std;

int main()
{
	srand(time(0)); // seed all the rand()s once and only once
	pthread_t initializer;
	pthread_t io;
	pthread_create(&initializer, NULL, shortTermInitialize, NULL);
	pthread_create(&io, NULL, IODevice, NULL);
	longTermScheduler();
	pthread_join(initializer, NULL);
	pthread_join(io, NULL);
	cout << "End of simulation" << endl;
	return 0;
}
