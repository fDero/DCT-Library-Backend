
#include <tinycrypt/sha256.h>
#include <tinycrypt/constants.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <hiredis/hiredis.h>
#include "hash.h"


char* sha256_hash_string(const char* string){
    int len = strlen(string);
    uint8_t digest[32];
    struct tc_sha256_state_struct s;

    (void)tc_sha256_init(&s);
    tc_sha256_update(&s, (const uint8_t *) string, len);
    (void)tc_sha256_final(digest, &s);

    char* hashed_string = (char*)malloc(sizeof(char) * 33);
    hashed_string[32] = '\0';
    for (int i = 0; i < 32; i++){
        hashed_string[i] = digest[i];
    }
    return hashed_string;
}

char* sha256_hash_string_alnum(const char* string){
    int len = strlen(string);
    uint8_t digest[32];
    struct tc_sha256_state_struct s;

    (void)tc_sha256_init(&s);
    tc_sha256_update(&s, (const uint8_t *) string, len);
    (void)tc_sha256_final(digest, &s);

    char* hashed_string = (char*)malloc(sizeof(char) * 33);
    hashed_string[32] = '\0';
    for (int i = 0; i < 32; i++){
        hashed_string[i] = (digest[i] % 78) + 48;
        hashed_string[i] += (hashed_string[i] == '\\');
    }
    return hashed_string;
}

char* sha256_hash_number(long long int num){
    char buffer[150];
    sprintf(buffer, "%lld", num);
    return sha256_hash_string_alnum(buffer);
}

char* sha256_salted_hash_alnum(const char* string, const char* salt){
    char* salted_string = (char*)malloc(sizeof(char) * (strlen(string) + strlen(salt) + 3));
    sprintf(salted_string, "%s%s", string, salt);
    char* hashed_string = sha256_hash_string_alnum(salted_string);
    free(salted_string);
    return hashed_string;
}