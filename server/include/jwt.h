#ifndef JWT_H
#define JWT_H

#include "http.h"
#include "cache.h"
#include <l8w8jwt/decode.h>
#include <l8w8jwt/encode.h>
#include <l8w8jwt/claim.h>

struct decoded_jwt {
 	int account_id;
 	char* session_token;
	char* iss;
	char* aud;
	int iat;
 	int exp;
};

typedef struct decoded_jwt decoded_jwt_t;

void jwt_init();
void encoded_jwt_destroy(char* jwt);
char* jwt_encode(int account_id, const char* session_token, unsigned long exp_time);
decoded_jwt_t* jwt_decode(const char* token);
void decoded_jwt_destroy(decoded_jwt_t* jwt);
decoded_jwt_t* authorize_jwt(const char* jwt_str);
bool is_jwt_about_to_expire(decoded_jwt_t* jwt);
unsigned long get_token_duration(const char* desired_exp);

#endif