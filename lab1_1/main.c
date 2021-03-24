#include <stdio.h>
#include <math.h>
#include <locale.h>

int check_int(int n)
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
	return n;
}

int maths(int k)
{
	int length = 0, a = 0, number = 0;				
	while (length < k)
	{
		a++;
		int p = pow(a, 2);
		number = p;
		while (p != 0)
		{
			p /= 10;
			length++;
		}
	}
	if (length > k)
	{
		while (length != k)
		{
			number /= 10;
			length--;
		}
	}
	return number;
}

int main()
{
	printf("Enter the number of the dijit in sequence: ");
	int k = 0;
	k = check_int(k);
	int number = maths(k);
	printf("the digit: %d", number % 10);
	return 0;
}