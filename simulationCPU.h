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
	// private class implementation TO-DO
public:
	static const int BLOCKED = 1;
	static const int TIMED_OUT = 2;
	static const int DONE = 0;
	static const int TIME_QUANTUM = 16;
	void * runCPU(void * arg);
	simulationCPU();
	virtual ~simulationCPU();
};

#endif