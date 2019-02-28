	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
	#include <stdbool.h>
	#include <ctype.h>

	//RAM Struct
	struct memory{
		unsigned int page;
		int isDirty;
	};
	
	//Varibles for queue
	int front = 0;
	int rear = -1;
	int itemCount = 0;

	//Page Replacement Algorithms
	void lru();
	void fifo();
	void vms();	
	
	//Classes for queue
	int peek(struct memory queue[]);
	bool isEmpty();
	bool isFull(int MAX);
	int size();
	void enqueue(struct memory queue[], struct memory data, int MAX);
	struct memory dequeue(struct memory queue[], int MAX);
	
	//Function to check if argv is int
	bool isNumber(char number[]);
	
	//Main function
	int main(int argc, char *argv[]){
		
		//Hold data from argv's
		char *file;
		char *nFrames;
		int ramSize;		//convert input from char to int
		char *algo;
		char *mode;
		
		//Size of FIFO queue in VMS
		int RSS = 0;

		//Final output variables
		int totalFrames = 0;
		int eventCount = 0;
		int readCount = 0;
		int writeCount = 0;
		
		//Load in user input from command line
		if (argc == 5){
			printf("%s\n", argv[1]);
			
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
				nFrames = argv[2];
				ramSize = atoi(nFrames);
				RSS = ramSize/2;
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
			
			printf("User input: %s %s %s %s\n", file, nFrames, algo, mode);

		}
		else {
			printf("Incorrect number of args\n");		
		}

		//Read in from file
		FILE *fp = fopen(file, "r");;
	
		if(fp == NULL){
			printf("error");
			exit(1);
		}
		
		//File IO variables
		int fileSize = 0;
		unsigned int address[1048576];
		char rw[1048576];

		//Declare main mem queue
		int MAX = ramSize;
		struct memory queue[MAX];
		
		//Reads file addresses and RW's into arrays
		while ((fscanf(fp, "%x %c\n", &address[fileSize], &rw[fileSize]) != EOF) && (fileSize < MAX)){
			//printf("%s\n", algo);
			//printf("base address: %08x\n", address[fileSize]);
			
			queue[fileSize].page = address[fileSize]/4096;
			queue[fileSize].isDirty = 0;
			//printf("ram: %x\n", queue[fileSize].page);
			//printf("%c\n", rw[fileSize]);

			fileSize++;
		}
		fclose(fp);
		
		
		//Choose algorihm based on user input
		if (algo == "lru"){
			lru();		
		}
		else if (algo == "fifo"){
			fifo();
		}	
		else if (algo == "vms"){
			vms();		
		}
		
		//Test queue
		printf("queue.page: %d\n", queue[0].page);
		enqueue(queue, queue[0], MAX);
		enqueue(queue, queue[1], MAX);
		enqueue(queue, queue[2], MAX);
		
		int q;
		printf("\nTest queue:\t");
		for (q = front; q < rear+1; q++){
			printf("%d ",queue[q].page);
		}
		
		printf("\nPeek front:\t%d\n", peek(queue));
		
		struct memory temp = dequeue(queue, MAX);
		printf("Dequeue:\t%d\n", temp);

		printf("Test queue:\t");
		for (q = front; q < rear+1; q++){
			printf("%d ",queue[q].page);
		}
		
		printf("\n");
		
		//Final Output
		printf("\ntotal memory frames: %d\n", totalFrames);
		printf("events in trace: %d\n", eventCount);
		printf("total disk reads: %d\n", readCount);
		printf("total disk writes: %d\n", writeCount);

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
	
  //Implement functions to support
	//enqueue(int)		adds to back of queue
	//dequeue()			removes front of queue
	
	int peek(struct memory queue[]) {
	   return queue[front].page;
	}
	
	bool isEmpty() {
	   return itemCount == 0;
	}
	
	bool isFull(int MAX) {
	   return itemCount == MAX;
	}
	
	int size() {
	   return itemCount;
	}  
	
	void enqueue(struct memory queue[], struct memory data, int MAX) {

	   if(!isFull(MAX)) { 
	
		  if(rear == MAX-1) {
		     rear = -1;            
		  }       

		  queue[++rear] = data;
		  itemCount++;
	   }
	}
	
	struct memory dequeue(struct memory *queue, int MAX) {
	   struct memory data = queue[front++];
	
	   if(front == MAX) {
		  front = 0;
	   }
	
	   itemCount--;
	   return data;  
	}
  //End queue functions
	
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
