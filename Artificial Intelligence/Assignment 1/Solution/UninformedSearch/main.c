#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
typedef struct Node
{
    int distance;
    char city[100];
    struct Node * next;
}Node;

typedef struct infoNode
{
    char city[100];
    struct Node * head;
}infoNode;

Node * createNode(char * city)
{
    Node * source = (Node *) malloc(sizeof(Node));
    source->distance = 0;
    source->next = -1;
    strcpy(source->city,city);
    return source;
}

//parentNode * createParentList()
//{
//    parentNode * ptr = (parentNode *) malloc(sizeof(parentNode));
//    ptr->nextChild = -1;
//    ptr->nextParent = -1;
//    strcpy(ptr->city,"");
//    return ptr;
//}

//int checkParent(parentNode * parent, char * city)
//{
//    parentNode * ptr = (parentNode *) malloc(sizeof(parentNode));
//    ptr = parent;
//
//    while(ptr != -1)
//    {
//        if(strcmp(ptr->city,city) == 0)
//        {
//            return 1; //city exists
//        }
//        else
//        {
//            ptr = ptr->nextParent;
//        }
//    }
//    return 0;
//}
void displayNodeArray(infoNode * array[])
{
    printf("The value in the infoNode array is : %s", array[0]->city);
    printf("The value in the infoNode array is : %s", (array[0]->head)->city);
}

void displayArray(char tokenArray[3][100])
{
    for(int i=0; i<3; i++)
    {
        printf("%s", tokenArray[i]);
    }
    //printf("%s", tokenArray[0]);
}

Node * createList(char tokenArray[3][100])
{
    Node * source = (Node *) malloc(sizeof(Node));
    Node * destination = (Node *) malloc(sizeof(Node));
    strcpy(source->city,tokenArray[1]);
    source->distance = 0;
    strcpy(destination->city,tokenArray[2]);
    source->distance = (int)tokenArray[3];
    source->next = destination;
    return source;
}

void inputFile(char * inputFileName)
{
    FILE * fp;
    char * buffer[1000];
    char tokenArray[3][100];
    infoNode * array[1000];
    fp = fopen(inputFileName,"r");
//    parentNode * head = (parentNode *) malloc(sizeof(parentNode));
//    parentNode * ptr = (parentNode *) malloc(sizeof(parentNode));
//    head = ptr;
//    ptr->nextChild = -1;
//    ptr->nextParent = -1;
//    strcpy(ptr->city,"");

    while(!feof(fp))
    {
        fgets(buffer, 500, fp);
        //puts(buffer);
        char * token = strtok(buffer, " ");
        int i = 0;
        while(token)
        {
//            if(i==0)
//            {
//                if(checkParent(head,token))   //if the parent already exists in this list then do this
//                {
//                    strcpy(ptr->city,token);
//                }
//                else // if the parent does not exist then do this
//                {
//                    parentNode * parent = (parentNode *) malloc(sizeof(parentNode));
//                    parent->nextChild = -1;
//                    parent->nextParent = -1;
//                    strcpy(parent->city,token);
//                    ptr->nextParent = parent;
//                    ptr = ptr->nextParent;
//                }
//            }
//            else if(i==1)
//            {
//                strcpy(node->city,token);
//                ptr->nextChild = child;
//                child->next = -1;
//            }
//            else
//            {
//                child->distance = token;
//            }
            //printf("%s\n", token);
            //strcpy(tokenArray[i], token);
            strcpy(tokenArray[i], token);
            //printf("%s", tokenArray[i]);
            i++;
            token = strtok(NULL, " ");
        }
        //displayArray(tokenArray);
        array[0] = (infoNode *) malloc(sizeof(infoNode));
        array[0]->head = createList(tokenArray);
        strcpy(array[0]->city,(array[0]->head)->city);
        displayNodeArray(array);
    }
    fclose(fp);

}

int main()
{
    /*1. Maintain the parent node list */
//    parentNode * parent = (parentNode *) malloc(sizeof(parentNode));
    /*2. First step is to read the input file and create adjacency list array*/
    char inputFileName[500];
    printf("Please enter the name of the file : ");
    scanf("%s", inputFileName);
    inputFile(inputFileName);
    return 0;
}
