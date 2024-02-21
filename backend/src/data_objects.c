#include "data_objects.h"

void account_destroy(account_t* account) {
	free(account->name);
	free(account->surname);
	free(account->email);
	free(account);
}

void book_destroy(book_t* book) {
	free(book->title);
	free(book->author);
	free(book->publisher);
	free(book);
}

void loan_destroy(loan_t* loan) {
	free(loan);
}

void account_array_init(account_array_t *array, size_t size)
{
	array->size = size;
	array->storage = (account_t *)malloc(sizeof(account_t) * (size));
}

void book_array_init(book_array_t *array, size_t size)
{
	array->size = size;
	array->storage = (book_t *)malloc(sizeof(book_t) * (size));
}

void loan_array_init(loan_array_t *array, size_t size)
{
	array->size = size;
	array->storage = (loan_t *)malloc(sizeof(loan_t) * (size));
}

void account_array_destroy(account_array_t *array) {
	for(int i = 0; i < array->size; i++){
		free(array->storage[i].name);
		free(array->storage[i].surname);
		free(array->storage[i].email);
	}
	free(array->storage);
	free(array);
}

void book_array_destroy(book_array_t *array) {
	for(int i = 0; i < array->size; i++){
		free(array->storage[i].title);
		free(array->storage[i].author);
		free(array->storage[i].publisher);
	}
	free(array->storage);
	free(array);
}

void loan_array_destroy(loan_array_t *array) {
	free(array->storage);
	free(array);
}
