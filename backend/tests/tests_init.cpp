#include <gtest/gtest.h>
#include <iostream>
#include "db_connection.h"
#include "data_objects.h"

extern db_conn_t* conn;
extern account_t* account1;
extern account_t* account2;
extern account_t* account3;
extern account_t* account4;
extern account_t* account5;
extern account_t* account6;

class Database : public ::testing::Test {
protected:
    static void SetUpTestSuite() {
			db_connection_init();
      conn = open_db_connection();

			account1 = (account_t*) malloc (sizeof(account_t));
			account_init(account1, 1, "John", "Smith", "john.smith@example.com", 1);
			account2 = (account_t*) malloc (sizeof(account_t));
			account_init(account2, 2, "Emma", "Johnson", "emma.johnson@example.com", 1);
			account3 = (account_t*) malloc (sizeof(account_t));
			account_init(account3, 3, "William", "Brown", "william.brown@example.com", 2);
			account4 = (account_t*) malloc (sizeof(account_t));
			account_init(account4, 4, "Olivia", "Williams", "olivia.williams@example.com", 1);
			account5 = (account_t*) malloc (sizeof(account_t));
			account_init(account5, 5, "James", "Jones", "james.jones@example.com", 1);
			account6 = (account_t*) malloc (sizeof(account_t));
			account_init(account6, 6, "Sophia", "Davis", "sophia.davis@example.com", 0);
    }

    static void TearDownTestSuite() {
        close_db_connection(conn);
				account_destroy(account1);
				account_destroy(account2);
				account_destroy(account3);
				account_destroy(account4);
				account_destroy(account5);
				account_destroy(account6);
    }
};
