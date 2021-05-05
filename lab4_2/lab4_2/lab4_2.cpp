#include <stdio.h>
#define size 10000
#define _CRT_SECURE_NO_WARNINGS

int main()
{
	char buffer[size];
	FILE* f;
	f = fopen();
	if (!f)
		return;
	while (fgets(buffer, size, f) != NULL)
	{
		printf(buffer);
	}
	fclose(f);
	return 0;
}
