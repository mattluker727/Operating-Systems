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
	int peekPage(struct memory queue[]);
	int peekDirty(struct memory queue[]);
	bool isEmpty();
	bool isFull(int MAX);
	int size();
	void enqueue(struct memory queue[], struct memory data, int MAX);
	struct memory dequeue(struct memory queue[], int MAX);
	void printQueue(struct memory queue[]);
	bool findQueue(struct memory queue[], int find);
	
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
		unsigned int address;
		char rw;
		
		//Declare main mem queue
		int MAX = ramSize;
		struct memory queue[MAX];
		struct memory temp;
		struct memory current;
		
		//Reads file addresses and RW's into arrays
		while ((fscanf(fp, "%x %c\n", &address, &rw) != EOF) && (fileSize < 10)){
			//Hold current line from trace
			int currentPage = address/4096;
			int currentRW = rw;
			//Initialize current struct
			current.page = currentPage; 
			current.isDirty = 0;
			
			printf("\n\nCURRENT LINE: %d, %c", currentPage, currentRW);
			
			//If queue is full, dequeue
			if (isFull(MAX)){
				//Check if page already in memory, flip dirty bit if current line is write
				if (findQueue(queue, currentPage)){
					printf("\nAlready in queue!");
					if(currentRW == 'W'){
						//find place in queue and replace dirty bit
						//queue[fileSize].isDirty = 1;
					}
					continue;
				}
				else{
					printf("\nQUEUE FULL!");
					//Check if isDirty, increment write if true
					int getDirty = 0;
					getDirty = peekDirty(queue);
					printf("\npeekPage\t%d\n", peekPage(queue));
					printf("getDirty:\t%d\n", peekDirty(queue));
					if (peekDirty(queue) == 1){
						writeCount ++;
					}
					printf("writeCount:\t%d\n", writeCount);
					//dequeue front of queue
					temp = dequeue(queue, MAX);
					printf("Dequeued:\t%d\n", temp);
					printf("Dequeue:\t");
					printQueue(queue);
				}
			}
		  //Add new address to queue
			//Intitialize struct
			if (currentRW == 'R'){
				current.isDirty = 0;
			}
			else {
				current.isDirty = 1;
			}
			//Enqueue struct
			enqueue(queue, current, MAX);
			//Print new queue
			printf("\nQueue:\t\t");
			printQueue(queue);
			//Increment readCount
			readCount++;
			printf("\nreadCount:\t%d", readCount);
			
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
		
		//Final Output
		printf("\n\ntotal memory frames: %d\n", totalFrames);
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
	
	int peekPage(struct memory queue[]) {
		return queue[front].page;
	}

	int peekDirty(struct memory queue[]) {
		return queue[front].isDirty;
	}
	
	bool isFull(int MAX) {
		return itemCount == MAX;
	}
	
	bool isEmpty() {
		return itemCount == 0;
	}
	
	int size() {
		return itemCount;
	}  
	
	void enqueue(struct memory queue[], struct memory data, int MAX) {

		if(!isFull(MAX)) { 
	
			if(rear == MAX-1) {
				rear = -1;            
			}       

			rear = (rear+ 1)%MAX; 
			
			queue[rear] = data;
			itemCount++;
		}
	}
	
	struct memory dequeue(struct memory queue[], int MAX) {
		struct memory data = queue[front++];
	
		if (isEmpty(queue)) 
        	return; 
		
		struct memory item = queue[front]; 
    	front = (front + 1)%MAX;
		
		itemCount--;
		return item;  
	}

	void printQueue(struct memory queue[]){
		int q;
		for (q = front; q < rear+1; q++){
			printf("%d ",queue[q].page);
		}
	}

	bool findQueue(struct memory queue[], int find){
		int q = front;
		
		for (q = front; q < rear+1; q++){
			if (queue[q].page == find){
				return true;			
			}
		}
		return false;
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
