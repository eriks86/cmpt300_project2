// ------------------------------------------
// CMPT 300 Project 2
// process.cpp (file 5 of 11)
//
// Erik Schultz, eriks@sfu.ca, 301034882
// Ian Stewart, iastewar@sfu.ca, 301190316
// Yixuan Li, yixuanl@sfu.ca, 301191905
// ------------------------------------------

#include "process.h"
#include <iostream>
#include <stdlib.h>
#include <time.h>

process::process()
{
    counter = 0;
	numTimeouts = 0;
	probability = 0;
    length = rand()%246+10;
    cpuCluster = 0;
    instructions = new int[length]; //array of random length between 10 and 255.

    //The instructions are IO instructions with a 10% probability.
    //The IO instructions are uniformly distributed throughout the program
	//(unrealistic, maybe change this later)
    for (int i=0; i<length; i++)
    {
        if (rand()%100 < (10 + probability) && cpuCluster == 0)
        {
            instructions[i] = IO;
            if(probability < 21)
            {
                probability++; //probability is how much chance added onto the initial
            }
        }
        else
        {
            instructions[i] = CPU;
            probability = 0;
            if(rand()%100 < 1) //1% chance
            {
                cpuCluster = rand()%30 + 1; //randomly determine how many cpu process will follow
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

//increments the program counter and returns the next instruction
//if it is at the end of the file, returns process::END_OF_FILE
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
