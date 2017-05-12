#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    int data;
    struct Node * nextNode;
}Node;

Node * createList()
{
    Node * headNode = (Node *) malloc(sizeof(Node));
    printf("Please enter a value for the head node : \n");
    scanf("%d",&(headNode->data));
    headNode->nextNode = -1;
    return headNode;
}

int displayList(Node * headerNode)
{
    Node * ptr;
    ptr = headerNode;
//    if(headerNode->nextNode == -1)
//    {
//        printf("This is the header node!\n");
//        printf("The number you entered in the list is : %d\n", headerNode->data);
//    }
    if(headerNode == -1)
    {
        printf("The entire list has been cleared");
        return 0;
    }

    while(ptr != -1)
    {
        printf("The number you entered in the list is : %d\n", ptr->data);
        ptr = ptr->nextNode;
    }
    return 0;
}

Node * addNodeBegin(Node * headerNode)
{
    Node * newHeaderNode = (Node *) malloc(sizeof(Node));
    newHeaderNode->nextNode = headerNode;
    printf("Please enter a value for the node : \n");
    scanf("%d",&(newHeaderNode->data));
    return newHeaderNode;
}

void addNodeEnd(Node * headerNode)
{
    Node * ptr = headerNode;
    Node * endNode = (Node *) malloc(sizeof(Node));
    while(ptr->nextNode != -1)
    {
        ptr = ptr->nextNode;
    }
    printf("Please enter a value for the new end node : \n");
    scanf("%d",&(endNode->data));
    endNode->nextNode = -1;
    ptr->nextNode = endNode;
}

Node * addNodeBeforeGivenNode(Node * headerNode)
{
    int numberToAdd,numberToBeAddedBefore;
    Node * nodeToAdd = (Node *) malloc(sizeof(Node));
    Node * ptr = (Node *) malloc(sizeof(Node));
    Node * previous = (Node *) malloc(sizeof(Node));
    ptr = headerNode;
    printf("Please enter the number to be added : ");
    scanf("%d",&numberToAdd);
    nodeToAdd->data = numberToAdd;
    printf("Please add the number before which it should be added : ");
    scanf("%d",&numberToBeAddedBefore);

    if(ptr->data==numberToBeAddedBefore)
    {
        nodeToAdd->nextNode = ptr;
        headerNode = nodeToAdd;
        return headerNode;
    }

    while(ptr->data != numberToBeAddedBefore)
    {
        previous = ptr;
        ptr = ptr->nextNode;
    }
    previous->nextNode = nodeToAdd;
    nodeToAdd->nextNode = ptr;
    return headerNode;
}

void addNodeAfterGivenNode(Node * headerNode)
{
    int numberToAdd,numberToBeAddedAfter;
    Node * nodeToAdd = (Node *) malloc(sizeof(Node));
    Node * ptr = (Node *) malloc(sizeof(Node));
    ptr = headerNode;
    printf("Please enter the number to be added : ");
    scanf("%d",&numberToAdd);
    nodeToAdd->data = numberToAdd;
    printf("Please add the number after which it should be added : ");
    scanf("%d",&numberToBeAddedAfter);

    while(ptr->data != numberToBeAddedAfter)
    {
        ptr = ptr->nextNode;
    }
    nodeToAdd->nextNode = ptr->nextNode;
    ptr->nextNode = nodeToAdd;
}

Node * deleteNodeFromBegin(Node * headerNode)
{
    Node * ptr = (Node *) malloc(sizeof(Node));
    ptr = headerNode;
    headerNode = headerNode->nextNode;
    free(ptr);
    return headerNode;
}

Node * deleteNodeFromEnd(Node * headerNode)
{
    Node * ptr = (Node *) malloc(sizeof(Node));
    Node * previous = (Node *) malloc(sizeof(Node));
    ptr = headerNode;

    if(ptr->nextNode == -1)
    {
        free(ptr);
        return -1;
    }

    while(ptr->nextNode != -1)
    {
        previous = ptr;
        ptr = ptr->nextNode;
    }
    free(ptr);
    previous->nextNode = -1;
}

Node * deleteGivenNode(Node * headerNode)
{
    int numberToDelete;
    Node * nodeToDelete = (Node *) malloc(sizeof(Node));
    Node * ptr = (Node *) malloc(sizeof(Node));
    Node * previous = (Node *) malloc(sizeof(Node));
    ptr = headerNode;
    printf("Please enter the number to be deleted : ");
    scanf("%d",&numberToDelete);
    nodeToDelete->data = numberToDelete;

    if(ptr->nextNode == -1)
    {
        free(ptr);
        return -1;
    }

    while(ptr->data != numberToDelete)
    {
        previous = ptr;
        ptr = ptr->nextNode;
    }

    previous->nextNode = ptr->nextNode;
    free(ptr);
    return headerNode;
}

void deleteNodeAfterGivenNode(Node * headerNode)
{
    int numberToDelete,numberToBeDeletedAfter;
    Node * nodeToDelete = (Node *) malloc(sizeof(Node));
    Node * ptr = (Node *) malloc(sizeof(Node));
    ptr = headerNode;
    printf("Please enter the number to be delete : ");
    scanf("%d",&numberToDelete);
    nodeToDelete->data = numberToDelete;
    printf("Please add the number after which it should be deleted : ");
    scanf("%d",&numberToBeDeletedAfter);

    while(ptr->data != numberToBeDeletedAfter)
    {
        ptr = ptr->nextNode;
    }
    nodeToDelete = ptr->nextNode;
    ptr->nextNode = nodeToDelete->nextNode;
    free(nodeToDelete);
}

Node * deleteEntireList(Node * headerNode)
{
    Node * ptr = (Node *) malloc(sizeof(Node));
    Node * nextNode = (Node *) malloc(sizeof(Node));
    ptr = headerNode;
    nextNode = ptr;
    while(ptr != -1)
    {
        nextNode = ptr->nextNode;
        free(ptr);
        ptr = nextNode;
    }
    return -1;
}

Node * sortList(Node * headerNode)
{
    Node * ptr = (Node *) malloc(sizeof(Node));
    Node * nextNode = (Node *) malloc(sizeof(Node));
    int temp;
    ptr = headerNode;
    while(ptr->nextNode != -1)
    {
        nextNode = ptr->nextNode;
        while(nextNode != -1)
        {
            if(ptr->data > nextNode->data)
            {
                temp = nextNode->data;
                nextNode->data = ptr->data;
                ptr->data = temp;
            }
            nextNode = nextNode->nextNode;
        }
        ptr = ptr->nextNode;
    }
    return headerNode;
}

int main()
{
    int choice, display;
    char cont = 'Y';
    Node * headerNode;
    while(cont == 'Y')
    {
        printf("Hello to the world of LinkedLists !\n");
        printf("Your options are : \n1. Create List \n2. Display the list \n3. Add a node in the beginning \n4. Add a node in the end \n5. Add a node before a given node \n");
        printf("6. Add a node after a given node\n7. Delete a node from beginning \n8. Delete a node from end \n9. Delete a given node\n10. Delete a node after a given node\n");
        printf("11. Delete the entire list\n12. Sort the list\n");
        printf("Please enter your choice : ");
        scanf("%d", &choice);
        if(choice == 1)
        {
            headerNode = createList();
        }
        else if (choice == 2)
        {
            display = displayList(headerNode);
        }
        else if (choice == 3)
        {
            headerNode = addNodeBegin(headerNode);
            display = displayList(headerNode);
        }
        else if (choice == 4)
        {
            addNodeEnd(headerNode);
            display = displayList(headerNode);
        }
        else if (choice == 5)
        {
            headerNode = addNodeBeforeGivenNode(headerNode);
            display = displayList(headerNode);
        }
        else if (choice == 6)
        {
            addNodeAfterGivenNode(headerNode);
            display = displayList(headerNode);
        }
        else if (choice == 7)
        {
            headerNode = deleteNodeFromBegin(headerNode);
            display = displayList(headerNode);
        }
        else if (choice == 8)
        {
            headerNode = deleteNodeFromEnd(headerNode);
            display = displayList(headerNode);
        }
        else if (choice == 9)
        {
            headerNode = deleteGivenNode(headerNode);
            display = displayList(headerNode);
        }
        else if (choice == 10)
        {
            deleteNodeAfterGivenNode(headerNode);
            display = displayList(headerNode);
        }
        else if (choice == 11)
        {
            headerNode = deleteEntireList(headerNode);
        }
        else
        {
            headerNode = sortList(headerNode);
            display = displayList(headerNode);
        }
        printf("\nDo you want to continue : Y/N\n");
        scanf(" %c",&cont);
    }

//    Node * headNode = (Node *) malloc(sizeof(Node));
//    Node * nextNode = (Node *) malloc(sizeof(Node));
//    printf("Please enter a value for the head node : \n");
//    scanf("%d",&(headNode->data));
//    printf("The value entered for headnode is : %d\n", headNode->data);
//    headNode->nextNode = nextNode;
//    printf("Please enter a value for the next node : \n");
//    scanf("%d",&(nextNode->data));
//    printf("The value entered for next node is : %d\n", nextNode->data);
//    nextNode->nextNode = -1;
//
//    printf("LinkedList Traversal");
//    Node * header = &headNode;
//    while();

    return 0;
}
