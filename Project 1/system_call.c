
#include <time.h>
#include <sys/time.h>
#include <stdlib.h>
#include <stdio.h>
#include "rdtsc.h"


int main()
{
	//iterations of loop
	float iterations = 1000000;

	//data to be read by read()
	char data[1];

	//parameters for gettimeofday()
	struct timeval start, end;

	//start time
	gettimeofday(&start, NULL);

	//hold read()
	int bytes_read;

	//loop for iterations, call read() each time
	int i;
	for(i = 0; i < iterations; i++){
		bytes_read = read(0, data, 0);
		//printf("Iteration\n");
	}

	//end time 
	gettimeofday(&end, NULL);

	//float endResult = end.tv_usec;
	//float startResult = start.tv_usec;
	//printf("startResult: %.5f\n",startResult);
	//printf("endResult: %.5f\n",endResult);

	long totalTime = (end.tv_usec-start.tv_usec);
	float totalSec = (float)totalTime/1000000;
	//printf("totalTime: %.5f\n",totalTime);
	printf("totalTime: (sec) %.9f\n", totalSec);
	// (time in seconds / #iterations)
	float result = totalSec /(iterations);

	printf("Seconds per Iteration: %.9f\n", result);


	return 0;
}



