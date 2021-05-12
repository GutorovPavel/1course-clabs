#include "main.h"
#include <assert.h>
#include <stdio.h>

int TestPalindrom() 
{
	char* str = (char*)malloc(6 * sizeof(char));
	CheckPtr(str);
	str = "abba\0";
	assert(Palindrom(&str, 4) == 1);
	str = "abcabc\0";
	assert(Palindrom(&str, 6) == 0);
}

#undef main
int main() {
	TestPalindrom();
	return 0;
}