#include<stdio.h>
#include<stdlib.h>

typedef struct Node
{
    int value;
    struct Node * next;
}Node;

Node * createChain(int number)
{
    Node * nodes, *head;
    int n = number;

    while(number > 0)
    {
        Node * player = (Node *) malloc(sizeof(Node));
        if(n == number)
        {
            printf("This has to be the head node!\n");
            player->value = number;
            player->next = NULL;
            nodes = player;
            head = player;
        }
        else
        {
            player->value = number;
            player->next = NULL;
            nodes->next = player;
            nodes = nodes->next;
        }
        number--;
    }
    nodes->next = nodes;
    return head;
}

void displayChain(Node * start, int number)
{
    Node * node = (Node *) malloc(sizeof(Node));
    node = start;
    while(number>0)
    {
        printf("The values in the chain are : %d\n", node->value);
        node = node->next;
        number--;
    }
}

void deleteLinks(Node * start, int number, int skip)
{
    Node * node = (Node *) malloc(sizeof(Node));
    node = start;
    int i = 0;
    while(number != 1)
    {
        if(i==skip)
        {
            printf("The number to be deleted is : %d\n", start->value);
            node->next = start->next;
            node = node->next;
            start = node;
            i = 0;
            number--;
        }
        else
        {
            i++;
            start = start->next;
        }
    }
}

int main()
{
    int number,skip;
    printf("Solving the Josephus Problem\n");
    printf("Please enter the number of players playing the game : \n");
    scanf("%d", &number);
    printf("Please enter the number to be skipped\n");
    scanf("%d",&skip);
    Node * start = createChain(number);
    displayChain(start,number);
    deleteLinks(start, number, skip);
}

