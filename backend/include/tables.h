
#ifndef DB_TABLES_H
#define DB_TABLES_H
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
#endif