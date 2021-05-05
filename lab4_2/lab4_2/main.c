#define _CTR_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>
#include <malloc.h>
#include "main.h"

int main()
{
    FILE* f, *write;
    char temp1[100], temp2[100], * text;
    int i, j, k, l;
    int count;
    int fsize;
    f = fopen("dict.txt", "r");

    if (f == NULL)
    {
        printf("Failed to open file!");
        return 0;
    }

    fseek(f, 0, SEEK_END);
    fsize = ftell(f) + 1;
    text = (char*)malloc(fsize * sizeof(char));

    if (text == NULL)
    {
        printf("Not enough memory!");
        return 0;
    }

    fseek(f, 0, SEEK_SET);
    j = 0;

    while (1)
    {
        if (fgets(temp1, 100, f) == NULL)
        {
            if (!feof(f))
            {
                printf("Error reading from file");
                fclose(f);
                return 0;
            }
            else
            {
                text[j++] = ' ';
                text[j] = '\0';
                break;
            }
        }
        else
        {
            for (i = 0; i < StrLen(temp1); i++)
            {
                if (temp1[i] != '\n')
                {
                    text[j++] = temp1[i];
                }
                else
                {
                    text[j++] = ' ';
                }
            }
        }
    }

    fclose(f);
    printf(text);
    write = fopen("write.txt", "w");

    if (write == NULL)
    {
        printf("Failed to open/create file!");
        return 0;
    }

    k = 0;
    count = 1;

    for (i = 0; i < StrLen(text); i++)
    {
        if (text[i] != ' ' && text[i] != '.' && text[i] != ',' && text[i] != '!' && text[i] != '?' && text[i] != ':' && text[i] != ';' && text[i] != '(' && text[i] != ')')
        {
            temp1[k++] = text[i];
        }
        else
        {
            temp1[k] = '\0';
            k = 0;
            for (j = i + 1; j < StrLen(text); j++)
            {
                if (text[j] != ' ')
                {
                    temp2[k++] = text[j];
                }
                else
                {
                    temp2[k] = '\0';
                    k = 0;
                    if (Compare(temp1, temp2))
                    {
                        count++;
                        j -= StrLen(temp2);
                        for (l = 0; l < StrLen(temp2) + 1; l++)
                        {
                            text = Del(text, j, fsize--);
                        }
                    }
                }
            }
            if (temp1[0] != '\0')
            {
                fprintf(write, "%s - %d\n", temp1, count);
            }
            count = 1;
        }
    }
    fclose(write);
    return 0;
}

int StrLen(char* str)
{
    int res;
    res = 0;

    while (str[res] != '\0')
    {
        res++;
    }
    return res;
}

char* Del(char* str, int index, int size)

{
    char* res;
    int i, j;

    if (size > 0)
    {
        size--;
    }
    res = (char*)malloc(size * sizeof(char));
    if (res == NULL)
    {
        printf("Not enough memory!");
        exit(0);
    }
    for (i = 0, j = 0; i < StrLen(str); i++)
    {
        if (i != index)
        {
            res[j] = str[i];
            j++;
        }
    }
    res[j] = '\0';
    return res;
}

bool Compare(char* str1, char* str2)
{
    int i;
    if (StrLen(str1) == StrLen(str2))
    {
        for (i = 0; i < StrLen(str1); i++)
        {
            if (str1[i] != str2[i])
            {
                return false;
            }
        }
        return true;
    }
    else
    {
        return false;
    }
}