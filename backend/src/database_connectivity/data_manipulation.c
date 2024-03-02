
#include "db_utils.h"
#include "data_objects.h"
#include "utils.h"
#include <assert.h>

int insert_loan(db_conn_t* connection, loan_t* loan, char** error_code){

    assert(error_code != NULL);
    *error_code = NULL;

    char sql_command_string[200];
    char starting_time[30];
    char ending_time[30];

    timestamp_to_string(starting_time, 30, &(loan->starting_time));
    timestamp_to_string(ending_time, 30, &(loan->ending_time));

    sprintf(
        sql_command_string, 
        "INSERT INTO Loan(account_id,book_id) "
        "VALUES(%d, %d) RETURNING *;", 
        loan->account_id, loan->book_id
    );

    resultset_t* resultset = perform_query(connection, sql_command_string);
    char* sql_status = get_error_code(resultset);

    if (sql_status != NULL || PQntuples(resultset) <= 0){
        if (sql_status != NULL){
            alloc_and_strcpy(error_code, sql_status);
        }
        if (resultset != NULL) {
            PQclear(resultset);
        }
        return -1;
    }
    else {
        int id = atoi(PQgetvalue(resultset, 0, 0));
        loan->loan_id = id;
        PQclear(resultset);
        return id;
    }
}
