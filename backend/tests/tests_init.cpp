#include <gtest/gtest.h>
#include <iostream>
#include "db_connection.h"

extern db_conn_t* conn;

class Database : public ::testing::Test {
protected:
    static void SetUpTestSuite() {
			db_connection_init();
      conn = open_db_connection();
    }

    static void TearDownTestSuite() {
        close_db_connection(conn);
    }
};
