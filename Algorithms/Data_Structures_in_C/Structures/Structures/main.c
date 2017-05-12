#include <stdio.h>
#include <stdlib.h>
typedef union test
{
    int x;
    int y;
}test;

typedef struct student
{
    int id;
    char address[20];
    float fees;
    struct tests; //This is a valid structure because it is an anonymous structure.
   // struct student tests; //Structure can not have the same structure inside its own declaration. This is invalid declaration.
    test test1; // Union is allowed in structure definition, but it means that it can be used to store only one value at a time;
    char name[]; //Array without a size can be allowed to be a part of the structure definition as long as they are in the end of the structure definition
}student;

void readData(student studPtr[])
{
    for(int i=0; i<3; i++)
    {
        studPtr[i].id = i+1;
        studPtr[i].fees = 10000;
        printf("Please enter the name of the student : \n");
        fgets(studPtr[i].name,20,stdin);
        printf("Please enter the address : \n");
        fgets(studPtr[i].address,20,stdin);
    }

    //For an array of sturcture pointers referenced by an array of structure pointers
//    studPtr[3].id = 4;
//    studPtr[3][0].fees = 10000;
//    printf("Please enter the name of the student : \n");
//    fgets(studPtr[3][0].name,20,stdin);
//    printf("Please enter the address : \n");
//    fgets(studPtr[3][0].address,20,stdin);
}

void displayPtr(student *stud)
{
    printf("The name of the student is : %s",(*(stud+0)).name);
    printf("The address of the student is : %s",(*(stud+0)).address);
    printf("The fees of the student is : %f\n",(*(stud+0)).fees);

    printf("Ptr - The name of the student is : %s",(stud+0)->name);
    printf("Ptr - The address of the student is : %s",(stud+0)->address);
    printf("Ptr - The fees of the student is : %f",(stud+0)->fees);
}

void display(student *stud)
{
    printf("The name of the student is : %s",(*stud).name);
    printf("The address of the student is : %s",(*stud).address);
    printf("The fees of the student is : %f\n",(*stud).fees);

    printf("Ptr - The name of the student is : %s",stud->name);
    printf("Ptr - The address of the student is : %s",stud->address);
    printf("Ptr - The fees of the student is : %f",stud->fees);
}

int main()
{
    /*Passing structures around*/
//    student stud;
//    stud = readData(stud);
//    display(stud);

    /*Array of pointers to structures*/
/*
    student *studPtr[3];
    student stud1;
    student stud2;
    student stud3;
    student stud4[2];

    studPtr[0] = &stud1;
    studPtr[1] = &stud2;
    studPtr[2] = &stud3;
    studPtr[3] = &stud4;

    readData(studPtr);
    displayPtr(studPtr);
*/ //Temporary comment, remove after below work is done

    /*Pointers and structures*/
//    student stud;
//    student *studPntr;
//    stud = readData(stud);
//    studPntr = &stud;
//    display(studPntr);

    /*Pointer to an array of structures*/
//    student studArray[2];
//    student *studPointer = studArray;
//
//    strcpy(studPointer->address,"Arlington");
//
//    printf("The value in the array location 0 is : %s",studPointer->address);
//
//    strcpy((studPointer+1)->address,"Dallas");
//
//    printf("The value in the array location 1 is : %s",(studPointer+1)->address);
//
//    studPointer++;
//
//    printf("The value in the array location 1 is : %s",(studPointer)->address);

//    student studentArray[2];
//    student *studentPointer[2];
//    studentPointer[0] = studentArray;
//    studentPointer[1] = studentArray;
//
//    strcpy(studentPointer[0]->address,"Arlington");
//
//    printf("The value in the array location 0 is : %s",studentPointer[0]->address);
//
//    strcpy((studentPointer[0]+1)->address,"Dallas");
//
//    printf("The value in the array location 1 is : %s",(studentPointer[0]+1)->address);
//
//
//    //strcpy(studentPointer[1]->address,"Arlington");
//
//    printf("The value in the array location 0 is : %s",studentPointer[1]->address);
//
//    //strcpy((studentPointer[1]+1)->address,"Dallas");
//
//    printf("The value in the array location 1 is : %s",(studentPointer[1]+1)->address);

    /*Array of structures*/
//      typedef struct classes
//      {
//        int classid;
//        student stud;
//        char subject[20];
//      }classes;
//    classes class1[10];
//
//    int i = 0;
//    char cont='Y';
//    while((i<10) && (cont=='Y'))
//    {
//        class1[i].stud.id = i+1;
//        class1[i].classid=i+1;
//        class1[i].stud.fees = 10000;
//        printf("Please enter the name of the student : \n");
//        scanf(" %s", &class1[i].stud.name);
//        printf("Please enter the address : \n");
//        scanf(" %s", &class1[i].stud.address);
//        printf("Please enter the name of the subject : \n");
//        scanf(" %s", &class1[i].subject);
//        i++;
//        printf("Do you want to continue : \n");
//        scanf(" %c", &cont);
//    }
//
//    for(int j=0; j<i; j++)
//    {
//        printf("The name of the student is : %s\n", class1[j].stud.name);
//        printf("The name of the student is : %s\n", class1[j].subject);
//    }
    /*This is an introduction to structures*/
//    class1[0].stud.id = 1;
//    // class1.stud.name = "Nitin Kanwar"; // This will not work because the array here is non assignable and non initilizable
//    strcpy(class1[0].stud.name,"Nitin Kanwar");
//    strcpy(class1[0].stud.address,"Arlington");
//    class1[0].stud.fees = 10307;
//    strcpy(class1[0].subject,"Algorithms");
//
//    printf("The name of the student is : %s\n", class1[0].stud.name);
//    printf("The name of the class is : %s\n", class1[0].subject);
//----------------------------------------------------------------------------------------------------------------------------------------------------------------
    /*Union*/

    test test1;
    test1.x = 4; //Even though x is given a separate value and y is given a separate value, in reality y overwrites the value in x because in a union
    //both x and y share the same memory location.
    test1.y = 5;

    printf("The value of x is : %d", test1.x);
    printf("The value of y is : %d", test1.y);
    return 0;
}
