// ------------------------------------------
// CMPT 300 Project 2
// process.cpp (file 3 of 9)
//
// Erik Schultz, eriks@sfu.ca, 301034882
// Ian Stewart, iastewar@sfu.ca, 301190316
// Yixuan Li, yixuanl@sfu.ca, 301191905
// ------------------------------------------

#include "process.h"

process::process()
{
    counter = 0;
	numTimeouts = 0;
	probability = 0;
    length = rand()%246+10;
    cpuCluster = 0;
    instructions = new int[length];         // array of random length between 10 and 255

    for (int i=0; i<length; i++)			// each entry of instructions[] will be an IO or CPU
    {
        if (rand()%100 < (10 + probability) && cpuCluster == 0)
        {
            instructions[i] = IO;	        // assign an IO operation
            if(probability < 21)		
            {
                probability++;              // increasing probability to distribute an IO operation
            }
        }
        else
        {
            instructions[i] = CPU;	        // assign a CPU operation
            probability = 0;
            if(rand()%100 < 1) 			    // 1% chance for heavy CPU-bound processes
            {
                cpuCluster = rand()%30 + 1; // randomly determine how many CPU operations will follow
            }
            if(cpuCluster > 0)
            {
                cpuCluster--;
            }
        }
    }
}

process::~process()
{
    delete [] instructions;
}

// public method: process::next()
//      function: increments the program counter and returns the next instruction.
//                if it is at the end of the file, returns END_OF_FILE
int process::next()
{
    if (counter==length) 
	{
        return END_OF_FILE;
    } 
	else 
	{
        return instructions[counter++];
    }
}
