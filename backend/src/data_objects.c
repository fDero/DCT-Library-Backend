
#include "data_objects.h"

void account_init(
    account_t *account, int id, const char *name,
    const char *surname, const char *email, const char* password
){
    account->account_id = id;
    alloc_and_strcpy(&(account->name), name);
    alloc_and_strcpy(&(account->surname), surname);
    alloc_and_strcpy(&(account->email), email);
    alloc_and_strcpy(&(account->password), password);
}

void book_init(
    book_t *book, int id, const char *title, const char *author,
    const char *publisher, const char *genres,
    const timestamp_t *release_date, int total_copies
){
    book->book_id = id;
    alloc_and_strcpy(&(book->title), title);
    alloc_and_strcpy(&(book->author), author);
    alloc_and_strcpy(&(book->publisher), publisher);
    alloc_and_strcpy(&(book->genres), genres);
    book->release_date = *release_date;
    book->total_copies = total_copies;
}

void loan_init(
    loan_t *loan, int id, const timestamp_t *starting_time,
    const timestamp_t *ending_time, int account_id, int book_id
){
    loan->loan_id = id;
    loan->starting_time = *starting_time;
    loan->ending_time = *ending_time;
    loan->account_id = account_id;
    loan->book_id = book_id;
}

void account_destroy(account_t *account) {
	if (account == NULL) return;
    free(account->name);
    free(account->surname);
    free(account->email);
    free(account->password);
    free(account);
}

void book_destroy(book_t *book) {
	if (book == NULL) return;
    free(book->title);
    free(book->author);
    free(book->publisher);
    free(book->genres);
    free(book);
}

void loan_destroy(loan_t *loan) { free(loan); }

void account_array_init(account_array_t *array, size_t size) {
    array->size = size;
    array->storage = (account_t *)malloc(sizeof(account_t) * (size));
}

void book_array_init(book_array_t *array, size_t size) {
    array->size = size;
    array->storage = (book_t *)malloc(sizeof(book_t) * (size));
}

void loan_array_init(loan_array_t *array, size_t size) {
    array->size = size;
    array->storage = (loan_t *)malloc(sizeof(loan_t) * (size));
}

void account_array_destroy(account_array_t *array) {
	if (array == NULL) return;
    for (int i = 0; i < array->size; i++) {
        free(array->storage[i].password);
        free(array->storage[i].name);
        free(array->storage[i].surname);
        free(array->storage[i].email);
    }
    free(array->storage);
    free(array);
}

void book_array_destroy(book_array_t *array) {
		if (array == NULL) return;
    for (int i = 0; i < array->size; i++) {
        free(array->storage[i].title);
        free(array->storage[i].author);
        free(array->storage[i].publisher);
        free(array->storage[i].genres);
    }
    free(array->storage);
    free(array);
}

void loan_array_destroy(loan_array_t *array) {
		if (array == NULL) return;
    free(array->storage);
    free(array);
}
