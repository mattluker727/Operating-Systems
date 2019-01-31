
#include <time.h>
#include <sys/time.h>
#include <stdlib.h>
#include <stdio.h>
#include "rdtsc.h"


int main()
{	
	//iterations of loop
	long iterations = 1000000;
	
	//data to be read by read()
	char data[123];
	
	//parameters for gettimeofday()
	struct timeval start, end, mid;
	
	//start time
	gettimeofday(&start, NULL);
	
	//hold read()
	int bytes_read;

	//loop for iterations, call read() each time
	int i;
	for(i = 0; i < iterations; i++){
		bytes_read = read(0, data, 0);
	}
	
	//end time 
	gettimeofday(&end, NULL);
	
	//long endResult = end.tv_usec;
	//long startResult = start.tv_usec;
	//printf("startResult: %ld\n",startResult);
	//printf("endResult: %ld\n",endResult);

	long totalTime = ((end.tv_usec)- (start.tv_usec));
	printf("totalTime: %ld\n",totalTime);
  	
	// (time in seconds / #iterations)
	long result = (totalTime*1000)/(iterations);

	printf("result: %ld\n", result);
	//(:)

	return 0;
}


