#include "main.h"
#include <assert.h>

void StrLenTest()
{
	int len;
	len = Strlen("qwertyuiopas");
	assert(len == 12);
}

void DelTest()
{
	char* str;
	str = Del(" qwertyuiopas", 0, 12);
	assert(Compare(str, "qwertyuiopas"));
}

#undef main
int main()
{
	StrLenTest();
	DelTest();
	return 0;
}