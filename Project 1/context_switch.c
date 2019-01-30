// context_swtich.c -  measures the time of a context switch

//forces a context switch using pipes or some other valid method

//sets the machine to use a single processor
//calculates the average time of a context switch using a sufficiently large number of samples


#include <stdlib.h>
#include <time.h>

#define _OPEN_THREADS
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

void *thread(void *arg) {

	/* A simple loop with only puts() would allow a thread to write several
	lines in a row.
	With pthread_yield(), each thread gives another thread a chance before
	it writes its next line */

	while (1) {
		puts((char*) arg);
		pthread_yield(NULL);
	}
}

main() {
  pthread_t t1, t2;

  if (pthread_create(&t1, NULL, thread, "thread 1") != 0) {
    perror("pthread_create() error");
    exit(1);
  }

  if (pthread_create(&t2, NULL, thread, "thread 2") != 0) {
    perror("pthread_create() error");
    exit(2);
  }

  sleep(1);

  exit(0); /* this will tear all threads down */
}







