#include <assert.h>
#include "main.h"

void testing()
{
	assert(Number(2, 1) == 3);
}

#undef main
int main()
{
	testing();
}