#include "main.h"
#include <assert.h>

void testing_module()
{
	assert(module(1, 1) == 1,4142136);
	assert(module(1, 1) == 2);
}

void testing_argument()
{
	assert(argument(1, 1) == 0.7853982);
	assert(argument(1, 1) == 2);
}

#undef main
int main()
{
	testing_module();
	testing_argument();
}