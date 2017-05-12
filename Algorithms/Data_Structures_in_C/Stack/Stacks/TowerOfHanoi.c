#include<stdio.h>
#include<stdlib.h>
void move(int disks, char source, char spare, char destination)
{
    if(disks==1)
    {
        printf("Move the disk from %c to %c\n", source, destination);
    }
    else
    {
        move(disks-1, source, destination,spare);
        move(1,source,spare,destination);
        move(disks-1,spare,source,destination);
    }
}

int main()
{
    int disks;
    printf("Enter the number of disks : ");
    scanf("%d",&disks);
    move(disks,'A','B','C');
}
