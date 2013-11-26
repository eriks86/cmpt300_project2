// ------------------------------------------
// CMPT 300 Project 2
// process.h (file 2 of 9)
//
// Erik Schultz, eriks@sfu.ca, 301034882
// Ian Stewart, iastewar@sfu.ca, 301190316
// Yixuan Li, yixuanl@sfu.ca, 301191905
// ------------------------------------------

#ifndef PROCESS_H
#define PROCESS_H

#include <iostream>
#include <stdlib.h>
#include <time.h>

/*/ class:   process
	purpose: simulates a process with an array of instructions, which are either
			 CPU-bound computation or else traps to input/output devices.
/*/

class process
{
    public:
        static const int CPU = 0;			   // defines a CPU-bound operation
        static const int IO = 1;			   // defines an IO-bound operation
        static const int END_OF_FILE = -1;     // defines the end of a process
		int numTimeouts;                       // used for the multi-level ready queue
        int next(void);						   // method to retrieve the next operation
        process();
        virtual ~process();
    protected:
    private:
        int * instructions;					   // used for process creation/randomization
        int counter;                           // ^
        int length;                            // ^
        int probability;					   // ^
        int cpuCluster;						   // ^
};

#endif // PROCESS_H
