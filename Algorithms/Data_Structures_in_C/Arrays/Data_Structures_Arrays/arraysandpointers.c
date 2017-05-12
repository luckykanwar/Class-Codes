#include<stdio.h>

int main()
{
    /*Pointers and arays*/
//    int array1[]={1,2,3,4,5}, array2[]={6,7,8,9,10}, array3[]={11,12,13,14,15};
//    int *ptr[3];
//
//    ptr[0] = array1;
//    ptr[1] = array2;
//    ptr[2] = array3;
//
//    int j=0;
//    for(int i=0; i<5; i++)
//    {
//        printf("The value at position %d in array1 is : %d\n", j, *(ptr[j]+i));
//        printf("The value at position %d in array2 is : %d\n", j+1, *(ptr[j+1]+i));
//        printf("The value at position %d in array3 is : %d\n", j+2, *(ptr[j+2]+i));
//    }

    /*Two dimensional arrays*/
    int array[3][3] = {{1,2,3},{4,5,6},{7,8,9}};
    for(int i=0; i<3; i++)
    {
        for(int j=0; j<3; j++)
        {
            printf("The values in array is : %d\n",array[i][j]);
        }
    }

    /*Pascals Trianlge*/
    int arr[7][7]={0};
    int row=2, col, i, j;
    arr[0][0] = arr[1][0] = arr[1][1] = 1;
    while(row <= 7)
    {
        arr[row][0] = 1;
        for(col = 1; col <= row; col++)
        {
            arr[row][col] = arr[row-1][col-1] + arr[row-1][col];
        }
        row++;
    }

    for(i=0; i<7; i++)
    {
        printf("\n");
        for(j=0; j<=i; j++)
        {
            printf("\t %d", arr[i][j]);
        }
    }


    return 0;
}
