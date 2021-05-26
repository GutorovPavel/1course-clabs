#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

#define N 80

typedef struct node
{
    char data[N];
    struct node* left;
    struct node* right;
} Node;

void AddNode(char data[], Node** node);
void LeftOrder(Node* node);
int Palindrom(char data[]);
int checker(char data[]);

int main()
{
    char buffer[N];
    int check = 1;
    int count = 0;
    Node* root = NULL;
    printf("Enter words (to stop enter end, word length < 80) : \n");
    while (check == 1)
    {
        gets(buffer);
        int output = checker(buffer);
        int length = strlen(buffer);
        while (output == 0 || length > 80)
        {
            printf("Wrong output, please try again : \n");
            gets(buffer);
            output = checker(buffer);
            length = strlen(buffer);
        }
        if (strcmp(buffer, "end") == 0)
        {
            break;
        }
        AddNode(buffer, &root);
    }
    printf("Palindromes : \n");
    LeftOrder(root);
    getchar();
    return 0;
}

void AddNode(char data[], Node** node)
{
    if (*node == NULL)
    {
        *node = (Node*)calloc(1, sizeof(Node));
        int len = strlen(data);
        for (int i = 0; i < len; i++)
        {
            (*node)->data[i] = data[i];
        }
        (*node)->left = (*node)->right = NULL;
    }
    else
    {
        int len1, len2, check1 = 0, check2 = 0, check3 = 0;
        len1 = strlen(data);
        len2 = strlen((*node)->data);
        if (len1 > len2)
        {
            for (int i = 0; i < len2; i++)
            {
                if (data[i] > (*node)->data[i])
                {
                    check1 = 1;
                    break;
                }
                else if (data[i] < (*node)->data[i])
                {
                    check2 = 1;
                    break;
                }
                else
                {
                    check3++;
                    continue;
                }
            }
            if (check3 == len2)
            {
                check3 = 1;
            }
        }
        else
        {
            for (int i = 0; i < len1; i++)
            {
                if (data[i] > (*node)->data[i])
                {
                    check1 = 1;
                    break;
                }
                else if (data[i] < (*node)->data[i])
                {
                    check2 = 1;
                    break;
                }
                else
                {
                    check3++;
                    continue;
                }
            }
            if (check3 == len1)
            {
                check3 = 1;
            }
        }
        if (check2 == 1)
        {
            AddNode(data, &(*node)->left);
        }
        else if (check1 == 1)
        {
            AddNode(data, &(*node)->right);
        }
        else if (check3 == 1)
        {
            AddNode(data, &(*node)->left);
        }
        else
        {
            puts("There is such element in the tree");
        }
    }
}

void LeftOrder(Node* node)
{
    if (node->left)
    {
        LeftOrder(node->left);
    }
    if (Palindrom(node->data) == 1)
    {
        puts(node->data);
    }
    if (node->right)
    {
        LeftOrder(node->right);
    }
}

int Palindrom(char data[])
{
    int len = strlen(data);
    int mid, res;
    int check = 0;
    mid = len / 2;
    for (int i = 0; i < mid; i++)
    {
        if (data[i] == data[len - 1 - i])
        {
            check++;
        }
    }
    if (check == mid)
    {
        res = 1;
    }
    else
    {
        res = 0;
    }
    return res;
}

int checker(char data[])
{
    int len = strlen(data);
    int res;
    int check = 0;
    for (int i = 0; i < len; i++)
    {
        if ((data[i] <= 'z' && data[i] >= 'a') || (data[i] <= 'Z' && data[i] >= 'A'))
        {
            check++;
        }
    }
    if (data[0] == '\0')
    {
        res = 0;
    }
    else if (check == len)
    {
        res = 1;
    }
    else
    {
        res = 0;
    }
    return res;
}