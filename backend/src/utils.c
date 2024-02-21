#include "utils.h"

void alloc_and_strcpy(char* *destination, char* source)
{
	*destination = (char *)malloc(sizeof(char) * strlen(source));
	strcpy(*destination, source);
}