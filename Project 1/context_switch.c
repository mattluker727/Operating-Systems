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
		char buf[15];
		long totalTime = 0;
		//string to be printed
		char pipeText[] = "test";
		
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

				//while (read(pipefd[0], &buf, 1) > 0)
				//	write(STDOUT_FILENO, &buf, 1);
				read(pipefd[0], &buf, sizeof(buf));
				printf(buf + "\n");

				//end time
				gettimeofday(&end, NULL);
				totalTime += ((end.tv_usec)- (start.tv_usec));

				close(pipefd[0]);

				write(STDOUT_FILENO, "\n", 1);
				
				printf("test0");
				exit(0);
				//_exit(EXIT_SUCCESS);
			}
			else{							/* Parent writes pipeText to pipe */
				printf("P: %d\n",sched_getcpu());
				close(pipefd[0]);			/* Close unused read end */
				write(pipefd[1], pipeText, sizeof(pipeText));
				close(pipefd[1]);			/* Reader will see EOF */

				printf("test1");
				wait(NULL);					/* Wait for child */
				printf("test2");
				//exit(EXIT_SUCCESS);
				//exit(0);
			}
			printf("test3");
		}
		printf("test4");
		
		printf(start.tv_usec + "start \n");
		printf(end.tv_usec + "end \n");
		printf("totalTime: %ld\n",totalTime);

		// (time in seconds / #iterations)
		long result = (totalTime)/(iterations);

		printf("result: %ld\n", result);

		return 0;
	}




