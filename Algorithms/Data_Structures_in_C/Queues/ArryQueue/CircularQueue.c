#include <stdio.h>
#include <stdlib.h>
#define MAX 3

int queue[MAX] = {0};
int front = -1;
int rear = -1;

void insertQ()
{
    int value;
    printf("Please enter the value to be inserted into the queue : \n");
    scanf("%d",&value);
    if(front == -1 && rear == -1)
    {
        front = 0;
        rear = 0;
        queue[front] = value;
        printf("This is the first value inserted into the queue\n");
    }
    else
    {
        if(front == 0 && rear == MAX-1)
        {
            // In this case we will display a warning about array overflow
            printf("You may encounter overflow !\n");
        }
        else if(front != 0 && rear == MAX-1)
        {
            // In this case rear will be set to 0 to use the free space in the array
            rear = 0;
            queue[rear] = value;
        }
        else
        {
            // In this case we insert the value into the queue as usual
            if(rear+1 == front)
            {
                printf("You may encounter overflow !\n");
                return;
            }
            rear++;
            queue[rear] = value;
        }
    }
}

void extractQ()
{
    if(front == -1)
    {
        printf("You will encounter an underflow condition");
    }
    else
    {
        if(front == rear) // This means the queue has just one element in the end
        {
            printf("The next value to be extracted is : %d\n", queue[front]);
            front = -1;
            rear = -1;
        }
        else if(front == MAX-1)
        {
            printf("The next value to be extracted is : %d\n", queue[front]);
            front = 0;
        }
        else
        {
            printf("The next value to be extracted is : %d\n", queue[front]);
            queue[front] = 0;
            front++;
        }
    }
}

void peekQ()
{
    printf("The value at the head of the queue is : %d\n", queue[front]);
}

void displayQ()
{
    printf("The values in the queue from the front are : \n");

    if(front <= rear)
    {
        for(int i = front; i<= rear; i++)
        {
            printf("%d\n", queue[i]);
        }
    }
    else
    {
        for(int i = front; i<= MAX-1; i++)
        {
            printf("%d\n", queue[i]);
        }
        for(int i = 0; i<=rear; i++)
        {
            printf("%d\n", queue[i]);
        }
    }
}

void displayFrontRear()
{
    printf("The value of front is : %d\n", front);
    printf("The value of rear is : %d\n", rear);
}

int main()
{
    char cont = 'Y';
    int choice;

    while(cont == 'Y' || cont=='y')
    {
        printf("Welcome to the world of circular queues !\n");
        printf("Please select from below : \n");
        printf("1. Insert into queue\n2. Extract from queue\n3. Peek from queue\n4. Display queue\n5. Display front and rear\n6. Exit\n");
        scanf("%d", &choice);

        switch(choice)
        {
            case 1:
                insertQ();
                break;

            case 2:
                extractQ();
                break;

            case 3:
                peekQ();
                break;

            case 4:
                displayQ();
                break;

            case 5:
                displayFrontRear();
                break;

            default:
                return 0;
        }
        printf("Do you wish to continue : ");
        scanf(" %c",&cont);
    }
    return 0;
}
