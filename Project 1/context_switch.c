// context_swtich.c -  measures the time of a context switch

//forces a context switch using pipes or some other valid method

//sets the machine to use a single processor
//calculates the average time of a context switch using a sufficiently large number of samples

	#define _GNU_SOURCE
	#include <sys/types.h>
	#include <sys/wait.h>
	#include <stdio.h>
	#include <stdlib.h>
	#include <unistd.h>
	#include <string.h>
	#include <time.h>
	
    #include <sched.h>
    #include <pthread.h>

	#define errExit(msg)    do { perror(msg); exit(EXIT_FAILURE); \
		                           } while (0)
	
	int main(){
		
		//define # CPU's
		cpu_set_t cpuset;
        int numCPU = 0;
		CPU_ZERO(&cpuset);
		CPU_SET(numCPU, &cpuset);
		//restrict current process to 1 CPU
  		sched_setaffinity(0, sizeof(cpuset), &cpuset);
		
		int pipefd[2];
		pid_t cpid;

		//buffer and string
		char pipeText[] = "test";
		char buf[5];
		
		long totalTime = 0;

		//setup timer
		long iterations = 1;
		struct timeval start, end;

		if (pipe(pipefd) == -1) {
			perror("pipe");
			exit(EXIT_FAILURE);
		}

		cpid = fork();

		if (cpid == -1) {
			perror("fork");
			exit(EXIT_FAILURE);
		}
		
		int i;
		for(i = 0; i < iterations; i++){
			//start timer
			gettimeofday(&start, NULL);

			if (cpid == 0) {			/* Child reads from pipe */
				printf("C: %d\n",sched_getcpu());
				close(pipefd[1]);		/* Close unused write end */

				read(pipefd[0], buf, sizeof(buf));
				printf(buf);
				printf("\n");

				//end time
				gettimeofday(&end, NULL);
				totalTime += ((end.tv_usec)- (start.tv_usec));

				close(pipefd[0]);

				exit(0);
			}
			else{							/* Parent writes pipeText to pipe */
				printf("P: %d\n",sched_getcpu());
				close(pipefd[0]);			/* Close unused read end */
				write(pipefd[1], buf, strlen(pipeText));
				close(pipefd[1]);			/* Reader will see EOF */

				wait(NULL);					/* Wait for child */
				//exit(0);
			}
		}
		
		printf(start.tv_usec + "start \n");
		printf(end.tv_usec + "end \n");
		printf("totalTime: %ld\n",totalTime);

		// (time in seconds / #iterations)
		long result = (totalTime)/(iterations);

		printf("result: %ld\n", result);

		return 0;
	}




