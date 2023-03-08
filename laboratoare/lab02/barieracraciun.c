#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "pthread_barrier_mac.h"
#define NUM_THREADS 2 //N+E

pthread_barrier_t barrier;
void *f(void *arg)
{
	int thread_id = *(int *)arg;

	if (0 <= thread_id || thread_id < N) {
		printf("1\n");
	}
	pthread_barrier_wait(&barrier);
	if (N < thread_id ) {
		printf("2\n");
	}

	pthread_exit(NULL);
}

int main(int argc, char **argv)
{
	int i, r;
	void *status;
	pthread_t threads[NUM_THREADS];
	int arguments[NUM_THREADS];
	pthread_barrier_init( &barrier, NULL, 2);
	for (i = 0; i < NUM_THREADS; i++) {
		arguments[i] = i;
		r = pthread_create(&threads[i], NULL, f, &arguments[i]);

		if (r) {
			printf("Eroare la crearea thread-ului %d\n", i);
			exit(-1);
		}
	}

	for (i = 0; i < NUM_THREADS; i++) {

		r = pthread_join(threads[i], &status);

		if (r) {
			printf("Eroare la asteptarea thread-ului %d\n", i);
			exit(-1);
		}
	}
	pthread_barrier_destroy(&barrier);
	return 0;
}