#include <assert.h>
#include "main.h"

void test_maths()
{
	assert(maths(2) == 4);
}

#undef main
int main()
{
	test_maths();
	return 0;
}