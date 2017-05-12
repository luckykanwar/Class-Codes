#include<stdio.h>
#include<stdlib.h>
#define MAX 5
/*In a multistack, there can be more than one stack implementation on the same array. The separation is done based on the location of flags for each array. For an example, the start flag for one array can be the start index of the array while the start for another array can be the index representing the end of the array*/

int MultiStack[MAX] = {0};
int topA = -1; // We start from -1 because else the index moves one location ahead of the actual array data causing stack overflow
int topB = MAX;

void pushA()
{
	int value;
	printf("Please enter the number to be pushed onto the stack A :");
	scanf("%d", &value);

	if(topA+1 == topB)
	{
		printf("Stack overflow will be caused !");
	}
	else
	{
		topA = topA + 1;
		MultiStack[topA] = value;
	}
}

void popA()
{
	int value;
	if(topA-1 == -1)
	{
		printf("Stack underflow will be caused !");
	}
	else
	{
		MultiStack[topA] = 0;
		topA--;
	}
}

void displayA()
{
    int i;
	printf("The values in the Stack A are : \n");
//	printf("%d", MultiStack[0]);
	for(i = topA;i >= 0; i--)
	{
		printf("%d\n", MultiStack[i]);
	}
}

void pushB()
{
	int value;
	printf("Please enter the number to be pushed onto the stack B :");
	scanf("%d", &value);

	if(topB-1 == topA)
	{
		printf("Stack overflow will be caused !");
	}
	else
	{
		topB = topB - 1;
		MultiStack[topB] = value;
	}
}

void popB()
{
	int value;
	if(topB+1 == MAX)
	{
		printf("Stack underflow will be caused !");
	}
	else
	{
		MultiStack[topB] = 0;
		topB++;
	}
}

void displayB()
{
    int i;
	printf("The values in the Stack B are : \n");
//	printf("%d", MultiStack[0]);
	for(i = topB; i <= MAX-1; i++)
	{
		printf("%d\n", MultiStack[i]);
	}
}

int main()
{
	int choice;
	char cont = 'Y';
    	while(cont =='Y' || cont == 'y')
    	{
        	printf("Welcome to the world of Multistacks!\n");
	        printf("Here are your available options : \n1. Push into Stack A\n2. Push into Stack B\n3. Pop from Stack A\n4. Pop from Stack B\n5. Display Stack A\n6. Display Stack B\n7. Exit\n");
        	scanf(" %d",&choice);

	        if(choice == 1)
        	{
           	    pushA();
        	    displayA();
        	}
	       else if(choice == 2)
        	{
           	    pushB();
        	    displayB();
        	}
        	else if(choice == 3)
        	{
                popA();
        	    displayA();
        	}
           else if(choice == 4)
        	{
                popB();
        	    displayB();
        	}
        	else if(choice == 5)
        	{
        	    displayA();
        	}
        	else if(choice == 6)
            {
        	    displayB();
            }
            else
            {
                return 0;
            }
        	printf("Do you want to continue further ? \n");
        	scanf(" %c", &cont);
  	}
        return 0;

}

