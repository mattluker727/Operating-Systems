	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
	#include <limits.h>
	#include <stdbool.h>
	#include <ctype.h>

	//RAM Struct
	struct Page{
		unsigned int page;
		int isDirty;
	};
	
	struct Queue { 
		int front, rear, size; 
		unsigned capacity; 
		struct Page *ram; 
	};
	
	//Functions to support queue
	struct Queue* createQueue(unsigned capacity);
	int isFull(struct Queue* queue);
	int isEmpty(struct Queue* queue);
	void enqueue(struct Queue* queue, struct Page data);
	struct Page dequeue(struct Queue* queue);
	struct Page front(struct Queue* queue);
	struct Page rear(struct Queue* queue);
	int peekPage(struct Queue* queue);
	int peekDirty(struct Queue* queue);
	void printQueue(struct Queue* queue);
	int findQueue(struct Queue* queue, int find);

	//Page Replacement Algorithms
	void fifo(char *file, int nFrames, bool debug);
	void lru(char *file, int nFrames, bool debug);
	void vms(char *file, int nFrames, bool debug);
	
	//Function to check if argv is int
	bool isNumber(char number[]);

	//Final output variables
	int totalFrames = 0;
	int eventCount = 0;
	int readCount = 0;
	int writeCount = 0;

	//Main function
	int main(int argc, char *argv[]){
		
		//Hold data from argv's
		char *file;
		int nFrames;
		char *algo;
		bool debug = false;

		//Size of FIFO queue in VMS
		int RSS = 0;
		
		//Load in user input from command line
		if (argc == 5){
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
				nFrames = atoi(argv[2]);
				RSS = nFrames/2;
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
				if (strcmp(argv[4], "debug")== 0){
					debug = true;
				}
			}
			else {
				printf("Invalid mode argument\n");
				exit(0);
			}
			
			//Print user choices
			printf("User input: %s %d %s ", file, nFrames, algo);
			if (debug){
				printf("debug \n");
			}
			else {
				printf("quiet \n");
			}
		}
		else {
			printf("Incorrect number of args\n");		
		}
		
		//Choose algorihm based on user input
		if (strcmp(algo, "fifo")== 0){
			fifo(file, nFrames, debug);
		}
		else if (strcmp(algo, "lru")== 0){
			lru(file, nFrames, debug);
		}
		else if (strcmp(algo, "vms")== 0){
			vms(file, nFrames, debug);
		}
		
		//Final Output
		printf("\n\ntotal memory frames: %d\n", totalFrames);
		printf("events in trace: %d\n", eventCount);
		printf("total disk reads: %d\n", readCount);
		printf("total disk writes: %d\n", writeCount);

		return 0;
	}
	
	//External replacment algorithms
	void fifo(char *file, int nFrames, bool debug){
				//Read in from file
		FILE *fp = fopen(file, "r");;
		if(fp == NULL){
			printf("error");
			exit(1);
		}
		
		//File IO temp variables
		unsigned int address;
		char rw;

		//Declare main mem queue
    struct Queue* queue = createQueue(nFrames); 
		//Temp to track current trace
		struct Page current;
		
		//Reads file addresses and RW's into arrays
		while ((fscanf(fp, "%x %c\n", &address, &rw) != EOF) && (totalFrames < 10)){
			//Hold current line from trace
			int currentPage = address/4096;
			int currentRW = rw;
			//Initialize page struct
			current.page = currentPage; 
			//Intitialize diry struct
			if (currentRW == 'R'){
				current.isDirty = 0;
			}
			else {
				current.isDirty = 1;
			}
			
			printf("\n\nCURRENT LINE:\t%d, %c\n", currentPage, currentRW);

			//Check if page already in Page, flip dirty bit if current line is write
			if (findQueue(queue, currentPage) != 0){
					printf("Already in ram!");
					if(currentRW == 'W'){
						//find place in ram and replace dirty bit
						printf("Dirty bit: %d\n", queue->ram[findQueue(queue, currentPage)].isDirty);
						queue->ram[findQueue(queue, currentPage)].isDirty = 1;
						printf("Dirty bit: %d\n", queue->ram[findQueue(queue, currentPage)].isDirty);
					}
					eventCount++;
					continue;
			}
			//If queue is full, dequeue
			if (isFull(queue)){
				printf("RAM FULL!\n");
				//Check if isDirty, increment write if true
				printf("Dequeue:\t%d\n", peekPage(queue));
				int getDirty = peekDirty(queue);
				if (getDirty == 1){
					printf("Dirty page removed!\n");
					writeCount ++;
					printf("writeCount:\t%d\n", writeCount);
				}
				//dequeue front of queue
				dequeue(queue);
			}
		  //Add new address to ram
			//Enqueue struct
			enqueue(queue, current);
			//Print new ram
			printf("Queue:\t\t");
			printQueue(queue);
			//Increment readCount
			readCount++;
			//printf("\nreadCount:\t%d", readCount);
			
			totalFrames++;
		}
		//Close file
		fclose(fp);		
	}

	void lru(char *file, int nFrames, bool debug){
		printf("Running lru...\n");		
	}
	
	void vms(char *file, int nFrames, bool debug){
		printf("Running vms...\n");			
	}
	
  //Implement functions to support queue

	struct Queue* createQueue(unsigned capacity){ 
		struct Queue* queue = (struct Queue*) malloc(sizeof(struct Queue)); 
		queue->capacity = capacity; 
		queue->front = queue->size = 0;  
		queue->rear = capacity - 1;
		queue->ram = (struct Page*) malloc(queue->capacity); 
		return queue; 
	} 

	int isFull(struct Queue* queue){
		return (queue->size == queue->capacity);
	}
	
	// Queue is empty when size is 0 
	int isEmpty(struct Queue* queue){
		return (queue->size == 0);
	} 
	
	void enqueue(struct Queue* queue, struct Page item) {
		if (isFull(queue)){
			return; 
		}
	
		queue->rear = (queue->rear + 1)%queue->capacity; 
		queue->ram[queue->rear] = item; 
		queue->size = queue->size + 1; 
		//printf("\n%d enqueued to queue\n", item.page); 
	}
	
	struct Page dequeue(struct Queue* queue) {
		
		struct Page item = queue->ram[queue->front]; 
		queue->front = (queue->front + 1)%queue->capacity; 
		queue->size = queue->size - 1; 
		return item;
	}
	
	struct Page front(struct Queue* queue){ 
		return queue->ram[queue->front]; 
	} 
	
	struct Page rear(struct Queue* queue){ 
		return queue->ram[queue->rear]; 
	}
	
	int peekPage(struct Queue* queue) {
		return queue->ram[queue->front].page;
	}

	int peekDirty(struct Queue* queue) {
		return queue->ram[queue->front].isDirty;
	}
	
	void printQueue(struct Queue* queue){
		int q;
		if (queue->front == queue->rear+1){
			for (q = queue->front; q < queue->capacity; q++){
				printf("%d ",queue->ram[q].page);
			}
			
			for (q = 0; q < queue->rear+1; q++){
				printf("%d ",queue->ram[q].page);
			}
		}
		else{
			for (q = queue->front; q < queue->rear+1; q++){
				printf("%d ",queue->ram[q].page);
			}

		}
	}
	
	int findQueue(struct Queue* queue, int find){
		int q;
		for (q = 0; q < queue->capacity; q++){
			if (queue->ram[q].page == find){
				return q;			
			}
		}
		return 0;
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
