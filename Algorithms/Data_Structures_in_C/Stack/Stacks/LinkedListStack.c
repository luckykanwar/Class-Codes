#include<stdio.h>
#include <stdlib.h>

typedef struct Node
{
    int value;
    struct Node * next;
}Node;

Node * push(Node * top)
{
    int number;
    printf("Please enter the number to push to the stack : ");
    scanf("%d", &number);

    if(top == NULL)
    {
        top = (Node *) malloc(sizeof(Node));
        top->value = number;
        top->next = NULL;
        return top;
    }
    else
    {
        Node * head = (Node *) malloc(sizeof(Node));
        head->value = number;
        head->next = top;
        return head;
    }
}

Node * pop(Node * top)
{
    printf("Popping value : %d\n", top->value);
    Node * head = (Node *) malloc(sizeof(Node));
    head = top;
    top = top->next;
    free(head);
    return top;
}

void peek(Node * top)
{
    
    if(top != NULL)
    {
	printf("The top value is : %d\n",top->value);	
    }

}

void display(Node * top)
{
    printf("The values in the stack are : \n");
    while(top != NULL)
    {
        printf("%d\n", top->value);
        top = top->next;
    }
}

int main()
{
    int choice;
    Node * top = NULL;
    char cont = 'Y';
    while(cont =='Y' || cont == 'y')
    {
        printf("Welcome to the world of Stacks using LinkedList!\n");
        printf("Here are your available options : \n1. Push\n2. Pop \n3. Peek\n4. Display Stack\n5. Exit\n");
        scanf(" %d",&choice);

        if(choice == 1)
        {
            top = push(top);
            display(top);
        }
        else if(choice == 2)
        {
            top = pop(top);
            display(top);
        }
        else if(choice == 3)
        {
            peek(top);
        }
        else if(choice == 4)
        {
            display(top);
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
