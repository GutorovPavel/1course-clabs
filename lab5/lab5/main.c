#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

#define BUFFER_SIZE 255

void CheckPtr(void* ptr)
{
    if (ptr == NULL)
    {
        printf("Failed. The program has crashed.\n");
        exit(-1);
    }
}

void CopyFromBuffer(char** buffer, char*** str, int* const length, int* const n)
{
    **str = (char*)realloc(**str, (*n + *length + 1) * sizeof(char));
    CheckPtr(str);

    int i;
    for (i = 0; i < *length; i++)
    {
        (**str)[(*n)++] = (*buffer)[i];
    }

    *length = 0;

    return;
}

int ReadStr(char** str)
{
    char h;
    int length = 0, n = 0;

    char* buffer = (char*)malloc(BUFFER_SIZE * sizeof(char));
    CheckPtr(buffer);

    while ((h = getchar()) != '\n')
    {
        if (!((h >= 'A' && h <= 'Z') || (h >= 'a' && h <= 'z')))
        {
            continue;
        }
        buffer[length++] = h;
        if (length == BUFFER_SIZE)
        {
            CopyFromBuffer(&buffer, &str, &length, &n);
        }
    }
    if (length != 0)
    {
        CopyFromBuffer(&buffer, &str, &length, &n);
    }
    (*str)[n] = '\0';

    free(buffer);

    return n;
}

typedef struct stack
{
    struct stack* l, * r;
    char symb;
} Stack;

short Palindrom(char** str, int n)
{
    int i;
    short ans = 1;
    Stack* ptr = (Stack*)malloc(sizeof(Stack));
    CheckPtr(ptr);

    ptr->l = NULL;
    ptr->r = NULL;
    ptr->symb = (*str)[0];

    for (i = 1; i < n / 2; i++)
    {
        ptr->r = (Stack*)malloc(sizeof(Stack));
        CheckPtr(ptr->r);

        ptr->r->l = ptr;
        ptr->r->r = NULL;
        ptr->r->symb = (*str)[i];

        ptr = ptr->r;
    }

    int m = n / 2;
    if (n % 2 == 1)
    {
        m++;
    }

    for (i = m; i < n; i++)
    {
        if (ptr->symb != (*str)[i])
        {
            ans = 0;
        }

        if (ptr->l == NULL)
        {
            free(ptr);
        }
        else
        {
            ptr = ptr->l;
            free(ptr->r);
        }
    }
    return ans;
}


int main()
{
    char* str = NULL;
    int n = ReadStr(&str);

    if (Palindrom(&str, n) == 1)
    {
        printf("The string is a palindrome.\n");
    }
    else
    {
        printf("The string isn't a palindrome.\n");
    }

    free(str);
    return 0;
}
