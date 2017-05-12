#include<stdio.h>
#include<stdlib.h>
#define MAX 100

int originalList[MAX] = {0};
int stack[MAX] = {0};
int reversedList[MAX] = {0};

int * insertList()
{
	int value, i = 0,* b;
	int cont = 1;
	while(cont == 1)
	{
        printf("Please enter the number to be pushed into the original list : ");
        scanf("%d", &value);
        originalList[i] = value;
        i++;
        printf("Do you want to continue (0/1): ");
        scanf("%d", &cont);
	}
	b = &i;
	return(b);
	//return(&i); -- We can't do this because i is local to the given function insertList. It has its existence only till the point this function is alive on the stack.
	//Once the stack pops off the function, the address linked with this variable is also lost. So the returned address is not longer in existence hence it makes no sense to
	//return the address. Why am I able to return an address of a pointer ?
}

void display(int list)
{
	printf("The values in the list are : \n");
    for(int i = 0;i < list; i++)
	{
		printf("%d\n", originalList[i]);
	}
}

void displayReverse(int list)
{
	printf("The values in the reversed list are : \n");
    for(int i = 0;i < list; i++)
	{
		printf("%d\n", reversedList[i]);
	}
}

void pushToStack(int list)
{
    int j=0;
    for(int i = list-1; i>=0; i--)
    {
        stack[i] = originalList[j];
        j++;
    }
}

void popFromStack(int list)
{
    for(int i=0; i<list; i++)
    {
        reversedList[i] = stack[i];
    }
}

void reverseList(int list)
{
    pushToStack(list);
    popFromStack(list);
}

int main()
{
	int choice, number;
	int * position;
	char cont = 'Y';
    while(cont == 'Y' || cont == 'y')
    {
        	printf("Welcome to the world of Reverse Lists!\n");
	        printf("Here are your available options : \n1. Insert into the list \n2. Reverse the list \n3. Display the list\n4. Exit\n");
        	scanf(" %d",&choice);

	        if(choice == 1)
        	{
           	    position = insertList();
                number = *position;
        	    display(number);
        	}
	        else if(choice == 2)
        	{
           	    reverseList(number);
        	    displayReverse(number);
        	}
        	else if(choice == 3)
        	{
        	    displayReverse(number);
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

