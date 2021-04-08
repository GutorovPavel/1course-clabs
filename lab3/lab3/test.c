#include <assert.h>
#include "main.h"

void testing()
{
	assert(CheckSize(2, 1, 0) == 0);
	assert(CheckSize(6, 5, 0) == 1);
}

#undef main
int main()
{
	testing();
}