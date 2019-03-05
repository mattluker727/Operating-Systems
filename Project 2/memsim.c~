	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
	#include <limits.h>
	#include <stdbool.h>
	#include <ctype.h>
	#include <math.h>
	
	//RAM Struct
	struct Page{
		unsigned int page;
		int isDirty;
		int age;
		bool isTeamA;
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
	void ageSort(struct Queue* queue, int itemCount);
	struct Queue *copyQueue(struct Queue *qOne);
	int inMemory(struct Page Mefmory[], unsigned int target, int size);

	//Page Replacement Algorithms
	void fifo();
	void lru();
	void vms();
	
	//Function to check if argv is int
	bool isNumber(char number[]);
	
	//Final output variables
	int eventCount = 0;
	int readCount = 0;
	int writeCount = 0;
	
	//Hold data from argv's
	char *file;
	int nFrames;
	char *algo;
	bool debug = false;
	
	//Main function
	int main(int argc, char *argv[]){
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
				//max input = 25, min = 
				nFrames = atoi(argv[2]);
				//if (nFrames > 25) nFrames = 25;
				//double test = pow(2, nFrames);
				//printf("%lf\n", test);
				//nFrames = (int)test;

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
			//printf("User input: %s %d %s ", file, nFrames, algo);
			//if (debug){
			//	printf("debug \n");
			//}
			//else {
			//	printf("quiet \n");
			//}
		}
		else {
			printf("Incorrect number of args\n");		
		}
		
		//Choose algorihm based on user input
		if (strcmp(algo, "fifo")== 0){
			fifo();
		}
		else if (strcmp(algo, "lru")== 0){
			lru();
		}
		else if (strcmp(algo, "vms")== 0){
			vms();
		}
		
		//Final Output
		printf("total memory frames: %d\n", nFrames);
		printf("events in trace: %d\n", eventCount);
		printf("total disk reads: %d\n", readCount);
		printf("total disk writes: %d\n", writeCount);

		return 0;
	}
	
	//External replacment algorithms
	void fifo(){
		printf("\n");
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
		while ((fscanf(fp, "%x %c\n", &address, &rw) != EOF)){
			//Hold current line from trace
			int currentPage = address/4096;
			int currentRW = rw;
			//Initialize page struct
			current.page = currentPage; 
			current.age = 0;
			//Intitialize diry struct
			if (currentRW == 'R'){
				current.isDirty = 0;
			}
			else {
				current.isDirty = 1;
			}
			
			//CHANGE: %d -> %x
			if (debug) printf("Current Request:%x, %c\n", currentPage, currentRW);

			//Check if page already in Page, flip dirty bit if current line is write
			if (findQueue(queue, currentPage) != -1){
				if(currentRW == 'W'){
					int found = findQueue(queue, currentPage);
					//find place in ram and replace dirty bit
					if (debug) printf("Dirty bit changed to 1\n");
					queue->ram[findQueue(queue, currentPage)].isDirty = 1;
				}
				eventCount++;
				if (debug){
					printf("Queue:\t\t");
					printQueue(queue);
					printf("\n\n");
				}
				continue;
			}
			//If queue is full, dequeue
			if (isFull(queue)){
				//Check if isDirty, increment write if true
				if (debug) printf("Dequeue:\t %x\n", peekPage(queue));
				int getDirty = peekDirty(queue);
				if (getDirty == 1){
					writeCount ++;
					if (debug) printf("writeCount:\t%d\n", writeCount);
				}
				//dequeue front of queue
				dequeue(queue);
			}
		  //Add new address to ram
			//Enqueue struct
			enqueue(queue, current);
			//Print new ram
			if (debug){
				printf("Queue:\t\t");
				printQueue(queue);
				printf("\n\n");
			}
			//Increment readCount
			readCount++;
			//printf("\nreadCount:\t%d", readCount);
			eventCount++;
		}
		
		//Close file
		fclose(fp);		
	}
	
	void lru(){
		printf("\n");
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
		while ((fscanf(fp, "%x %c\n", &address, &rw) != EOF)){
			//Hold current line from trace
			int currentPage = address/4096;
			int currentRW = rw;
			//Initialize page struct
			current.page = currentPage; 
			current.age = 0;
			//Intitialize diry struct
			if (currentRW == 'R'){
				current.isDirty = 0;
			}
			else {
				current.isDirty = 1;
			}
			
			//CHANGE: %d -> %x
			if (debug) printf("Current Request:%x, %c\n", currentPage, currentRW);

			//Check if page already in Page, flip dirty bit if current line is write
			if (findQueue(queue, currentPage) != -1){
					int found = findQueue(queue, currentPage);
					queue->ram[found].age = 0;
					if(currentRW == 'W'){
						//find place in ram and replace dirty bit
						if (debug) printf("Dirty bit changed to 1\n");
						queue->ram[findQueue(queue, currentPage)].isDirty = 1;
					}
					ageSort(queue, queue->size);
					eventCount++;
					if (debug){
						printf("Queue:\t\t");
						printQueue(queue);
						printf("\n\n");
					}
					continue;
			}
			//If queue is full, dequeue
			if (isFull(queue)){
				//Check if isDirty, increment write if true
				if (debug) printf("Dequeue:\t%x\n", peekPage(queue));
				int getDirty = peekDirty(queue);
				if (getDirty == 1){
					writeCount ++;
					if (debug) printf("writeCount:\t%d\n", writeCount);
				}
				//dequeue front of queue
				dequeue(queue);
			}
		  //Add new address to ram
			//Enqueue struct
			enqueue(queue, current);
			//Print new ram
			ageSort(queue, queue->size);
			
			if (debug){
				printf("Queue:\t\t");
				printQueue(queue);
				printf("\n\n");
			}
			//Increment readCount
			readCount++;
			//printf("\nreadCount:\t%d", readCount);
			
			eventCount++;
		}
		//Close file
		fclose(fp);		
	}
	
	void vms(){
		printf("\n");
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
		struct Queue* FIFOA = createQueue(nFrames/2);
		struct Queue* FIFOB = createQueue(nFrames/2);
		struct Queue* Clean = createQueue((nFrames/2)+1); 
		struct Queue* Dirty = createQueue((nFrames/2)+1); 
		struct Queue* Memory = createQueue(nFrames);
		
		struct Page Mefmory[nFrames];
		int val;

		//Initialize all of Memory to 0
		for(val = 0; val < nFrames; val++) Mefmory[val].page = -1;	
		//for(val = 0; val < nFrames; val++) printf("memval: %x\n", Mefmory[val]);
	
		//Fill FIFOA and FIFOB with null pages
		struct Page fill;
		fill.page = -1;
		int f;
		for (f = 0; f < (nFrames/2); f++){
			enqueue(FIFOA, fill);
			enqueue(FIFOB, fill);
		}

		//Temp to track current trace
		struct Page current;
		
		//Reads file addresses and RW's into arrays
		while ((fscanf(fp, "%x %c\n", &address, &rw) != EOF)){
			//Hold current line from trace
			int currentPage = address/4096;
			int currentRW = rw;
			//Initialize page struct
			current.page = currentPage; 
			current.age = 0;
			//Intitialize diry struct
			if (currentRW == 'R'){
				current.isDirty = 0;
			}
			else {
				current.isDirty = 1;
			}
			
			//CHANGE: %d -> %x
			if (debug) printf("Current Request:%x, %c\n", currentPage, currentRW);

			//Check if current page starts with a 3
			int temp3 = currentPage;
			int check3 = currentPage;
			while (temp3){
				check3 = temp3;
				temp3 /= 16;
			}

			//Assign current page to team
			current.isTeamA = false;
			if (check3 == 3) current.isTeamA = true;
			//printf("current.isTeamA: %d\n", current.isTeamA);
			
			if (current.isTeamA){
				//Check if new page already in FIFO(current), flip dirty bit if current line is write
				if (findQueue(FIFOA, current.page) != -1){
					if(currentRW == 'W'){
						int found = findQueue(FIFOA, currentPage);
						//find place in ram and replace dirty bit
						FIFOA->ram[findQueue(FIFOA, currentPage)].isDirty = 1;
					}
					eventCount++;
					if (debug){
						printf("FIFOA:\t\t");
						printQueue(FIFOA);
						printf("\n");
						printf("FIFOB:\t\t");
						printQueue(FIFOB);
						printf("\n");
						printf("Clean:\t\t");
						printQueue(Clean);
						printf("\n");
						printf("Dirty:\t\t");
						printQueue(Dirty);
						printf("\n");
						printf("Memory:\t\t[");
						int kl;
						for(kl = 0; kl < nFrames; kl++)  printf("%x  ", Mefmory[kl].page);
						printf("]\n\n");
					}
					continue;
				}
				//else:
				//page_out = insert new page into the FIFO of the current process;
				struct Page pageOut = dequeue(FIFOA);
				//if (debug) printf("RAM Full!\nDequeue:\t%x\n", pageOut);
				enqueue(FIFOA, current);
				
				if (pageOut.page != -1){
					if (!pageOut.isDirty) enqueue(Clean, pageOut);
					else enqueue(Dirty, pageOut);
				}
				
				//if current page already in memory
				
				if (inMemory(Mefmory, current.page, nFrames) != -1){
					//Remove current.page from Clean/Dirty, whereever it may be
					struct Page hold;
					int count = (nFrames/2)+1;
					if (findQueue(Clean, current.page) != -1){
						while(count){
							hold = dequeue(Clean);
							if (hold.page != current.page){
								enqueue(Clean, hold);
							}
							count = count - 1;
						}
					}
					else{
						while(count){
							hold = dequeue(Dirty);
							if (hold.page != current.page){
								enqueue(Dirty, hold);
							}
							count = count - 1;
						}
					}
				}
				else {
					//If there is room in memory, place it into any free frame
					int p;
					if(inMemory(Mefmory, -1, nFrames) != -1){
						//printf("0 IS IN MEMEORY\n");
						//Mefmory[inMemory(Mefmory, 0)] = current.page;
						for(p = 0; p < nFrames; p++){
							if(Mefmory[p].page == -1){
								//rintf("\n\n Mem is now %x\n\n", current.page);
								Mefmory[p] = current;
								break;
							}
						}
					}

					else {
						struct Page frameToEmpty;
						if (!isEmpty(Clean)){
							frameToEmpty = dequeue(Clean);
						}
						else {
							frameToEmpty = dequeue(Dirty);
							writeCount++;
							//if (debug) printf("Dirty page removed!\nwriteCount:\t%d\n", writeCount);
						}
						//Replace frameToEmpty with current
						for(p = 0; p < nFrames; p++){
							if(Mefmory[p].page == frameToEmpty.page){
								Mefmory[p] = current;
								break;
							}
						}
					}
				}
				
				//Print new ram
				if (debug){
					printf("FIFOA:\t\t");
					printQueue(FIFOA);
					printf("\n");
					printf("FIFOB:\t\t");
					printQueue(FIFOB);
					printf("\n");
					printf("Clean:\t\t");
					printQueue(Clean);
					printf("\n");
					printf("Dirty:\t\t");
					printQueue(Dirty);
					printf("\n");
					printf("Memory:\t\t[");
					int kl;
					for(kl = 0; kl < nFrames; kl++)  printf("%x  ", Mefmory[kl].page);
					printf("]\n\n");
				}
				//Increment readCount
				readCount++;
				//printf("\nreadCount:\t%d", readCount);
				eventCount++;
			}
			//FIFO B
			else {
				//Check if new page already in FIFO(current), flip dirty bit if current line is write
				if (findQueue(FIFOB, current.page) != -1){
					if(currentRW == 'W'){
						int found = findQueue(FIFOB, currentPage);
						//find place in ram and replace dirty bit
						FIFOB->ram[findQueue(FIFOB, currentPage)].isDirty = 1;
					}
					eventCount++;
					if (debug){
						printf("FIFOA:\t\t");
						printQueue(FIFOA);
						printf("\n");
						printf("FIFOB:\t\t");
						printQueue(FIFOB);
						printf("\n");
						printf("Clean:\t\t");
						printQueue(Clean);
						printf("\n");
						printf("Dirty:\t\t");
						printQueue(Dirty);
						printf("\n");
						printf("Memory:\t\t[");
						int kl;
						for(kl = 0; kl < nFrames; kl++)  printf("%x  ", Mefmory[kl].page);
						printf("]\n\n");
					}
					continue;
				}
				//else:
				//page_out = insert new page into the FIFO of the current process;
				struct Page pageOut = dequeue(FIFOB);
				//if (debug) printf("RAM Full!\nDequeue:\t%x\n", pageOut);
				enqueue(FIFOB, current);
				
				if (pageOut.page != -1){
					if (!pageOut.isDirty) enqueue(Clean, pageOut);
					else enqueue(Dirty, pageOut);
				}
				
				//if current page already in memory
				if (inMemory(Mefmory, current.page, nFrames) != -1){
					
					//Remove current.page from Clean/Dirty, whereever it may be
					struct Page hold;
					int count = (nFrames/2)+1;
					if (findQueue(Clean, current.page) != -1){
						while(count){
							hold = dequeue(Clean);
							if (hold.page != current.page){
								enqueue(Clean, hold);
							}
							count = count - 1;
						}
					}
					else{

						while(count){
							hold = dequeue(Dirty);
							if (hold.page != current.page){
								enqueue(Dirty, hold);
							}
							count = count - 1;
						}
					}
				}
				else {
					//If there is room in memory, place it into any free frame
					int p;
					if(inMemory(Mefmory, -1, nFrames) != -1){
						//Mefmory[inMemory(Mefmory, 0)] = current.page;
						for(p = 0; p < nFrames; p++){
							if(Mefmory[p].page == -1){
								Mefmory[p] = current;
								break;
							}
						}
					}
					
					else {
						struct Page frameToEmpty;
						if (!isEmpty(Clean)){
							frameToEmpty = dequeue(Clean);
						}
						else {
							frameToEmpty = dequeue(Dirty);
							writeCount++;
						}
						//Replace frameToEmpty with current
						for(p = 0; p < nFrames; p++){
							if(Mefmory[p].page == frameToEmpty.page){
								Mefmory[p] = current;
								break;
							}
						}
					}
				}
				
				//Print new ram
				if (debug){
					printf("writeCount: \t\t%i\n", writeCount);
					printf("FIFOA:\t\t");
					printQueue(FIFOA);
					printf("\n");
					printf("FIFOB:\t\t");
					printQueue(FIFOB);
					printf("\n");
					printf("Clean:\t\t");
					printQueue(Clean);
					printf("\n");
					printf("Dirty:\t\t");
					printQueue(Dirty);
					printf("\n");
					printf("Memory:\t\t[");
					int kl;
					for(kl = 0; kl < nFrames; kl++)  printf("%x  ", Mefmory[kl].page);
					printf("]\n\n");
				}
				//Increment readCount
				readCount++;
				//printf("\nreadCount:\t%d", readCount);
				eventCount++;
			}

		}
		//Close file
		fclose(fp);				
	}
	
  //Implement functions to support queue

	struct Queue* createQueue(unsigned capacity){ 
		struct Queue* queue = (struct Queue*) malloc(sizeof(struct Queue));
		queue->capacity = capacity; 
		queue->front = queue->size = 0;  
		queue->rear = capacity - 1;
		queue->ram = (struct Page*) malloc(queue->capacity * sizeof(struct Page)); 

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
	
	//CHANGE: %d -> %x
	void printQueue(struct Queue* queue){
		printf("[");
		int q;
		int pFront = queue->front;
		for (q = 0; q < queue->size; q++){
			//needed?
			//if (queue->ram[pFront].page == -1 || queue->ram[pFront].page == 0) continue;
			printf("%x ",queue->ram[pFront].page);
			pFront = (pFront+1)%queue->capacity;
		}
		printf("]");
	}

	int findQueue(struct Queue* queue, int find){
		int q;
		for (q = 0; q < queue->capacity; q++){
			if (queue->ram[q].page == find){
				return q;			
			}
		}
		return -1;
	}
	//returns spot in memory of searched objects or a -1 if object not found
	int inMemory(struct Page Mefmory[], unsigned int target, int size){
		//printf("\n\n");
		while(size > -1){
			//printf("searching for %x against %x\n",target, Mefmory[size].page);
			//printf("Nframes: %i\n", size);
			//printf("Searching MEMORY: %x\n", Mefmory[size].page);
			if(target == Mefmory[size].page){
				return size;
			}
			size = size - 1;
		}		
		return -1;
		
	}
	void ageSort(struct Queue* queue, int itemCount){
		
		int i, j;
		struct Page temp;
		for(i = 0; i < itemCount; i++){
			queue->ram[i].age+= 1;
		}
		if(isFull(queue)){
			//printf("%i\n\n", itemCount);
			for(i = 0; i < itemCount; i++){
				//printf("%x\n", queue[i].page);
				for (j = 0; j < itemCount - 1 - i; ++j )
				{
					 if (queue->ram[j].age < queue->ram[j+1].age)
					 {
						  temp = queue->ram[j+1];
						  queue->ram[j+1] = queue->ram[j];
						  queue->ram[j] = temp;
					}
				}
			}
			for(i = 0; i < itemCount; i++){
				//printf("%x\t%i\t%i\n",queue[i].page, queue[i].age, queue[i].isDirty);
			}

			queue->front = 0;  
			queue->rear = queue->capacity - 1;
			//printf("HERE\n");
		}
	}
	
	struct Queue *copyQueue(struct Queue *qOne){
		struct Queue *qTwo = createQueue(nFrames/2);;
		qTwo->capacity = qOne->capacity; 
		qTwo->front = qOne->front;
		qTwo->size = qOne->size;  
		qTwo->rear = qOne->capacity - 1;
		qTwo->ram = (struct Page*) malloc(qOne->capacity); 
		//printQueue(qTwo);
		return qTwo;
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
