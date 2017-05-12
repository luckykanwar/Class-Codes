#include <stdio.h>
#include <stdlib.h>
int N = 100;

int main()
{
    /*Array Traversal*/
    int array[5] = {1,3,5,7,9}, arrayTwo[5] = {2,4,6,8,10}, i = 0;
    int arrayMerged[N];
    char cnt = 'Y';
//    do{
//        printf("Please enter a number into the array :\n");
//        scanf("%d",&array[i++]);
//        printf("Do you want to continue : (Y/N)");
//        scanf(" %c",&cnt);
//    }while(cnt == 'Y');

    /*Merge two arrays */
    printf("The values you entered into the array are :\n");
    for(int j=0; j<5; j++)
    {
        printf("%d\n", array[j]);
    }

    printf("The values you entered into the arrayTwo are :\n");
    for(int j=0; j<5; j++)
    {
        printf("%d\n", arrayTwo[j]);
    }

    for(int j=0; j<5; j++)
    {
        arrayMerged[j] = array[j];
    }

    int k=0;
    for(int j=5; j<10; j++)
    {
        arrayMerged[j] = arrayTwo[k];
        k++;
    }

    printf("The values you entered into the array are :\n");
    for(int j=0; j<10; j++)
    {
        printf("%d\n", arrayMerged[j]);
    }

    /*Merge two sorted arrays to create another sorted array*/
    //First merge the two arrays as is and then sort them in place
    for(int k=0; k<10; k++)
    {
        for(int j=0; j<9; j++)
        {
            if(arrayMerged[j] >= arrayMerged[j+1])
            {
                int temp = arrayMerged[j+1];
                arrayMerged[j+1] = arrayMerged[j];
                arrayMerged[j] = temp;
            }
        }
    }


    printf("The values after sorting the array are :\n");
    for(int j=0; j<10; j++)
    {
        printf("%d\n", arrayMerged[j]);
    }

//    /*Mean of n numbers*/
//    int mean=0;
//    for(int j=0; j<i; j++)
//    {
//        mean = mean + array[j];
//    }
//    mean = mean / i ;
//    printf("The mean of %d number is : %d\n",i,mean);
//
//    /*Smallest number of n numbers*/
//    int small = array[0];
//    for(int j=1; j<i; j++)
//    {
//        if(small >= array[j])
//        {
//            small = array[j];
//        }
//    }
//    printf("The smallest value is : %d\n", small);
//
//    /*Largest number of n numbers*/
//    int large = array[0];
//    for(int j=1; j<i; j++)
//    {
//        if(large <= array[j])
//        {
//            large = array[j];
//        }
//    }
//    printf("The largest value is : %d\n", large);
//
//
//    /*Second largest number of n numbers*/
//    int secondLarge = array[0];
//    for(int j=1; j<i; j++)
//    {
//        if(array[j]!=large)
//        {
//            if(array[j]>secondLarge)
//            {
//                secondLarge = array[j];
//            }
//        }
//    }
//    printf("The second largest value is : %d\n", secondLarge);
//
//    /*Make a number from digits*/
//    int number =0;
//    for(int j =0; j<i; j++)
//    {
//        number = number + (array[j] * pow(10,j));
//    }
//    printf("The final number is : %d\n",number);
//
//    /*Find duplicates*/
//    int arrayDuplicates[N], n=0;
//    for(int j=0; j<i; j++)
//    {
//        for(int k=0; k<i; k++)
//        {
//            if((array[j] == array[k]) && (j!=k))
//            {
//                arrayDuplicates[n] = array[j];
//                n++;
//            }
//        }
//    }
//
//    printf("The duplicate values in the array are :\n");
//    for(int j=0; j<n; j++)
//    {
//        printf("%d", arrayDuplicates[j]);
//    }
//
//    /*Insert a new number at a said location in an array*/
//    int position, value, tempLocation = i,j;
//    printf("Please enter the position at which you want to add the new number : \n");
//    scanf("%d", &position);
//    printf("Please enter the new number : \n");
//    scanf("%d", &value);
//
//    while(tempLocation>=position)
//    {
//        j=tempLocation-1;
//        array[tempLocation] = array[j];
//        tempLocation--;
//    }
//    array[position-1] = value;
//    printf("The values you entered into the array are :\n");
//    for(int j=0; j<=i; j++)
//    {
//        printf("%d\n", array[j]);
//    }
//    i = i+1;
//
//    /*Insert a new number by finding its right location in the array which is sorted in ascending order*/
//    printf("Please enter the new number : \n");
//    scanf("%d", &value);
//    position=0;
//    for(int j=0; j<=i; j++)
//    {
//        if(array[j] <= value)
//        {
//            position ++;
//        }
//    }
//    tempLocation = i;
//    while(tempLocation>=position)
//    {
//        j=tempLocation-1;
//        array[tempLocation] = array[j];
//        tempLocation--;
//    }
//    array[position-1] = value;
//    printf("The values you entered into the array are :\n");
//    for(int j=0; j<=i; j++)
//    {
//        printf("%d\n", array[j]);
//    }
//    i = i+1;


//    /*Deleting a number from an array at a given position*/
//    int position;
//    printf("Please enter the position from which you want to delete the number : \n");
//    scanf("%d", &position);
//    for(int j=position-1; j<i; j++)
//    {
//        array[j] = array[j+1];
//    }
//    i = i-1;
//    printf("The values you entered into the array are :\n");
//    for(int j=0; j<i; j++)
//    {
//        printf("%d\n", array[j]);
//    }

//    /*Deleting a number from an array of ascending numbers*/
//    int value;
//    printf("Please enter the number to delete: \n");
//    scanf("%d", &value);
//    int position=0;
//    for(int j=0;j<i;j++)
//    {
//        if(array[j] <= value)
//        {
//            position = position + 1;
//        }
//    }
//    printf("The position to delete is : %d\n",position);
//    for(int j=position-1; j<i; j++)
//    {
//        array[j] = array[j+1];
//    }
//    i = i-1;
//    printf("The values you entered into the array are :\n");
//    for(int j=0; j<i; j++)
//    {
//        printf("%d\n", array[j]);
//    }

    /*This section just checks for some properties of arrays*/
        /*
        int arrayTest[10];
        printf("The location of array is : %d\n", &arrayTest); //this gives the address of the base location
        printf("The location of array is : %d\n", &arrayTest[0]); //this gives the address of the base location
        printf("The location of array is : %d\n", &arrayTest[1]); //this gives the address of the second location i.e. index 1
        printf("The location of array is : %d\n", &arrayTest[2]); //this gives the address of the third location i.e. index 2
        printf("The location of array is : %d\n", &arrayTest+0); //this gives the address of the base location + (0 * 40 bytes)
        printf("The location of array is : %d\n", &arrayTest+1); //this gives the address of the base location + (1 * 40 bytes), because pointer arithmetic is being applied here
        printf("The location of array is : %d\n", &arrayTest+2); //this gives the address of the base location + (2 * 40 bytes), because pointer arithmetic is being applied here
        printf("The location of array is : %d\n", &arrayTest+3); //this gives the address of the base location + (3 * 40 bytes), because pointer arithmetic is being applied here
        printf("The size of array is : %d\n", sizeof(arrayTest));
        printf("The number of elements in array is : %d\n", sizeof(arrayTest)/sizeof(int));
        */
        /*The base of an array represents the address of the base of the array*/
        int arr[]={1,2,3,4,5};
        printf("\n Address of array = %p %p %p", arr, &arr[0], &arr);
    return 0;
}
