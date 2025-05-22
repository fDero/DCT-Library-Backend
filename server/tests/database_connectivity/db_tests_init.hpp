#include <gtest/gtest.h>

#include <iostream>

#include "data_objects.h"
#include "db_utils.h"

extern db_conn_t *conn;

extern account_t *db_account_1;
extern account_t *db_account_2;
extern account_t *db_account_3;
extern account_t *db_account_4;
extern account_t *db_account_5;
extern account_t *db_account_6;

extern book_t *db_book_1;
extern book_t *db_book_2;
extern book_t *db_book_3;
extern book_t *db_book_4;
extern book_t *db_book_5;
extern book_t *db_book_6;

extern loan_t *db_loan_1;
extern loan_t *db_loan_2;
extern loan_t *db_loan_3;
extern loan_t *db_loan_4;
extern loan_t *db_loan_5;
extern loan_t *db_loan_6;

class Database : public ::testing::Test {
protected:
  static void SetUpTestSuite() {
    db_connection_init();
    conn = open_db_connection();

    db_account_1 = (account_t *)malloc(sizeof(account_t));
    db_account_2 = (account_t *)malloc(sizeof(account_t));
    db_account_3 = (account_t *)malloc(sizeof(account_t));
    db_account_4 = (account_t *)malloc(sizeof(account_t));
    db_account_5 = (account_t *)malloc(sizeof(account_t));
    db_account_6 = (account_t *)malloc(sizeof(account_t));

    db_book_1 = (book_t *)malloc(sizeof(book_t));
    db_book_2 = (book_t *)malloc(sizeof(book_t));
    db_book_3 = (book_t *)malloc(sizeof(book_t));
    db_book_4 = (book_t *)malloc(sizeof(book_t));
    db_book_5 = (book_t *)malloc(sizeof(book_t));
    db_book_6 = (book_t *)malloc(sizeof(book_t));

    db_loan_1 = (loan_t *)malloc(sizeof(loan_t));
    db_loan_2 = (loan_t *)malloc(sizeof(loan_t));
    db_loan_3 = (loan_t *)malloc(sizeof(loan_t));
    db_loan_4 = (loan_t *)malloc(sizeof(loan_t));
    db_loan_5 = (loan_t *)malloc(sizeof(loan_t));
    db_loan_6 = (loan_t *)malloc(sizeof(loan_t));

    account_init(db_account_1, 1, "John", "Smith", "john.smith@example.com",
                 "ABCDEFGH");
    account_init(db_account_2, 2, "Emma", "Johnson", "emma.johnson@example.com",
                 "ABCDEFGH");
    account_init(db_account_3, 3, "William", "Brown",
                 "william.brown@example.com", "ABCDEFGH");
    account_init(db_account_4, 4, "Olivia", "Williams",
                 "olivia.williams@example.com", "ABCDEFGH");
    account_init(db_account_5, 5, "James", "Jones", "james.jones@example.com",
                 "ABCDEFGH");
    account_init(db_account_6, 6, "Sophia", "Davis", "sophia.davis@example.com",
                 "ABCDEFGH");

    timestamp_t *timestamp_book_1 = string_to_timestamp("1997-06-26 00:00:00");
    timestamp_t *timestamp_book_2 = string_to_timestamp("1949-06-08 00:00:00");
    timestamp_t *timestamp_book_3 = string_to_timestamp("1980-11-01 00:00:00");
    timestamp_t *timestamp_book_4 = string_to_timestamp("2014-05-15 00:00:00");
    timestamp_t *timestamp_book_5 = string_to_timestamp("1954-07-29 00:00:00");
    timestamp_t *timestamp_book_6 = string_to_timestamp("2008-09-14 00:00:00");

    book_init(db_book_1, 1, "Harry Potter", "J.K. Rowling", "Bloomsbury",
              "Fantasy,Young adult literature,Adventure fiction",
              timestamp_book_1, 10);

    book_init(db_book_2, 2, "1984", "G. Orwell", "Secker & Warburg",
              "Fiction,Science fiction,Mystery", timestamp_book_2, 6);

    book_init(db_book_3, 3, "Karamazov Brothers", "F. Dostoevskij",
              "The Russian Messenger",
              "Fiction,Novel,Mystery,Historical fiction,Literary fiction",
              timestamp_book_3, 4);

    book_init(db_book_4, 4, "Programming, Principles and Practices Using C++",
              "Bjarne Stroustrup", "Pearson", "Education", timestamp_book_4, 3);

    book_init(db_book_5, 5, "The Lord of the Rings",
              "John Ronald Reuel Tolkien",
              "George Allen and Unwin (UK) Houghton Mifflin (US)",
              "Fantasy fiction,Adventure fiction", timestamp_book_5, 2);

    book_init(db_book_6, 6, "The Hunger Games", "Suzanne Collins",
              "Scholastic Press",
              "Science fiction,Adventure fiction,Young adult literature",
              timestamp_book_6, 7);

    timestamp_t *timestamp_loan_1_st =
        string_to_timestamp("2024-04-02 00:00:00");
    timestamp_t *timestamp_loan_1_et =
        string_to_timestamp("2024-04-14 00:00:00");
    timestamp_t *timestamp_loan_2_st =
        string_to_timestamp("2024-04-05 00:00:00");
    timestamp_t *timestamp_loan_2_et =
        string_to_timestamp("2024-04-18 00:00:00");
    timestamp_t *timestamp_loan_3_st =
        string_to_timestamp("2024-04-08 00:00:00");
    timestamp_t *timestamp_loan_3_et =
        string_to_timestamp("2024-04-12 00:00:00");

    timestamp_t *timestamp_loan_4_st =
        string_to_timestamp("2024-04-10 00:00:00");
    timestamp_t *timestamp_loan_4_et =
        string_to_timestamp("2024-04-20 00:00:00");

    timestamp_t *timestamp_loan_5_st =
        string_to_timestamp("2024-04-11 00:00:00");
    timestamp_t *timestamp_loan_5_et =
        string_to_timestamp("2024-04-16 00:00:00");

    timestamp_t *timestamp_loan_6_st =
        string_to_timestamp("2024-04-12 00:00:00");
    timestamp_t *timestamp_loan_6_et =
        string_to_timestamp("2024-04-18 00:00:00");

    loan_init(db_loan_1, 1, timestamp_loan_1_st, timestamp_loan_1_et, 1, 1);
    loan_init(db_loan_2, 2, timestamp_loan_2_st, timestamp_loan_2_et, 2, 2);
    loan_init(db_loan_3, 3, timestamp_loan_3_st, timestamp_loan_3_et, 3, 4);
    loan_init(db_loan_4, 4, timestamp_loan_4_st, timestamp_loan_4_et, 3, 2);
    loan_init(db_loan_5, 5, timestamp_loan_5_st, timestamp_loan_5_et, 4, 5);
    loan_init(db_loan_6, 6, timestamp_loan_6_st, timestamp_loan_6_et, 5, 1);

    free(timestamp_book_1);
    free(timestamp_book_2);
    free(timestamp_book_3);
    free(timestamp_book_4);
    free(timestamp_book_5);
    free(timestamp_book_6);
    free(timestamp_loan_1_st);
    free(timestamp_loan_1_et);
    free(timestamp_loan_2_st);
    free(timestamp_loan_2_et);
    free(timestamp_loan_3_st);
    free(timestamp_loan_3_et);
    free(timestamp_loan_4_st);
    free(timestamp_loan_4_et);
    free(timestamp_loan_5_st);
    free(timestamp_loan_5_et);
    free(timestamp_loan_6_st);
    free(timestamp_loan_6_et);
  }

  static void TearDownTestSuite() {
    close_db_connection(conn);

    account_destroy(db_account_1);
    account_destroy(db_account_2);
    account_destroy(db_account_3);
    account_destroy(db_account_4);
    account_destroy(db_account_5);
    account_destroy(db_account_6);

    book_destroy(db_book_1);
    book_destroy(db_book_2);
    book_destroy(db_book_3);
    book_destroy(db_book_4);
    book_destroy(db_book_5);
    book_destroy(db_book_6);

    loan_destroy(db_loan_1);
    loan_destroy(db_loan_2);
    loan_destroy(db_loan_3);
    loan_destroy(db_loan_4);
    loan_destroy(db_loan_5);
    loan_destroy(db_loan_6);
  }
};
