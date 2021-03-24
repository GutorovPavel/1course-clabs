#include <stdio.h>
#include <math.h>

void check_int(float x)
{
	int result_of_scan = 0;
	char ch;
	while (1)
	{
		result_of_scan = scanf_s("%f%c", &x, &ch);
		if (result_of_scan != 2 || ch != '\n')
		{
			while (getchar() != '\n');
			printf("Invalid input, try again: \n");
		}
		else
			break;
	}
};

int Number(float x, float e)
{
	float value = sin(x);
	float a = x;
	float sum = x;
	int n = 2;
	while (fabs(value - sum) >= e) 
	{		a *= (-1) * pow(x,2) / ((2 * (float)n - 2) * (2 * (float)n - 1));
		sum += a;
		n++;
	}
	return n;
}

int main()
{
	float x, e;
	int n;

	printf("Enter x: ");
	check_int(x);

	printf("Enter accuracy: ");
	check_int(e);
	
	n = Number(x, e);
	printf("%d\n", n);
	return 0;
}