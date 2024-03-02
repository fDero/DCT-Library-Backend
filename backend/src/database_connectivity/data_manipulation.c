
#include "db_utils.h"
#include "data_objects.h"
#include "utils.h"
#include "assert.h"
#include <assert.h>

void extract_loan(resultset_t* resultset, int row, loan_t* loan);

loan_t* insert_loan(db_conn_t* connection, int input_book_id, int input_account_id, char** error_code){

    assert(error_code != NULL);
    *error_code = NULL;

    char sql_command_string[200];

    sprintf(
        sql_command_string,
        "INSERT INTO Loan(account_id, book_id) "
        "VALUES(%d, %d) RETURNING Loan.loan_id, "
        "Loan.starting_time, Loan.ending_time, "
        "Loan.account_id, Loan.book_id",
        input_account_id, input_book_id
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
        return NULL;
    }
    else {
        assert (PQntuples(resultset) == 1);
        assert (PQnfields(resultset) == 5);
        log_to_console(RED, "ok...\n");
        loan_t* loan = (loan_t*)malloc(sizeof(loan_t));
        extract_loan(resultset, 0, loan);
        log_to_console(RED, "ok...\n");
        return loan;
    }
}
