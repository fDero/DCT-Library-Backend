#include "arrays.h"

void account_array_init(account_array_t *array, size_t size)
{
	array->array_size = size;
	array->array_storage = (account_t *)malloc(sizeof(account_t) * (size));
}

void book_array_init(book_array_t *array, size_t size)
{
	array->array_size = size;
	array->array_storage = (book_t *)malloc(sizeof(book_t) * (size));
}

void loan_array_init(loan_array_t *array, size_t size)
{
	array->array_size = size;
	array->array_storage = (loan_t *)malloc(sizeof(loan_t) * (size));
}