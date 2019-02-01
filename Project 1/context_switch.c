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
	
		int status;
		long totalTime = 0;

		//setup timer
		long iterations = 1000000;
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
		
		//Replicate pipe for # iterations
		int i;
		for(i = 0; i < iterations; i++){
			//start timer
			gettimeofday(&start, NULL);
			
			//check affinity
			if (sched_setaffinity(getpid(), sizeof(cpuset), &cpuset) == -1){
				errExit("sched_setaffinity");
			}
			else{
				//Child will read from pipe
				if (cpid == 0) {
					close(pipefd[1]);					//Close write end
					
					read(pipefd[0], buf, sizeof(buf));	//Read from pipe
					//Print from pipe (buffer)
					//printf(buf);
					//printf("\n");

					//end time
					gettimeofday(&end, NULL);
					//update total time
					totalTime += ((end.tv_usec)- (start.tv_usec));
					
					close(pipefd[0]);
				}
				//Parent will write to pipe
				else{
					close(pipefd[0]);								//Close read end
					write(pipefd[1], pipeText, strlen(pipeText));	//Write to pipe
					close(pipefd[1]);								//Close write end
					
					//waitpid(cpid, &status, 1);						//Wait for child
					wait(NULL);										//Wait for child
				}
			}
		}
		
		//Print result of gettimeofday
		if (cpid == 0){
			//Print time in microseconds
			printf("totalTime (micro sec): %ld\n",(totalTime));
			
			//Print time in seconds
			float totalsSecs = (float)totalTime/1000000;
			printf("totalTime (sec): %.6f\n", totalsSecs);
			
			//Print seconds per iteration
			float result = totalsSecs/iterations;
			printf("Seconds per Iteration: %.6f\n", result);
		}
		return 0;
	}




