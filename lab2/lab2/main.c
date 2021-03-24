#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <locale.h>

void check_int(int n)
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

void check_float(float n)
{
	float result_of_scan = 0;
	char ch;
	while (1)
	{
		result_of_scan = scanf_s("%f%c", &n, &ch);
		if (result_of_scan != 2 || ch != '\n')
		{
			while (getchar() != '\n');
			printf("Invalid input: \n");
		}
		else
			break;
	}
};

void input(float re, float im)
{
	printf("Please enter the real part: ");
	check_float(re);
	printf("Please enter a imaginary part: ");
	check_float(im);
};

void output_algebra(float re, float im)
{
	printf("\nComplex number in algebraic form : z = %.2f + %.2f*i\n", re, im);
};

int module(float re, float im)
{
	float z = sqrt(pow(re, 2) + pow(im, 2));
	return z;
}

int argument(float re, float im)
{
	float arg = atan(im / re);
	return arg;
}

void output_exponential(float re, float im)
{
	float z = 0;
	z = module(re, im, z);
	printf("\nComplex number module: |z| = %f", z);
	float arg = 0;
	arg = argument(re, im, arg);
	printf("\nComplex number argument: arg = %f", arg);
	printf("\nComplex number in exponential form: z = %.2f * e^(%.2f*%f)\n", z, im, arg);
};

void conj(float re, float im)
{
	printf("\nConjugate number to a given complex: z = %.2f - %.2f*i\n", re, im);
};

void power(float re, float im)
{
	float z = 0;
	z = module(re, im, z);
	float arg = 0;
	arg = argument(re, im, arg);
	printf("\nComplex number in exponential form: z = %.2f * e^(%.2f*%f)", z, im, arg);
	printf("\nEnter a positive integer to the power of which you want to raise this complex: ");
	float p = 0;
	check_float(p);
	printf("\nResult: z^%d = %.2f * e^(%.2f * %f)\n", p, pow(z, p), p * im, arg);
};

int func(int n, float re, float im)
{

	while (n != 6)
	{
		printf("\nEnter the number of function: ");
		check_int(n);

		switch (n)
		{
		case 1:
		{
			output_algebra(re, im);
			break;
		}
		case 2:
		{
			output_exponential(re, im);
			break;
		}
		case 3:
		{
			power(re, im);
			break;
		}
		case 4:
		{
			conj(re, im);
			break;
		}
		case 5:
		{
			system("cls");
			input(re, im);
			printf("\n1. Output the algebraic form of a complex number\n"
				"2. Output the exponential form of a complex number\n"
				"3. Raising a complex number to a positive integer power\n"
				"4. Getting the conjugate of a complex number\n"
				"5. Enter other input\n"
				"6. Exit\n");
			func(n, re, im);
			break;
		}
		case 6:
		{
			return 0;
		}
		default:
			printf("Enter a value between 1 and 6");
			func(n, re, im);
			break;
		}
	}
};

int main()
{
	float re = 0, im = 0;
	setlocale(LC_ALL, "ru");
	input(re, im);
	printf("\n1. Output the algebraic form of a complex number\n"
		"2. Output the exponential form of a complex number\n"
		"3. Raising a complex number to a positive integer power\n"
		"4. Getting the conjugate of a complex number\n"
		"5. Enter other input\n"
		"6. Exit\n");
	int n = 0;
	func(n, re, im);

	return 0;
}