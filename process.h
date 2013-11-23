// ------------------------------------------
// CMPT 300 Project 2
// process.h (file 4 of 11)
//
// Erik Schultz, eriks@sfu.ca, 301034882
// Ian Stewart, iastewar@sfu.ca, 301190316
// Yixuan Li, yixuanl@sfu.ca, 301191905
// ------------------------------------------

#ifndef PROCESS_H
#define PROCESS_H

// Simulates a process with an array of instructions, which are either
// CPU-bound computation or else traps to input/output devices.

class process
{
    public:
        static const int CPU = 0;
        static const int IO = 1;
        static const int END_OF_FILE = -1;
		int numTimeouts; //used for the multi-level ready queue
        int next(void);
        process();
        virtual ~process();
    protected:
    private:
        int * instructions;
        int counter; //the simulated program counter
        int length; //size of the program
};

#endif // PROCESS_H
