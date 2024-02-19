
#ifndef DBTABLES
#define DBTABLES
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <postgresql/libpq-fe.h>
#include "utils.h"

struct account
{
    string_t name;
    string_t surname;
    string_t email;
    int borrowed_books;
    int account_id;
};

struct book
{
    string_t title;
    string_t author;
    string_t publisher;
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