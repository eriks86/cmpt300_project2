// ------------------------------------------
// CMPT 300 Project 2
// main.cpp (file 1 of 9)
//
// Erik Schultz, eriks@sfu.ca, 301034882
// Ian Stewart, iastewar@sfu.ca, 301190316
// Yixuan Li, yixuanl@sfu.ca, 301191905
// ------------------------------------------

#include <iostream>
#include <stdlib.h>
#include "tests.h"

using namespace std;

int main(){
	srand(time(0)); //seed all the rand()s at once.
	//If you call srand anywhere else, it will get seeded more than once resulting in the same numbers.
	//testReadyQueue();
	//cin.get();
	testCPU();
	return 0;
}
