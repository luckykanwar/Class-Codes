#include <stdio.h>
#include <stdlib.h>
typedef struct Node
{
    int value;
    struct Node * next;
}Node;

typedef struct Queue
{
    Node * front;
    Node * rear;
}Queue;

Queue * insertQ(Queue * queue)
{
    int value;
    printf("Enter the value to be inserted into the queue\n");
    scanf("%d", &value);

    Node * node = (Node *) malloc(sizeof(Node));
    Node * currentRear = (Node *) malloc(sizeof(Node));

    if(queue->rear == NULL || queue->front == NULL)
    {
        printf("This is the first value to be inserted into the queue\n");
        node->next = NULL;
        node->value = value;
        queue->front = node;
        queue->rear = node;
    }
    else
    {
        node->value = value;
        currentRear = queue->rear;
        currentRear->next = node;
        queue->rear = node;
        node->next = NULL;
    }
    return queue;
}

Queue * extractQ(Queue * queue)
{
    Node * node = (Node *) malloc(sizeof(Node));
    Node * currentFront = (Node *) malloc(sizeof(Node));
    node = currentFront = queue->front;
    node = node->next;
    queue->front = node;
    free(currentFront);
    return queue;
}

void peekQ(Queue * queue)
{
    if(queue->front != NULL)
    {
        printf("The value at the head of the queue is : %d\n", queue->front->value);
    }
    else
    {
        printf("The queue is empty !\n");
    }
}

void displayQ(Queue * queue)
{
    Node * node = (Node *) malloc(sizeof(Node));
    node = queue->front;

    while(node != NULL)
    {
        printf("The values in the queue are : ");
        printf("%d\n", node->value);
        node = node->next;
    }
}

int main()
{
    char cont = 'Y';
    int choice;
    Queue * queue = (Queue *) malloc(sizeof(Queue));
    queue->front = NULL;
    queue->rear = NULL;

    printf("Welcome to the world of Linked Queue !\n");
    while(cont == 'Y' || cont == 'y')
    {
        printf("Please select a choice :\n");
        printf("1. Insert into queue\n2. Delete from queue\n3. Peek from queue\n4. Display queue\n5. Exit\n");
        scanf("%d", &choice);
        switch(choice)
        {
            case 1:
                queue = insertQ(queue);
                break;

            case 2:
                queue = extractQ(queue);
                break;

            case 3:
                peekQ(queue);
                break;

            case 4:
                displayQ(queue);
                break;

            default:
                return 0;

        }
        printf("Do you wish to continue ?\n");
        scanf(" %c", &cont);
    }
    return 0;
}
