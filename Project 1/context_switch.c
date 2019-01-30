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

	int main(int argc, char *argv[]){

		int pipefd[2];
		pid_t cpid;
		char buf;

		//setup timer
		long iterations = 10;
		struct timeval start, end;

		//start time
		gettimeofday(&start, NULL);
		
		int i;
		for(i = 0; i < iterations; i++){
			if (argc != 2) {
				fprintf(stderr, "Usage: %s <string>\n", argv[0]);
				exit(EXIT_FAILURE);
			}

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
				close(pipefd[1]);		/* Close unused write end */

				while (read(pipefd[0], &buf, 1) > 0)
					write(STDOUT_FILENO, &buf, 1);

				write(STDOUT_FILENO, "\n", 1);
				close(pipefd[0]);
				//_exit(EXIT_SUCCESS);

			}
			//stop after child to read timer
			else{							/* Parent writes argv[1] to pipe */
				close(pipefd[0]);			/* Close unused read end */
				write(pipefd[1], argv[1], strlen(argv[1]));
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




