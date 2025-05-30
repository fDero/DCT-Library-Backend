
#include "db_utils.h"
#include "data_objects.h"
#include "utils.h"
#include <assert.h>

size_t global_db_variables_size = 0;
database_gloabal_variable_t* global_db_variables = NULL;

char* get_error_code(resultset_t* res){
    if (PQresultStatus(res) == PGRES_COMMAND_OK){
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
    for (int row = 0; row < row_count; row++){
        alloc_and_strcpy(&(global_db_variables[row].name), PQgetvalue(resultset, row, 0));
        alloc_and_strcpy(&(global_db_variables[row].value_string), PQgetvalue(resultset, row, 1));
        global_db_variables[row].value_int = atoi(global_db_variables[row].value_string);
    }
    global_db_variables_size = row_count;
    PQclear(resultset);
    close_db_connection(connection);
}

const char* generic_error_str = "Unrecognized error";

const char* error_phrase(const char* error_code){
    for (size_t i = 0; i < global_db_variables_size; i++){
        if (strcmp(global_db_variables[i].value_string, error_code) == 0){
            return global_db_variables[i].name;
        }
    }
    return generic_error_str;
}
