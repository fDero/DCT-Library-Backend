
#ifndef ARRAYS_H
#define ARRAYS_H

#include <stdio.h>
#include <stdlib.h>
#include <postgresql/libpq-fe.h>
#include "tables.h"

struct account_array
{
    account_t *array_storage;
    size_t array_size;
};

struct book_array
{
    book_t *array_storage;
    size_t array_size;
};

struct loan_array
{
    loan_t *array_storage;
    size_t array_size;
};

typedef struct account_array account_array_t;
typedef struct book_array book_array_t;
typedef struct loan_array loan_array_t;

void account_array_init(account_array_t * array, size_t size);
void book_array_init(book_array_t *array, size_t size);
void loan_array_init(loan_array_t *array, size_t size);

#endif