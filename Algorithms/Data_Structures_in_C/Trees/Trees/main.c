#include <stdio.h>
#include <stdlib.h>
typedef struct Tree
{
    struct Tree * left;
    int value;
    struct Tree * right;
}Tree;

Tree * createTree()
{
    int value;
    printf("Please enter the value for the root node : \n");
    scanf("%d", &value);
    Tree * root = (Tree *) malloc(sizeof(Tree));
    root->left = NULL;
    root->right = NULL;
    root->value = value;
    return root;
}

void insertLeft(Tree * root)
{
    Tree * traverse, * head;
    Tree * node = (Tree *) malloc(sizeof(Tree));
    traverse = root;
    head = root;
    int value;
    printf("Please enter the value for the root node : \n");
    scanf("%d", &value);
    node->value = value;
    node->left = NULL;
    node->right = NULL;
    while(root->left != NULL)
    {
        traverse = traverse->left;
        if(traverse->left == NULL)
        {
            traverse->left = node;
        }
        else if(traverse->right == NULL)
        {
            traverse->right = node;
        }
        else
        {
            root = root->left;
        }
    }
    if(root->left == NULL && root->right == NULL)
    {
        root->left = node;
    }
//    else
//    {
//        root->right = node;
//    }
}

void insertRight(Tree * root)
{
    Tree * node = (Tree *) malloc(sizeof(Tree));
    int value;
    printf("Please enter the value for the root node : \n");
    scanf("%d", &value);
    node->value = value;
    node->left = NULL;
    node->right = NULL;
    while(root->right != NULL)
    {
        root = root->right;
    }
    if(root->left == NULL && root->right == NULL)
    {
        root->right = node;
    }
    else
    {
        root->left = node;
    }
}

void  inorderDisplayTree(Tree * root)
{
    Tree * node = (Tree *) malloc(sizeof(Tree));
    node = root;

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

int main()
{
    int choice,traverse;
    char cont='Y';

    Tree * root;
    printf("Welcome to the world of trees !");
    while(cont =='Y' || cont =='y')
    {
        printf("Please select one of the options : \n");
        printf("1. Create tree\n2. Insert a left node\n3. Insert a right node\n4. Traverse tree\n5. Exit\n");
        scanf("%d",&choice);

        switch(choice)
        {
            case 1:
                root = createTree();
                break;

            case 2:
                insertLeft(root);
                break;

            case 3:
                insertRight(root);
                break;

            case 4:
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

            default:
                break;
        }
        printf("Do you wish to continue ? (y/n)");
        scanf(" %c", &cont);
    }
}
