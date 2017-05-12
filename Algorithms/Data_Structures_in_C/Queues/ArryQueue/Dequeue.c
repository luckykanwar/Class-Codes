#include<stdio.h>
#include<stdlib.h>
typedef struct Node
{
    struct Node * previous;
    int value;
    struct Node * next;
}Node;

typedef struct Queue
{
    struct Node * front;
    struct Node * rear;
}Queue;

void input_insertQ(Queue * queue)
{
    int value;
    printf("Please enter the value to be inserted into the queue\n");
    scanf("%d",&value);

    if(queue->front == NULL && queue->rear == NULL)
    {
        printf("This is the first value to be inserted\n");
        Node * node = (Node *) malloc(sizeof(Node));
        node->previous = NULL;
        node->next = NULL;
        node->value = value;
        queue->front = node;
        queue->rear = node;
    }
    else
    {
        Node * node = (Node *) malloc(sizeof(Node));
        node->previous = queue->rear;
        queue->rear->next = node;
        node->next = NULL;
        node->value = value;
        queue->rear = node;
    }
}

void input_extractQF(Queue * queue)
{
    Node * currentNode = (Node *) malloc(sizeof(Node));
    Node * nextNode = (Node *) malloc(sizeof(Node));
    currentNode = queue->front;
    if(currentNode->next == NULL && currentNode->previous == NULL )
    {
        printf("The value we are extracting is : %d\n", currentNode->value);
        queue->front = NULL;
        queue->rear = NULL;
        free(currentNode);
    }
    else
    {
        nextNode = currentNode->next;
        queue->front = nextNode;
        nextNode->previous = NULL;
        currentNode->next = NULL;
        printf("The value we are extracting is : %d\n", currentNode->value);
        free(currentNode);
    }
}

void input_extractQR(Queue * queue)
{
    Node * currentNode = (Node *) malloc(sizeof(Node));
    Node * prevNode = (Node *) malloc(sizeof(Node));
    currentNode = queue->rear;
    if(currentNode->next == NULL && currentNode->previous == NULL )
    {
        printf("The value we are extracting is : %d\n", currentNode->value);
        queue->front = NULL;
        queue->rear = NULL;
        free(currentNode);
    }
    else
    {
        prevNode = currentNode->previous;
        queue->rear = prevNode;
        prevNode->next = NULL;
        currentNode->previous = NULL;
        printf("The value we are extracting is : %d\n", currentNode->value);
        free(currentNode);
    }
}

void input_displayQ(Queue * queue)
{
    Node * traverse = (Node *) malloc(sizeof(Node));
    traverse = queue->front;
    while(traverse != NULL)
    {
        printf("The values in the dequeue are : %d\n",traverse->value);
        traverse = traverse->next;
    }
}

void output_insertQF(Queue * queue)
{
    int value;
    printf("Please enter the value to be inserted into the queue\n");
    scanf("%d",&value);

    if(queue->front == NULL && queue->rear == NULL)
    {
        printf("This is the first value to be inserted\n");
        Node * node = (Node *) malloc(sizeof(Node));
        node->previous = NULL;
        node->next = NULL;
        node->value = value;
        queue->front = node;
        queue->rear = node;
    }
    else
    {
        Node * node = (Node *) malloc(sizeof(Node));
        node->previous = NULL;
        queue->front->previous = node;
        node->next = queue->front;
        node->value = value;
        queue->front = node;
    }
}

void output_insertQR(Queue * queue)
{
    int value;
    printf("Please enter the value to be inserted into the queue\n");
    scanf("%d",&value);

    if(queue->front == NULL && queue->rear == NULL)
    {
        printf("This is the first value to be inserted\n");
        Node * node = (Node *) malloc(sizeof(Node));
        node->previous = NULL;
        node->next = NULL;
        node->value = value;
        queue->front = node;
        queue->rear = node;
    }
    else
    {
        Node * node = (Node *) malloc(sizeof(Node));
        node->previous = queue->rear;
        queue->rear->next = node;
        node->next = NULL;
        node->value = value;
        queue->rear = node;
    }
}

void output_extractQR(Queue * queue)
{
    Node * currentNode = (Node *) malloc(sizeof(Node));
    Node * prevNode = (Node *) malloc(sizeof(Node));
    currentNode = queue->rear;
    if(currentNode->next == NULL && currentNode->previous == NULL )
    {
        printf("The value we are extracting is : %d\n", currentNode->value);
        queue->front = NULL;
        queue->rear = NULL;
        free(currentNode);
    }
    else
    {
        prevNode = currentNode->previous;
        queue->rear = prevNode;
        prevNode->next = NULL;
        currentNode->previous = NULL;
        printf("The value we are extracting is : %d\n", currentNode->value);
        free(currentNode);
    }
}

void output_displayQ(Queue * queue)
{
    Node * traverse = (Node *) malloc(sizeof(Node));
    traverse = queue->front;
    while(traverse != NULL)
    {
        printf("The values in the dequeue are : %d\n",traverse->value);
        traverse = traverse->next;
    }
}

int inputRQ(Queue * queue)
{
    char cont = 'Y';
    int choice;
    while(cont == 'Y' || cont=='y')
    {
        printf("************************************\n");
        printf("This is input restricted queue zone !\n");
        printf("1. Insert into queue from rear\n2. Extract from front\n3. Extract from rear\n4. Display queue\n5. Exit\n");
        scanf("%d", &choice);
        switch(choice)
        {
            case 1:
                input_insertQ(queue);
                break;

            case 2:
                input_extractQF(queue);
                break;

            case 3:
                input_extractQR(queue);
                break;

            case 4:
                input_displayQ(queue);
                break;

            default:
                return 0;
        }
        printf("Do you want to continue ? :\n");
        scanf(" %c",&cont);
    }
    return 0;
}

int outputRQ(Queue * queue)
{
    char cont = 'Y';
    int choice;
    while(cont == 'Y' || cont=='y')
    {
        printf("************************************\n");
        printf("This is output restricted queue zone !\n");
        printf("1. Insert into queue from front\n2. Insert into queue from rear\n3. Extract from rear\n4. Display queue\n5. Exit\n");
        scanf("%d", &choice);
        switch(choice)
        {
            case 1:
                output_insertQF(queue);
                break;

            case 2:
                output_insertQR(queue);
                break;

            case 3:
                output_extractQR(queue);
                break;

            case 4:
                output_displayQ(queue);
                break;

            default:
                return 0;
        }
        printf("Do you want to continue ? :\n");
        scanf(" %c",&cont);
    }
    return 0;
}

int main()
{
    char cont = 'Y';
    int type;
    Queue * queue = (Queue *) malloc(sizeof(Queue));
    queue->front = NULL;
    queue->rear = NULL;

    while(cont == 'Y' || cont=='y')
    {
        printf("Welcome to the world of Double Ended Queues!\n");
        /*
        --------------------------------------------------------------------------------------------------------------------------------
            Theory of double ended queue/head tail linkedlist -
            1. This can be implemented using a circular array or circular double linked list
            2. There are two types of double ended queues :
            a. Input restricted queue
               This type of queue allows insertion into the queue only from one end while the deletion can be done from both the ends.
            b. Output restricted queue
               This type of queue allows insertion from both the ends while deletion can only take place from one end.
        --------------------------------------------------------------------------------------------------------------------------------
        */
        printf("Please select from below : \n");
        printf("Type of queue to work with :\n1. Input restricted queue\n2. Output restricted queue\n3. Exits\n");
        scanf("%d", &type);
        switch(type)
        {
            case 1:
                inputRQ(queue);
                break;

            case 2:
                outputRQ(queue);
                break;

            default:
                return 0;
        }
        printf("Do you wish to continue : ");
        scanf(" %c",&cont);
    }
    return 0;
}

