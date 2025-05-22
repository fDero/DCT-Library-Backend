
#include "db_utils.h"
#include "data_objects.h"
#include "utils.h"
#include "assert.h"
#include <assert.h>
#include <stdbool.h>

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
        if (resultset != NULL){
            PQclear(resultset);
        }
        return NULL;
    }
    else {
        assert (PQntuples(resultset) == 1);
        assert (PQnfields(resultset) == 5);
        loan_t* loan = (loan_t*)malloc(sizeof(loan_t));
        extract_loan(resultset, 0, loan);
        PQclear(resultset);
        return loan;
    }
}

bool delete_loan(db_conn_t* connection, int loan_id, int account_id){

    char sql_command_string[200];

    sprintf(
        sql_command_string,
        "DELETE FROM Loan "
        "WHERE Loan.loan_id = %d "
        "AND Loan.account_id = %d "
        "RETURNING Loan.loan_id",
        loan_id, account_id
    );

    resultset_t* resultset = perform_query(connection, sql_command_string);
    char* sql_status = get_error_code(resultset);
    bool outcome = (PQntuples(resultset) > 0);
    PQclear(resultset);
    return outcome;
}

int insert_account(
    db_conn_t* connection, const char* name, const char* surname,
    const char* email, const char* hashed_password, const char* salt,
    char** error_code
){

    assert(error_code != NULL);
    *error_code = NULL;

    char sql_command_string[200];

    sprintf(
        sql_command_string,
        "SELECT * FROM insert_account('%s', '%s', '%s', '%s', '%s')",
        name, surname, email, hashed_password, salt
    );

    resultset_t* resultset = perform_query(connection, sql_command_string);
    char* sql_status = get_error_code(resultset);

    if (sql_status != NULL){
        alloc_and_strcpy(error_code, sql_status);
        PQclear(resultset);
        return 0;
    }
    else {
        assert (PQntuples(resultset) == 1);
        assert (PQnfields(resultset) == 1);
        int ret = atoi(PQgetvalue(resultset, 0, 0));
        PQclear(resultset);
        return ret;
    }
}