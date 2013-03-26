#include "str.h"

#include <stdlib.h>
#include <string.h>

char* str__dup(const char* src)
{
	char* dst;

	if(src == NULL)
		return NULL;

	dst = (char*)malloc(strlen(src) + 1);
	if(dst != NULL)
		strcpy(dst, src);

	return dst;
}
