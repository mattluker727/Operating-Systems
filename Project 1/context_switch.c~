// context_swtich.c -  measures the time of a context switch

//forces a context switch using pipes or some other valid method

//sets the machine to use a single processor
//calculates the average time of a context switch using a sufficiently large number of samples

	#include <sys/types.h>
	#include <sys/wait.h>
	#include <stdio.h>
	#include <stdlib.h>
	#include <unistd.h>
	#include <string.h>
    #include <sched.h>
    
	#define _GNU_SOURCE
	#define errExit(msg)    do { perror(msg); exit(EXIT_FAILURE); \
		                           } while (0)

	int main(){
		
		//define # CPU's
		//cpu_set_t set;
        //int numCPU = 0;
		//CPU_ZERO(&set);

		int pipefd[2];
		pid_t cpid;
		char buf;
		//string to be printed
		char* pipeText = "test";
		
		//setup timer
		long iterations = 10;
		struct timeval start, end;

		//start time
		gettimeofday(&start, NULL);
		
		int i;
		for(i = 0; i < iterations; i++){
			if (pipe(pipefd) == -1) {
				perror("pipe");
				exit(EXIT_FAILURE);
			}

			cpid = fork();

			if (cpid == -1) {
				perror("fork");
				exit(EXIT_FAILURE);
			}
		
			if (cpid == 0) {			/* Child reads from pipe */
				//CPU_SET(numCPU, &set);
				
				//if (sched_setaffinity(getpid(), sizeof(set), &set) == -1)
					//errExit("sched_setaffinity");

				close(pipefd[1]);		/* Close unused write end */

				while (read(pipefd[0], &buf, 1) > 0)
					write(STDOUT_FILENO, &buf, 1);

				write(STDOUT_FILENO, "\n", 1);
				close(pipefd[0]);
				//_exit(EXIT_SUCCESS);

			}
			//stop after child to read timer
			else{							/* Parent writes pipeText to pipe */
				//CPU_SET(numCPU, &set);
				//if (sched_setaffinity(getpid(), sizeof(set), &set) == -1)
					//errExit("sched_setaffinity");
				
				close(pipefd[0]);			/* Close unused read end */
				write(pipefd[1], pipeText, strlen(pipeText));
				close(pipefd[1]);			/* Reader will see EOF */
				wait(NULL);					/* Wait for child */
				exit(EXIT_SUCCESS);
			}
		}
		
		//end time 
		gettimeofday(&end, NULL);

		long totalTime = ((end.tv_usec)- (start.tv_usec));
		printf("totalTime: %ld\n",totalTime);

		// (time in seconds / #iterations)
		long result = (totalTime*1000)/(iterations);

		printf("result: %ld\n", result);

		return 0;
	}




