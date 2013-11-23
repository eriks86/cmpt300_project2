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

int main(){
	srand(time(0)); // seed all the rand()s once and only once
	pthread_t initializer;
	pthread_create(&initializer, NULL, shortTermInitialize, NULL);
	longTermScheduler();
	
	return 0;
}
