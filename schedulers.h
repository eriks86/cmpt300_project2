#ifndef LONGTERMSCHEDULER_H
#define LONGTERMSCHEDULER_H

void longTermScheduler ();
void * shortTermScheduler (void * arg);
void * shortTermInitialize (void * arg);
void * CPURunProcess (void * arg);
const int TIME_QUANTUM = 16;
const int MAX_MULTIPROGRAM = 16;

#endif