#include "main.h"
#include <assert.h>

void ChangePlusTest()
{
	assert(ChangePlus(0, '5', 2) == 5);
}

void ChangeMinusTest()
{
	assert(ChangeMinus(0, '2', 1) == 2);
}

#undef main
int main()
{
	ChangePlusTest();
	ChangeMinusTest;
	return 0;
}