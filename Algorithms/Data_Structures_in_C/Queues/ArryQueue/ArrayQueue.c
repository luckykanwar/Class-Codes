#include <stdio.h>
#include <stdlib.h>
#define MAX 100

int queue[MAX];
int front = -1;
int rear = -1;

void insertQ()
{
    int value;
    printf("Please enter the value you want to insert into the queue: ");
    scanf("%d",&value);
    if(rear == MAX-1)
    {
        printf("You may encounter overflow\n");
    }
    else if(front == -1)
    {
        front++;
        rear++;
        queue[front] = value;
    }
    else
    {
        rear++;
        queue[rear] = value;
    }
}

void deleteQ()
{
    if(front == -1 || front > rear)
    {
        printf("You may encounter underflow !\n");
    }
    else
    {
        queue[front] == 0;
        front++;
        if(front>rear)
        {
            front = rear = -1;
        }
    }
}

void peekQ()
{
    if(front == -1 || front>rear)
    {
        printf("The queue is empty !\n");
    }
    printf("The next value to be sent out is : %d", queue[front]);
}

void displayQ()
{
    printf("The values in the queue are :\n");
    for(int i = front; i<= rear; i ++)
    {
        printf("%d\n", queue[i]);
    }
}

int main()
{
    printf("Welcome to the world of Queues !\n");
    char cont='Y';
    int choice;
    while(cont == 'Y' || cont == 'y')
    {
        printf("Please enter your choice : \n");
        printf("1. Insert into the queue\n2. Delete from the queue\n3. Peek\n4. Display the queue\n5. Exit\n");
        scanf("%d",&choice);
        switch(choice)
        {
            case 1:
                insertQ();
                break;

            case 2:
                deleteQ();
                break;

            case 3:
                peekQ();
                break;

            case 4:
                displayQ();
                break;

            default:
                return 0;
        }
        printf("Do you wish to continue ? \n");
        scanf("%c", &cont);
    }
}
