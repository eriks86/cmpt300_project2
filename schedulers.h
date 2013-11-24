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

#endif