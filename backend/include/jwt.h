// #ifndef JWT_H
// #define JWT_H

// #include "http.h"
// #include <l8w8jwt/decode.h>
// #include <l8w8jwt/encode.h>

// extern char* jwt_private_key;
// extern char* jwt_public_key;
// extern char* jwt_iss;
// extern char* jwt_aud;
// extern int   jwt_exp;

// struct decoded_jwt {
// 		int id;
// 		char* session_token;
// 		int expiration_time;
// };

// typedef struct decoded_jwt decoded_jwt_t;

// void jwt_init();
// void jwt_destroy();
// int jwt_free(char* jwt);
// char* jwt_encode(int account_id, char* session_token);
// void jwt_decode(char* token, int account_id);

// #endif