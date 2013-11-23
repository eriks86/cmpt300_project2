#include <pthread.h>

void shortTermScheduler () {
	simulationCPU cpus [3];
	pthread_t threads [3];
	
	//initialize the threads
	for (int i=0; i<3 i++)
		pthread_create(&threads[i], NULL, cpu[i].doSomething, (void *)new process());
	}
	
	//do some more stuff
}