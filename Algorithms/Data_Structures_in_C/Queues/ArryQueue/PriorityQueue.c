#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    int value;
    int priority;
    struct Node * next;
}Node;

typedef struct Queue
{
    Node * front;
    Node * rear;
}Queue;

void displayQ(Queue * queue)
{
    Node * node = (Node *) malloc(sizeof(Node));
    node = queue->front;
    printf("The values in the priority queue are : \n");
    while(node != NULL)
    {
        printf("value : %d | priority : %d\n", node->value, node->priority);
        node = node->next;
    }
}

void insertQ(Queue * queue)
{
    // High number means higher priority in this program
    int value, priority;
    char cont = 'Y';
    while(cont == 'Y' || cont=='y')
    {
        printf("Please enter the value and the priority\n");
        printf("Value | Priority\n");
        scanf("%d %d",&value, &priority);
        Node * node = (Node *) malloc(sizeof(Node));
        if(queue->front == NULL && queue->rear == NULL)
        {
            printf("This is the first node \n");
            node->next= NULL;
            node->value = value;
            node->priority = priority;
            queue->front = node;
            queue->rear = node;
        }
        else
        {
            node = queue->front;
            Node * ptr = (Node *) malloc(sizeof(Node));
            while((node->next != NULL) && (node->next->priority <= priority))
            {
                node = node->next;
            }
            ptr->value = value;
            ptr->priority = priority;
            ptr->next = node->next;
            node->next = ptr;
        }
        printf("Do you wish to continue ? Y/N\n");
        scanf(" %c", &cont);
    }
}

void extractQ(Queue * queue)
{
    Node * node = (Node *) malloc(sizeof(Node));
    if(queue->front == NULL)
    {
        printf("There are no more nodes to be removed !\n");
        return;
    }
    node = queue->front;
    printf("The value of the node to be extracted is : %d and its priority is : %d\n", node->value, node->priority);
    if(node->next != NULL)
    {
        queue->front = node->next;
        node->next = NULL;
        free(node);
    }
    else
    {
        queue->rear = NULL;
        queue->front = NULL;
        free(node);
    }
}

void peekQ(Queue * queue)
{
    if(queue->front == NULL)
    {
        printf("There are no more nodes to be peeked!\n");
        return;
    }
    else
    {
        printf("The value at the head of the queue is : %d and its priority is : %d\n", queue->front->value, queue->front->priority);
    }
}

int main()
{
    char cont = 'Y';
    int choice;

    Queue * queue = (Queue *) malloc(sizeof(Queue));
    queue->front = NULL;
    queue->rear = NULL;

    while(cont == 'Y' || cont=='y')
    {
        printf("Welcome to the world of priority queues !\n");
        printf("Please select from below : \n");
        printf("1. Insert into queue\n2. Extract from queue\n3. Peek from queue\n4. Display queue\n6. Exit\n");
        scanf("%d", &choice);

        switch(choice)
        {
            case 1:
                insertQ(queue);
                break;

            case 2:
                extractQ(queue);
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
        printf("Do you wish to continue : ");
        scanf(" %c",&cont);
    }
    return 0;
}
