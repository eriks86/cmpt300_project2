// ------------------------------------------
// CMPT 300 Project 2
// process.cpp (file 3 of 9)
//
// Erik Schultz, eriks@sfu.ca, 301034882
// Ian Stewart, iastewar@sfu.ca, 301190316
// Yixuan Li, yixuanl@sfu.ca, 301191905
// ------------------------------------------

#include <stdlib.h>
#include <time.h>
#include "Process.h"
process::process()
{
    counter = 0;
	numTimeouts = 0;
	srand(time(0));
    length = rand()%246+10;
    instructions = new int[length]; //array of random length between 10 and 255.

    //The instructions are IO instructions with a 10% probability.
    //The IO instructions are uniformly distributed thoughout the program 
	//(unrealistic, maybe change this later)
    for (int i=0; i<length; i++) {
        if (rand()%100 < 10) {
            instructions[i] = IO;
        }
        else {
            instructions[i] = CPU;
        }
    }
}

process::~process()
{
    delete [] instructions;
}

//increments the program counter and returns the next instruction
//if it is at the end of the file, returns process::END_OF_FILE
int process::next()
{
    if (counter==length) {
        return END_OF_FILE;
    } else {
        return instructions[counter++];
    }
}
