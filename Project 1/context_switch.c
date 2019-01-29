// context_swtich.c -  measures the time of a context switch

//forces a context switch using pipes or some other valid method

//sets the machine to use a single processor
//calculates the average time of a context switch using a sufficiently large number of samples

#include <iostream>
#include <sys/time.h>     
#include <stdio.h>           
using namespace std;

int main()
{
    struct timeval t1, t2;
    double elapsedTime;

    // start timer
    gettimeofday(&t1, NULL); 

    // do something
    // ...

    // stop timer
    gettimeofday(&t2, NULL);

    // compute and print the elapsed time in millisec
    elapsedTime = (t2.tv_sec - t1.tv_sec) * 1000.0;      // sec to ms
    elapsedTime += (t2.tv_usec - t1.tv_usec) / 1000.0;   // us to ms
    cout << elapsedTime << " ms.\n";
    

    return 0;
}