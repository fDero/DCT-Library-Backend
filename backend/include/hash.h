#ifndef HASH_H
#define HASH_H

char* sha256_hash_number(long long int num);
char* sha256_hash_string(const char* string);
char* sha256_hash_string_alnum(const char* string);
char* sha256_salted_hash_alnum(const char* string, const char* salt);

#endif