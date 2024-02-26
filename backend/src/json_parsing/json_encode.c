#include "json.h"

char* account_to_json_string(account_t* account){
	return json_to_string_and_free(account_to_json(account));
}

char* book_to_json_string(book_t* book){
	return json_to_string_and_free(book_to_json(book));
}

char* loan_to_json_string(loan_t* loan){
	return json_to_string_and_free(loan_to_json(loan));
}

char* account_array_to_json_string(account_array_t* account_array){
	return json_to_string_and_free(account_array_to_json(account_array));
}

char* book_array_to_json_string(book_array_t* book_array){
	return json_to_string_and_free(book_array_to_json(book_array));
}

char* loan_array_to_json_string(loan_array_t* loan_array){
	return json_to_string_and_free(loan_array_to_json(loan_array));
}

json_t* account_to_json(account_t* account){
    
    json_t *json_object = init_json_object();
    assert (json_object != NULL);
    
    add_numeric_field_to_json_obj (json_object,  "account_id", account->account_id);
    add_text_field_to_json_obj    (json_object,  "name",       account->name);
    add_text_field_to_json_obj    (json_object,  "surname",    account->surname);
    add_text_field_to_json_obj    (json_object,  "email",      account->email);
    return json_object;
}

json_t* book_to_json(book_t* book){
    
    json_t *json_object = init_json_object();
    assert (json_object != NULL);

    add_numeric_field_to_json_obj  (json_object,  "book_id",      book->book_id);
    add_text_field_to_json_obj     (json_object,  "title",       book->title);
    add_text_field_to_json_obj     (json_object,  "author",       book->author);
    add_text_field_to_json_obj     (json_object,  "publisher",    book->publisher);
    add_text_field_to_json_obj     (json_object,  "genres",       book->genres);
    add_timestamp_field_to_json_obj(json_object,  "release_date", &(book->release_date));
    add_numeric_field_to_json_obj  (json_object,  "total_copies", book->total_copies);
    return json_object;
}

json_t* loan_to_json(loan_t* loan){
    
    json_t *json_object = init_json_object();
    assert (json_object != NULL);

    add_numeric_field_to_json_obj   (json_object,  "loan_id",        loan->loan_id);
    add_timestamp_field_to_json_obj (json_object,  "starting_time",  &(loan->starting_time));
    add_timestamp_field_to_json_obj (json_object,  "ending_time",    &(loan->ending_time));
    add_numeric_field_to_json_obj   (json_object,  "account_id",     loan->account_id);
    add_numeric_field_to_json_obj   (json_object,  "book_id",        loan->book_id);
    return json_object;
}

json_t* account_array_to_json(account_array_t* account_array){
    
    json_t *json_array = init_json_array();
    
    for (int i = 0; i < account_array->size; i++){
        account_t *account = &(account_array->storage[i]);
        json_t *json_account = account_to_json(account);
        add_json_item_to_json_array(json_array, json_account);
    }

    return json_array;
}

json_t* book_array_to_json(book_array_t* book_array){
    
    json_t *json_array = init_json_array();
    
    for (int i = 0; i < book_array->size; i++){
        book_t *book = &(book_array->storage[i]);
        json_t *json_book = book_to_json(book);
        add_json_item_to_json_array(json_array, json_book);
    }
    
    return json_array;
}

json_t* loan_array_to_json(loan_array_t* loan_array){
    
    json_t *json_array = init_json_array();
    
    for (int i = 0; i < loan_array->size; i++){
        loan_t *loan = &(loan_array->storage[i]);
        json_t *json_loan = loan_to_json(loan);
        add_json_item_to_json_array(json_array, json_loan);
    }
    
    return json_array;
}