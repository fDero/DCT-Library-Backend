#include <gtest/gtest.h>
#include <iostream>
#include "db_connection.h"
#include "data_objects.h"

extern db_conn_t* conn;
extern account_t* db_account_1;
extern account_t* db_account_2;
extern account_t* db_account_3;
extern account_t* db_account_4;
extern account_t* db_account_5;
extern account_t* db_account_6;

class Database : public ::testing::Test {
protected:
    static void SetUpTestSuite() {
			db_connection_init();
      conn = open_db_connection();

			db_account_1 = (account_t*) malloc (sizeof(account_t));
			account_init(db_account_1, 1, "John", "Smith", "john.smith@example.com");
			db_account_2 = (account_t*) malloc (sizeof(account_t));
			account_init(db_account_2, 2, "Emma", "Johnson", "emma.johnson@example.com");
			db_account_3 = (account_t*) malloc (sizeof(account_t));
			account_init(db_account_3, 3, "William", "Brown", "william.brown@example.com");
			db_account_4 = (account_t*) malloc (sizeof(account_t));
			account_init(db_account_4, 4, "Olivia", "Williams", "olivia.williams@example.com");
			db_account_5 = (account_t*) malloc (sizeof(account_t));
			account_init(db_account_5, 5, "James", "Jones", "james.jones@example.com");
			db_account_6 = (account_t*) malloc (sizeof(account_t));
			account_init(db_account_6, 6, "Sophia", "Davis", "sophia.davis@example.com");
    }

    static void TearDownTestSuite() {
        close_db_connection(conn);
				account_destroy(db_account_1);
				account_destroy(db_account_2);
				account_destroy(db_account_3);
				account_destroy(db_account_4);
				account_destroy(db_account_5);
				account_destroy(db_account_6);
    }
};
