#include<stdio.h>
#include<stdlib.h>

typedef struct Node
{
    struct Node * previous;
    int data;
    struct Node * next;
}Node;

Node * createList()
{
    Node * headerNode = (Node *) malloc(sizeof(Node));
    printf("Please enter the value for the headerNode : ");
    scanf("%d", &headerNode->data);
    headerNode->next = -1;
    headerNode->previous = -1;
    return headerNode;
}

void displayList(Node * headerNode)
{
    Node * ptr = (Node *) malloc(sizeof(Node));
    ptr = headerNode;
    while(ptr != -1)
    {
        printf("The values you entered in the list are : %d\n", ptr->data);
        ptr = ptr->next;
    }
}

Node * addNodeAtBegin(Node * headerNode)
{
    Node * ptr = (Node *) malloc(sizeof(Node));
    printf("Please enter the value for the new headerNode : ");
    scanf("%d", &ptr->data);
    ptr->next = headerNode;
    ptr->previous = -1;
    headerNode->previous = ptr;
    return ptr;
}

Node * addNodeInEnd(Node * headerNode)
{
    Node * temp = (Node *) malloc(sizeof(Node));
    Node * ptr = (Node *) malloc(sizeof(Node));
    temp = headerNode;
    printf("Please enter the value for the node : ");
    scanf("%d", &ptr->data);
    while(temp->next != -1)
    {
        temp = temp->next;
    }
    temp->next = ptr;
    ptr->previous = temp;
    ptr->next = -1;
    return headerNode;
}

Node * addNodeAfterGivenNode(Node * headerNode)
{
    int addAfter;
    Node * temp = (Node *) malloc(sizeof(Node));
    Node * ptr = (Node *) malloc(sizeof(Node));
    temp = headerNode;
    printf("Please enter the value for the node : ");
    scanf("%d", &ptr->data);
    printf("Please enter the value after which to add : ");
    scanf("%d", &addAfter);
    while(temp->data != addAfter)
    {
        temp = temp->next;
    }
    ptr->next = temp->next;
    ptr->previous = temp;
    temp->next = ptr;
    return headerNode;
}

Node * addNodeBeforeGivenNode(Node * headerNode)
{
    int addBefore;
    Node * temp = (Node *) malloc(sizeof(Node));
    Node * ptr = (Node *) malloc(sizeof(Node));
    Node * previous = (Node *) malloc(sizeof(Node));
    temp = headerNode;
    printf("Please enter the value for the node : ");
    scanf("%d", &ptr->data);
    printf("Please enter the value after which to add : ");
    scanf("%d", &addBefore);

    while(temp->data != addBefore)
    {
        previous = temp;
        temp= temp->next;
    }
    ptr->previous = temp->previous;
    ptr->next = temp;
    temp->previous = ptr;
    previous->next = ptr;
    return(headerNode);
}

Node * deleteFirstNode(Node * headerNode)
{
    Node * ptr = (Node *) malloc(sizeof(Node));
    ptr = headerNode;

    if(ptr->next == -1)
    {
        free(ptr);
        return -1;
    }

    headerNode = ptr->next;
    headerNode->previous = -1;
    free(ptr);
    return(headerNode);
}

Node * deleteLastNode(Node * headerNode)
{
    Node * ptr = (Node *) malloc(sizeof(Node));
    Node * previous = (Node *) malloc(sizeof(Node));
    ptr = headerNode;

    if(ptr->next == -1)
    {
        free(ptr);
        return -1;
    }

    while(ptr->next != -1)
    {
        previous = ptr;
        ptr = ptr->next;
    }
    previous->next = -1;
    ptr->previous = -1;
    free(ptr);
    return(headerNode);
}

Node * deleteAfterGivenNode(Node * headerNode)
{
    int deleteAfter;
    Node * temp = (Node *) malloc(sizeof(Node));
    Node * ptr = (Node *) malloc(sizeof(Node));
    temp = headerNode;
    printf("Please enter the value after which to delete : ");
    scanf("%d", &deleteAfter);
    while(temp->data != deleteAfter)
    {
        temp = temp->next;
    }
    ptr = temp->next;
    temp->next = -1;
    ptr->previous = -1;
    free(ptr);
    return headerNode;
}

Node * deleteBeforeGivenNode(Node * headerNode)
{
    int deleteBefore;
    Node * temp = (Node *) malloc(sizeof(Node));
    Node * ptr = (Node *) malloc(sizeof(Node));
    Node * previous = (Node *) malloc(sizeof(Node));
    temp = headerNode;
    printf("Please enter the value before which to delete : ");
    scanf("%d", &deleteBefore);
    while(temp->data != deleteBefore)
    {
        temp = temp->next;
    }
    ptr = temp->previous;
    previous = ptr->previous;
    previous->next = temp;
    temp->previous = previous;
    ptr->previous = -1;
    ptr->next = -1;
    free(ptr);
    return headerNode;
}

Node * deleteEntireList(Node * headerNode)
{
    Node * ptr = (Node *) malloc(sizeof(Node));
    Node * temp = (Node *) malloc(sizeof(Node));
    ptr = headerNode;
    while(ptr != -1)
    {
        ptr = deleteFirstNode(ptr);
    }
    return -1;
}

int main()
{
    char cont = 'Y';
    int choice;
    Node * headerNode = (Node *) malloc(sizeof(Node));

    while(cont == 'Y' || cont == 'y')
    {
        printf("Welcome to the world of double linked list !\n");
        printf("Please enter your choice from below given options :\n");
        printf("1. Create list\n2. Display list\n3. Add node at the beginning\n4. Add node in the end\n5. Add node after a given node\n");
        printf("6. Add node before a given node\n7. Delete first node\n8. Delete last node\n9. Delete after a given node\n10. Delete before a given node\n11. Delete entire list\n");
        scanf("%d", &choice);

        if(choice == 1)
        {
            headerNode = createList();
            displayList(headerNode);
        }
        if(choice == 2)
        {
            displayList(headerNode);
        }
        if(choice == 3)
        {
            headerNode = addNodeAtBegin(headerNode);
            displayList(headerNode);
        }
        if(choice == 4)
        {
            headerNode = addNodeInEnd(headerNode);
            displayList(headerNode);
        }
        if(choice == 5)
        {
            headerNode = addNodeAfterGivenNode(headerNode);
            displayList(headerNode);
        }
        if(choice == 6)
        {
            headerNode = addNodeBeforeGivenNode(headerNode);
            displayList(headerNode);
        }
        if(choice == 7)
        {
            headerNode = deleteFirstNode(headerNode);
            displayList(headerNode);
        }
        if(choice == 8)
        {
            headerNode = deleteLastNode(headerNode);
            displayList(headerNode);
        }
        if(choice == 9)
        {
            headerNode = deleteAfterGivenNode(headerNode);
            displayList(headerNode);
        }
        if(choice == 10)
        {
            headerNode = deleteBeforeGivenNode(headerNode);
            displayList(headerNode);
        }
        if(choice == 11)
        {
            headerNode = deleteEntireList(headerNode);
            displayList(headerNode);
        }

        printf("Do you want to continue : ");
        scanf(" %c", &cont);
    }
}

