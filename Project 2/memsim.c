	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
	#include <stdbool.h>
	
	//Page Replacement Algorithms
	void lru();
	void fifo();
	void vms();	
	
	//Classes for queue
	int peek();
	bool isEmpty();
	bool isFull();
	int size();
	void enqueue(int data);
	int dequeue();
	
	//Varibles for queue
	#define MAX 6		//size of queue
	
	int queue[MAX];
	int front = 0;
	int rear = -1;
	int itemCount = 0;
	
	//Function to check if argv is int
	bool isNumber(char number[]);
	
	//Main function
	int main(int argc, char *argv[]){
		
		//Hold data from argv's
		char *file;
		char *nFrames;
		int intFrames;		//convert input from char to int
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
				nFrames = argv[2];
				intFrames = atoi(nFrames);
				RSS = intFrames/2;
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
		


		FILE *fp = fopen(file, "r");;
	
		if(fp == NULL){
			printf("error");
			exit(1);
		}
		
		int fileSize = 0;
		unsigned int address[1048576];
		char instr[1048576];
		char adrStr[100];

		int buf = 3;
		
		//Reads file addresses and RW's into arrays
		while (fscanf(fp, "%x %c\n", &address[fileSize], &instr[fileSize]) != EOF){
			//printf("%08x\n", address[fileSize]);
			sprintf(adrStr, "%08x", address[fileSize]);
			//printf("%.5s\n", adrStr);
			
			//printf("%s\n", adrStr + strlen(adrStr) - 3);
			fileSize++;
		}
		fclose(fp);

		
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
		
		//Test queue
		enqueue(1);
		enqueue(2);
		enqueue(3);
		
		int q;
		printf("\nTest queue:\t");
		for (q = 0; q < size(); q++){
			printf("%d ",queue[q]);
		}
		
		printf("\nPeek front:\t%d\n", peek());
		
		int temp = dequeue();
		printf("Dequeue:\t%d\n", temp);
		
		printf("Test queue:\t");
		while(!isEmpty()) {
		  int n = dequeue();           
		  printf("%d ",n);
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
	
	int peek() {
	   return queue[front];
	}
	
	bool isEmpty() {
	   return itemCount == 0;
	}
	
	bool isFull() {
	   return itemCount == MAX;
	}
	
	int size() {
	   return itemCount;
	}  
	
	void enqueue(int data) {

	   if(!isFull()) {
	
		  if(rear == MAX-1) {
		     rear = -1;            
		  }       

		  queue[++rear] = data;
		  itemCount++;
	   }
	}
	
	int dequeue() {
	   int data = queue[front++];
	
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
