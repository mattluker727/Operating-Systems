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

int main(int argc, char **argv)
{
  if (argc < 2)
    {
      printf("USAGE: %s loop-iterations\n", argv[0]);
      return 1;
    }

  int iterations = atoi(argv[1]);

  struct timeval start, end;

  gettimeofday(&start, NULL);
	
  int i;
  for (i = 0; i < iterations; i++)
    {
    }

  gettimeofday(&end, NULL);

  printf("%ld\n", ((end.tv_sec * 1000000 + end.tv_usec)
		  - (start.tv_sec * 1000000 + start.tv_usec)));

  return 0;
}


