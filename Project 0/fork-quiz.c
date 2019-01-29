#include <stdio.h>
main()
{
   	int pid1, pid2, pid3;
   	int counter;
   	pid1 = 10; pid2 = 20; pid3 = 30; counter = 1;
   	pid1 = fork();
   	printf("%d, %d, %d, %d \n", pid1, pid2, pid3, counter);
   	pid2 = fork();
   	printf("%d, %d, %d, %d \n", pid1, pid2, pid3, counter);
   	while (counter < 2){
     		pid3 = fork();
     	printf("%d, %d, %d, %d \n", pid1, pid2, pid3,        counter);
     		counter = counter +1;
}
}



