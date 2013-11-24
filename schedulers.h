// ------------------------------------------
// CMPT 300 Project 2
// schedulers.h (file 10 of 11)
//
// Erik Schultz, eriks@sfu.ca, 301034882
// Ian Stewart, iastewar@sfu.ca, 301190316
// Yixuan Li, yixuanl@sfu.ca, 301191905
// ------------------------------------------

#ifndef LONGTERMSCHEDULER_H
#define LONGTERMSCHEDULER_H

void longTermScheduler ();
void * shortTermScheduler (void * arg);
void * shortTermInitialize (void * arg);
void * CPURunProcess (void * arg);
void * IODevice (void * arg);
const int TIME_QUANTUM = 16;
const int MAX_MULTIPROGRAM = 16;
const int TERMINATE_NOW = 64; 
// the idea is to terminate after some number of processes are run, so that we are not running forever
// the simulation might run more than this number because all the threads don't terminate at once, but that doesn't matter

#endif