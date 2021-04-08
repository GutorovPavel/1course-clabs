#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <time.h>
#include <stdbool.h>

void CheckInt(int& n)
{
    int result_of_scan = 0;
    char ch;
    while (1)
    {
        result_of_scan = scanf_s("%d%c", &n, &ch);
        if (result_of_scan != 2 || ch != '\n')
        {
            while (getchar() != '\n');
            printf("Invalid input, try again: \n");
        }
        else
            break;
    }
};

void Input(int& n, int& m)
{
    printf("Input the map size:\n");
    CheckInt(n);
    CheckInt(m);

    if (n < 5 && m < 5)
    {
        printf("Invalid input, one of ur input should be >= 5\n");
        system("cls");
        Input(n, m);
    }
}

int CheckSize(int &n, int &m, int &check)
{
    if (n >= 5 || m >= 5)
    {
        printf("Size is valid...\n");
        check++;
        return check;
    }
}

int main()
{
    srand(time(NULL));
    int n = 0, m = 0, check = 0;
    Input(n, m);
    CheckSize(n, m, check);

    printf("\n");

    int** map = (int**)malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++)
        map[i] = (int*)malloc(m * sizeof(int));

    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            map[i][j] = rand() % 2;

    for (int i = 0; i < n; i++, putchar('\n'))
        for (int j = 0; j < m; j++)
            printf(" %d", map[i][j]);

    printf("\n");

    bool win = false;
    for (int i = 0; i < n - 4; i++)
        for (int j = 0; j < m - 4; j++)
        {
            bool now = true;
            for (int q = 0; q < 5; q++)
            {
                if (map[i + q][j] == 0)
                    now = false;
            }
            if (now)
                win = true;
            now = false;

            for (int q = 0; q < 5; q++)
            {
                if (map[i][j + q] == 0)
                    now = false;
            }
            if (now)
                win = true;
            now = false;

            for (int q = 0; q < 5; q++)
            {
                if (map[i + q][j + q] == 0)
                    now = false;
            }
            if (now)
                win = true;
        }
    for (int i = 0; i < n - 4; i++)
        for (int j = 5; j > m; j--)
        {
            bool now = true;
            for (int q = 0; q < 5; q++)
            {
                if (map[i + q][j - q] == 0)
                    now = false;
            }
            if (now)
                win = true;
        }
    if (win)
    {
        printf("Krestiki win!\n");
    }
    else printf("Krestiki loose...\n");

    return 0;
}