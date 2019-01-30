
#include <time.h>
#include <sys/time.h>
#include <stdlib.h>
#include <stdio.h>
#include "rdtsc.h"


int main()
{
	double iterations = 10;
	long a;
	long b;

	struct timeval start, end;

	gettimeofday(&start, NULL);
	a = rdtsc();

	int i;
	for(i = 0; i < iterations; i++){
	}

	gettimeofday(&end, NULL);
	b = rdtsc();


	double totalTime1 = ((b)- (a));
	double totalTime2 = ((end.tv_usec)- (start.tv_usec));
  
	double result1 = totalTime1/iterations;
	double result2 = totalTime2/iterations;
	
    

	printf("result 1: %ld\n", result1);
	printf("result 2: %ld\n", result2);


	return 0;
}


