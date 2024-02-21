
#ifndef DATA_OBJECTS_H
#define DATA_OBJECTS_H
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <postgresql/libpq-fe.h>
#include "db_utils.h"

struct account
{
    char* name;
    char* surname;
    char* email;
    int borrowed_books;
    int account_id;
};

struct book
{
    char* title;
    char* author;
    char* publisher;
    timestamp_t release_date;
    int total_copies;
    int borrowed_copies;
    int book_id;
};

struct loan
{
    timestamp_t starting_time;
    timestamp_t ending_time;
    int account_id;
    int book_id;
    int loan_id;
};

typedef struct account account_t;
typedef struct book book_t;
typedef struct loan loan_t;

struct account_array
{
    account_t *storage;
    size_t size;
};

struct book_array
{
    book_t *storage;
    size_t size;
};

struct loan_array
{
    loan_t *storage;
    size_t size;
};

typedef struct account_array account_array_t;
typedef struct book_array book_array_t;
typedef struct loan_array loan_array_t;

void account_destroy(account_t* account);
void book_destroy(book_t* book);
void loan_destroy(loan_t* loan);

void account_array_init(account_array_t * array, size_t size);
void book_array_init(book_array_t *array, size_t size);
void loan_array_init(loan_array_t *array, size_t size);

void account_array_destroy(account_array_t *array);
void book_array_destroy(book_array_t *array);
void loan_array_destroy(loan_array_t *array);

#endif