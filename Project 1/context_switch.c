// context_swtich.c -  measures the time of a context switch

//forces a context switch using pipes or some other valid method

//sets the machine to use a single processor
//calculates the average time of a context switch using a sufficiently large number of samples

#include <sys/time.h>     
#include <stdio.h>       
#include <stdint.h>
#include <time.h>
#include <unistd.h>  //Header file for sleep(). man 3 sleep for details. 
#include <pthread.h>     

int main(){
	
	printf("test");

	struct timeval start, end;
	
    uint32_t COUNTER;
	pthread_mutex_t LOCK;
	pthread_mutex_t START;
	pthread_cond_t CONDITION;

	void * threads (void * unused) {
		pthread_mutex_lock(&START);
		pthread_mutex_unlock(&START);
		pthread_mutex_lock(&LOCK);
		if (COUNTER > 0) {
			pthread_cond_signal(&CONDITION);
		}
		for (;;) {
			COUNTER++;
			pthread_cond_wait(&CONDITION, &LOCK);
			pthread_cond_signal(&CONDITION);
		}
		pthread_mutex_unlock(&LOCK);
	}

	pthread_mutex_lock(&START);
    COUNTER = 0;

	pthread_t t1;	//new
	pthread_t t2;	//new

    pthread_create(&t1, NULL, threads, NULL);
    pthread_create(&t2, NULL, threads, NULL);
    pthread_detach(t1);
    pthread_detach(t2);

    //myTime = tTimer();
	gettimeofday(&start, NULL);	//new
    pthread_mutex_unlock(&START);
    sleep(1);

    // Lock both simulaneous threads
    pthread_mutex_lock(&LOCK);

    //Normalize the result in second precision
	gettimeofday(&end, NULL);	//new
	long totalTime = ((end.tv_usec)- (start.tv_usec));	//new

	long myTime = totalTime/1000;

	printf("result: %ld\n", myTime);

    //myTime = tTimer() - myTime / 1000;
}








