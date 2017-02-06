// A C Program to demonstrate adjacency list representation of graphs
#include <stdio.h>
#include <stdlib.h>
int numberToGive = 0;
typedef struct City
{
    char city[100];
    int number;
    struct City * next;
}City;


void inputFile(char * inputFileName)
{
    FILE * fp;
    char * buffer[1000];
    char tokenArray[3][100];
    fp = fopen(inputFileName,"r");

    while(!feof(fp))
    {
        fgets(buffer, 500, fp);
        char * token = strtok(buffer, " ");
        int i = 0;
        while(token)
        {
            strcpy(tokenArray[i], token);
            i++;
            token = strtok(NULL, " ");
        }
    }
    fclose(fp);
}

int checkExistsOrNot(City * cityList, char * token)
{
    City * head = (City *) malloc(sizeof(City));
    head = cityList;
    while(head != -1)
    {
        if(strcmp(head->city,token) == 0)
        {
           return 1; //exists
        }
        else
        {
            head = head->next;
        }
    }
    return 0;
}

void inputFileConversion(char * inputFileName)
{
    FILE * fp;
    char * buffer[1000];
    char tokenArray[3][100];
    fp = fopen(inputFileName,"r");
    int firstTime  = 1;
    City * cityList = (City *) malloc(sizeof(City));

    while(!feof(fp))
    {
        fgets(buffer, 500, fp);
        char * token = strtok(buffer, " ");
        int i = 0;
        while(token)
        {
            strcpy(tokenArray[i], token);
            if(i!=2)
            {
                if(firstTime == 1)
                {
                    strcpy(cityList->city,tokenArray[i]);
                    cityList->next = -1;
                    cityList->number = numberToGive;
                    numberToGive ++;
                }
                else
                {
                    if(checkExistsOrNot(cityList,tokenArray[i]) == 0)
                    {
                        City * newCity = (City *) malloc(sizeof(City));
                        strcpy(newCity->city,tokenArray[i]);
                        cityList->next = newCity;
                        newCity->next = -1;
                        newCity->number = numberToGive;
                        numberToGive ++;
                    }
                }
            }
            i++;
            token = strtok(NULL, " ");
            firstTime = 0;
        }
    }
    fclose(fp);
    displayListRead(cityList);
}

// Driver program to test above functions
int main()
{
    char inputFileName[500];
    printf("Please enter the name of the file : ");
    scanf("%s", inputFileName);
    inputFile(inputFileName);
    return 0;
}
