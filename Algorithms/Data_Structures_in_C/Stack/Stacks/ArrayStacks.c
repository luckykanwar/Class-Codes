#include <stdio.h>
#include <stdlib.h>
void display(int * stackArray, int top, int max)
{
    if(top > -1)
    {
        printf("The values you have pushed into the stack are : \n");
        for(int i = top; i>=0 ; i--)
        {
            printf(" %d\n", *(stackArray+i));
        }
    }
}

int push(int * stackArray, int top, int max)
{
    int valueToPush;
    printf("Please enter the value to be pushed onto the stack : \n");
    scanf("%d", &valueToPush);

    if(top == max)
    {
        printf("You have encountered stack overflow !\n");
        return max;
    }
    else
    {
        top ++;
        *(stackArray + top) = valueToPush;
        return top;
    }
}

int pop(int * stackArray, int top, int max)
{
    if(top == -1)
    {
        printf("You have encountered stack underflow !\n");
        return -1;
    }
    else
    {
        printf("This values has been popped off the stack : %d\n", *(stackArray+top));
        *(stackArray+top) = 0;
        top --;
        return top;
    }
}

void peek(int * stackArray, int top, int max)
{
    if(top != -1 || top != max)
    {
        printf("The top most value on the stack is : %d\n", *(stackArray+top));
    }
    else
    {
        printf("Out of bound values being accessed !");
    }
}

int main()
{
    int choice, top = -1, max = 100; // I have to check the array access is always done between the top and the max values, else we get overflow or underflow problems
    char cont = 'Y';
    int stackArray[100] = {};
    while(cont =='Y' || cont == 'y')
    {
        printf("Welcome to the world of Stacks using Arrays!\n");
        printf("Here are your available options : \n1. Push\n2. Pop \n3. Peek\n4. Display Stack\n5. Exit\n");
        scanf(" %d",&choice);

        if(choice == 1)
        {
            top = push(stackArray, top, max);
            display(stackArray, top, max);
        }
        else if(choice == 2)
        {
            top = pop(stackArray, top, max);
            display(stackArray, top, max);
        }
        else if(choice == 3)
        {
            peek(stackArray, top, max);
        }
        else if(choice == 4)
        {
            display(stackArray, top, max);
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
