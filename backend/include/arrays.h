
#ifndef ARRAYS
#define ARRAYS
#include <stdio.h>
#include <stdlib.h>
#include <postgresql/libpq-fe.h>
#include "tables.h"

struct books_array
{
    book_t *array_storage;
    size_t array_size;
};

struct accounts_array
{
    account_t *array_storage;
    size_t array_size;
};

struct loans_array
{
    loan_t *array_storage;
    size_t array_size;
};

typedef struct books_array books_array_t;
typedef struct accounts_array accounts_array_t;
typedef struct loans_array loans_array_t;
#endif