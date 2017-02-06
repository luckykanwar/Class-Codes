#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>

main()
{
    time_t t;
    int largeRandom[500000]; // large no of random numbers
    int smallRandom[500];	// small no of random numbers
    int largeSorted[500000]; // large number of sorted numbers
    int smallSorted[500];	// small no of sorted numbers
    int reverseSorted[500000]; // large number of reverse sorted numbers
    int smallReverseSorted[500]; // small array of reverse sorted numbers

    srand((unsigned) time(&t));


    for(i=0;i<500000;i++)
    	largeRandom[i]=rand()%50;

	for(i=0;i<500;i++)
		smallRandom[i]=rand()%50;

	for(i=0;i<500000;i++)
    	largeSorted[i]=i;

	for(i=0;i<500;i++)
		smallSorted[i]=i;

	for(i=500000;i>0;i--)
    	reverseSorted[i]=i;

	for(i=500;i>0;i--)
		smallReverseSorted[i]=i;


    

}