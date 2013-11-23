// ------------------------------------------
// CMPT 300 Project 2
// simulationCPU.h (file 8 of 9)
//
// Erik Schultz, eriks@sfu.ca, 301034882
// Ian Stewart, iastewar@sfu.ca, 301190316
// Yixuan Li, yixuanl@sfu.ca, 301191905
// ------------------------------------------

#ifndef SIMULATIONCPU_H
#define SIMULATIONCPU_H

class simulationCPU 
{
private:
	long b;
	long t;
	long d;
	//wrapper variables for the constants
public:
	static const long BLOCKED = 1;
	static const long TIMED_OUT = 2;
	static const long DONE = 0;
	static const int TIME_QUANTUM = 16;
	void * runProcess(void * arg);
	void * initializeCPUS(void * arg);
	simulationCPU();
	virtual ~simulationCPU();
};

#endif