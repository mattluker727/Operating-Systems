// context_swtich.c -  measures the time of a context switch

//forces a context switch using pipes or some other valid method

//sets the machine to use a single processor
//calculates the average time of a context switch using a sufficiently large number of samples
	
	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
	#include <stdbool.h>
	
	bool isNumber(char number[]);
	void lru();
	void fifo();
	void vms();	
	bool isNumber(char number[]);
	
	int main(int argc, char *argv[]){

		char *file;
		char *nframes;
		char *algo;
		char *mode;
		
		//Load in user input from command line
		if (argc = 4){
			//printf("%s\n", argv[1]);
			
			//Check that file is a valid file
			if (strcmp(argv[1], "bzip.trace")== 0 || strcmp(argv[1], "gcc.trace")== 0 
					|| strcmp(argv[1], "sixpack.trace")== 0 	|| strcmp(argv[1], "swim.trace")== 0){
				file = argv[1];
			}
			else {
				printf("Invalid file name\n");		
				exit(0);
			}
			
			//Check that nrames is an int
			if (isNumber(argv[2])) {
				nframes = argv[2];
			}
			else {
				printf("Invalid number of frames\n");
				exit(0);
			}
			
			//Check choice of replacement algorithm
			if (strcmp(argv[3], "lru")== 0 || strcmp(argv[3], "fifo")== 0 || strcmp(argv[3], "vms")== 0){
				algo = argv[3];
			}
			else {
				printf("Invalid algorithm choce\n");		
				exit(0);
			}
			
			//Check choice of mode
			if (strcmp(argv[4], "debug")== 0 || strcmp(argv[4], "quiet")== 0){
				mode = argv[4];
			}
			else {
				printf("Invalid mode argument\n");
				exit(0);
			}

			mode = argv[4];
			
			printf("%s %s %s %s\n", file, nframes, algo, mode);

		}
		else {
			printf("Incorrect number of args\n");		
		}	
		
		//Load input from given
		//char addr[9];
		//char rw;
		//FILE *fp;
		
		//fp = fopen (file, "w+");
		//fscanf(file, "%s %c", addr, &rw);
		
		//printf("%s", addr);
		
		//Choose algorihm based on user input
		if (algo = "lru"){
			lru();		
		}
		else if (algo = "fifo"){
			fifo();
		}	
		else if (algo = "vms"){
			vms();		
		}

		return 0;
	}
	
	//External replacment algorithms
	void lru(){
		printf("Running lru...\n");		
	}
	
	void fifo(){
		printf("Running fifo...\n");		
	}
	
	void vms(){
		printf("Running vms...\n");			
	}	
	
	//Function to check if argv is int
	bool isNumber(char number[]){
		int i = 0;

		//checking for negative numbers
		if (number[0] == '-')
		    i = 1;
		for (; number[i] != 0; i++)
		{
		    //if (number[i] > '9' || number[i] < '0')
		    if (!isdigit(number[i]))
		        return false;
		}
		return true;
	}
