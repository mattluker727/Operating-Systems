// - Measures the time of a system call -

// uses either gettimeofday, clock_gettime, rdtsc, or some other valid method to measure time

// invokes a system call correctly
// * E.g. if you decide to measure the time of read(), you will also need to use open() and close().

// calculates the average time of a system call using a sufficiently large number of samples

// * Pay special attention to time units, data types, and removing unnecessary code between measurements.

#include <time.h>
#include <sys/time.h>
#include <stdlib.h>
#include <stdio.h>
#include "rdtsc.h"


int main()
{
	int iterations = 1000000000;
	long a;
	long b;

	struct timeval start, end;
	gettimeofday(&start, NULL);

	a = rdtsc();
	b = rdtsc();
	gettimeofday(&end, NULL);

	int totalTime = ((b)- (a));
  
	int result = iterations/totalTime;
	
    

	printf("%ld\n", result);

	return 0;
}


