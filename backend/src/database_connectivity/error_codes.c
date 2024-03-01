
#include "db_utils.h"
#include "data_objects.h"
#include "utils.h"
#include <assert.h>

char* get_error_code(resultset_t* res){
    if (PQresultStatus(res) == PGRES_COMMAND_OK) {
        return NULL;
    }
    else {
        return PQresultErrorField(res, PG_DIAG_SQLSTATE);
    }
}

void init_db_global_variables(){
    db_conn_t* connection = open_db_connection();
    resultset_t* resultset = perform_query(connection, "SELECT * FROM GlobalValue");
	int row_count = PQntuples(resultset);
	int col_count = PQnfields(resultset);
	assert(col_count == 2);
	assert(row_count != 0);
    global_db_variables = (database_gloabal_variable_t*)malloc(sizeof(database_gloabal_variable_t) * row_count);
	for (int row = 0; row < row_count; row++)
	{
		alloc_and_strcpy(&(global_db_variables[row].name), PQgetvalue(resultset, row, 0));
        alloc_and_strcpy(&(global_db_variables[row].value_string), PQgetvalue(resultset, row, 1));
        global_db_variables[row].value_int = atoi(global_db_variables[row].value_string);
	}
    global_db_variables_size = row_count;
	PQclear(resultset);
    close_db_connection(connection);
}

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
        "INSERT INTO Loan(starting_time,ending_time,account_id,book_id) "
        "VALUES('%s', '%s', %d, %d) RETURNING Loan.loan_id;", 
        starting_time, ending_time, loan->account_id, loan->book_id
    );

    console_log(YELLOW, "SQL: %s\n", sql_command_string);

    resultset_t* resultset = perform_query(connection, sql_command_string);
    char* out_error_code = get_error_code(resultset);

    console_log(YELLOW, "Error code: %s\n", out_error_code);

    if (out_error_code != NULL || PQntuples(resultset) <= 0){
        if (out_error_code != NULL){
            console_log(YELLOW, "Setting error code\n");
            alloc_and_strcpy(error_code, out_error_code);
        }
        if (resultset != NULL) {
            console_log(YELLOW, "Clearing resultset\n");
            PQclear(resultset);
        }
        return -1;
    }
    else {
        console_log(YELLOW, "Getting loan id\n");
        int id = atoi(PQgetvalue(resultset, 0, 0));
        loan->loan_id = id;
        PQclear(resultset);
        return id;
    }
}
