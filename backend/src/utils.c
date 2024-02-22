#include "utils.h"

void alloc_and_strcpy(char* *destination, const char* source)
{
	*destination = (char *)malloc(sizeof(char) * strlen(source) + 1);
	strcpy(*destination, source);
}