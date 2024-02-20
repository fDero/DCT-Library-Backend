#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

void print_failure(long *errnum, const char *format, va_list args);
void print_success(long *errnum, const char *format, va_list args);
void test(long *errnum, const bool test_res, const char *format, ...);