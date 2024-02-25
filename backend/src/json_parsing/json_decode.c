#include "json.h"

account_t* account_from_json(json_t* json) {
    account_t* extracted_account = (account_t*)malloc(sizeof(account_t));
    bool valid = true;
    valid &= extract_int_from_json(json, "account_id",
                                   &(extracted_account->account_id));
    valid &= extract_text_from_json(json, "name", &(extracted_account->name));
    valid &=
        extract_text_from_json(json, "surname", &(extracted_account->surname));
    valid &= extract_text_from_json(json, "email", &(extracted_account->email));
    if (!valid) {
        free(extracted_account);
        extracted_account = NULL;
    }
    return extracted_account;
}

book_t* book_from_json(json_t* json) {
    book_t* extracted_book = (book_t*)malloc(sizeof(book_t));
    bool valid = true;
    valid &= extract_int_from_json(json, "book_id", &(extracted_book->book_id));
    valid &= extract_text_from_json(json, "author", &(extracted_book->author));
    valid &=
        extract_text_from_json(json, "publisher", &(extracted_book->publisher));
    valid &= extract_timestamp_from_json(json, "release_date",
                                         &(extracted_book->release_date));
    valid &= extract_int_from_json(json, "total_copies",
                                   &(extracted_book->total_copies));
    if (!valid) {
        free(extracted_book);
        extracted_book = NULL;
    }
    return extracted_book;
}

loan_t* loan_from_json(json_t* json) {
    loan_t* extracted_loan = (loan_t*)malloc(sizeof(loan_t));
    bool valid = true;
    valid &= extract_int_from_json(json, "account_id",
                                   &(extracted_loan->account_id));
    valid &= extract_int_from_json(json, "book_id", &(extracted_loan->book_id));
    valid &= extract_int_from_json(json, "loan_id", &(extracted_loan->loan_id));
    valid &= extract_timestamp_from_json(json, "starting_time",
                                         &(extracted_loan->starting_time));
    valid &= extract_timestamp_from_json(json, "ending_time",
                                         &(extracted_loan->ending_time));
    if (!valid) {
        free(extracted_loan);
        extracted_loan = NULL;
    }
    return extracted_loan;
}