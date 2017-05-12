#include<stdio.h>
#include<stdlib.h>

/*-------------------------------------------------------------------------------------------------------------*/
    //This is a program to implement the basic tree data structure called Binary Search Tree and operations
    //related to it. This is the first iteration and may contain errors in it.
/*-------------------------------------------------------------------------------------------------------------*/
typedef struct Tree
{
    struct Tree * left;
    int value;
    struct Tree * right;
}Tree;

Tree * createTree(Tree * rootNode)
{
    int value;
    printf("Please enter the value for the root node : \n");
    scanf("%d", &value);
    if(rootNode == NULL)
    {
        Tree * root = (Tree *) malloc(sizeof(Tree));
        root->left = NULL;
        root->right = NULL;
        root->value = value;
        return root;
    }
    else
    {
        printf("The root node is already created ! Can not create again !\n");
        return rootNode;
    }
}

void insertNodeIterative(Tree * root)
{
    Tree * traverse, *keepTrack;
    Tree * node = (Tree *) malloc(sizeof(Tree));
    traverse = keepTrack = root;
    int value;
    printf("Please enter the value for the node : \n");
    scanf("%d", &value);
    node->value = value;
    node->left = NULL;
    node->right = NULL;

    while(traverse != NULL)
    {
        if(node->value <= traverse->value)
        {
            keepTrack = traverse;
            traverse = traverse->left;
        }
        else
        {
            keepTrack = traverse;
            traverse = traverse->right;
        }
    }

    if(node->value <= keepTrack->value)
    {
        keepTrack->left = node;
    }
    else
    {
        keepTrack->right = node;
    }
}

void insertNodeRecursive(Tree * root, int value)
{

}

void binarySearch(Tree * root)
{
    int value;
    printf("Enter the value to search for : \n");
    scanf("%d", &value);
    while(root != NULL)
    {
        if(root->value == value)
        {
            printf("The value is found! The value is : %d\n", root->value);
            return;
        }
        else if(root->value >= value)
        {
            root = root->left;
        }
        else
        {
            root = root->right;
        }
    }
    printf("The value being searched for is not available in the tree !\n");
}

void  inorderDisplayTree(Tree * root)
{
    Tree * node = (Tree *) malloc(sizeof(Tree));
    node = root;

    if(node == NULL)
    {
        printf("Tree is empty! \n");
        return;
    }

    if(node->left == NULL && node->right == NULL)
    {
        printf("The value in the node is : %d\n", node->value);
    }
    else
    {
        if(node->left != NULL)
            inorderDisplayTree(node->left);

        printf("The value in the node is : %d\n", node->value);

        if(node->right != NULL)
            inorderDisplayTree(node->right);
    }
}

void  preorderDisplayTree(Tree * root)
{
    Tree * node = (Tree *) malloc(sizeof(Tree));
    node = root;

    if(node == NULL)
    {
        printf("Tree is empty! \n");
        return;
    }
    if(node->left == NULL && node->right == NULL)
    {
        printf("The value in the node is : %d\n", node->value);
    }
    else
    {
        printf("The value in the node is : %d\n", node->value);

        if(node->left != NULL)
            preorderDisplayTree(node->left);

        if(node->right != NULL)
            preorderDisplayTree(node->right);
    }
}

void  postorderDisplayTree(Tree * root)
{
    Tree * node = (Tree *) malloc(sizeof(Tree));
    node = root;

    if(node == NULL)
    {
        printf("Tree is empty! \n");
        return;
    }
    if(node->left == NULL && node->right == NULL)
    {
        printf("The value in the node is : %d\n", node->value);
    }
    else
    {
        if(node->left != NULL)
            postorderDisplayTree(node->left);

        if(node->right != NULL)
            postorderDisplayTree(node->right);

        printf("The value in the node is : %d\n", node->value);
    }
}

Tree * findMin(Tree * root)
{
    while(root->left != NULL)
    {
        root = root->left;
    }
    return root->value;
}

Tree * deleteNode(Tree * root, int value)
{
    if(root == NULL)
    {
        printf("Tree is empty ! Nothing to delete\n");
        return root;
    }
    else if(root->value > value)
    {
        root->left = deleteNode(root->left, value);
    }
    else if(root->value < value)
    {
        root->right = deleteNode(root->right, value);
    }
    else
    {
        if(root->left == NULL && root->right == NULL)
        {
            free(root);
            root = NULL;
            return root;
        }
        else if(root->left == NULL && root->right != NULL)
        {
            Tree * temp = (Tree *) malloc(sizeof(Tree));
            temp = root->right;
            root->value = temp->value;
            free(temp);
            return root;
        }
        else if(root->left != NULL && root->right == NULL)
        {
            Tree * temp = (Tree *) malloc(sizeof(Tree));
            temp = root->left;
            root->value = temp->value;
            free(temp);
            return root;
        }
        else
        {
            //Find the minimum of the nodes right child
            Tree * temp = (Tree *) malloc(sizeof(Tree));
            temp = findMin(root->right);
            root->value = temp->value;
            root->right = deleteNode(root->right, temp->value);
            return root;
        }
    }
}

int main()
{
    int choice,traverse, value;
    char cont='Y';
    Tree * root = NULL;
    printf("Welcome to the world of Binary Search Trees !\n");
    while(cont =='Y' || cont =='y')
    {
        printf("Please select one of the options : \n");
        printf("1. Create tree\n2. Insert a node\n3. Traverse tree\n4. Search a value in the tree\n5. Delete a node\n6. Exit\n");
        scanf("%d",&choice);

        switch(choice)
        {
            case 1:
                root = createTree(root);
                break;

            case 2:
                printf("Select the kind of insertion : \n");
                printf("1. Iterative\n2. Recursive\n");
                scanf("%d", &traverse);
                switch(traverse)
                {
                    case 1:
                        insertNodeIterative(root);
                        break;

                    default
                        int value;
                        printf("Please enter the value for the node : \n");
                        scanf("%d", &value);
                        insertNodeRecursive(root, value);
                }
                break;

            case 3:
                printf("Select the kind of traversal : \n");
                printf("1. Preorder \n2. Inorder\n3. Postorder\n");
                scanf("%d", &traverse);
                switch(traverse)
                {
                    case 1:
                        preorderDisplayTree(root);
                        break;

                    case 2:
                        inorderDisplayTree(root);
                        break;

                    default:
                        postorderDisplayTree(root);
                }
                break;

            case 4:
                binarySearch(root);
                break;

            case 5:
                printf("Please enter the number to be deleted : \n");
                scanf("%d", &value);
                root = deleteNode(root, value);
                break;

            default:
                break;
        }
        printf("Do you wish to continue ? (y/n)");
        scanf(" %c", &cont);
    }
    return 0;
}

