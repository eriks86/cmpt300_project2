#include "process.h"
#include "readyqueue.h"
#include "blockedqueue.h"
#include "tests.h"
#include <iostream>
#include <unistd.h>
#include <stdlib.h>

void * longTermScheduler(void * arg) { //argument to pthread_create
	readyqueue * r = (readyqueue *)arg;
	while (true) {
		if (r->size()>=16) {
			//continue;
			break;
			//release some sort of mutex here
		}
		process * p = new process();
		r->push(p);
		usleep(rand()/(RAND_MAX/500));
		//sleep for between 0 and 500 microseconds. Not sure if this is enough.
		//so that we don't flood the ready queue
	}
	return 0;
}