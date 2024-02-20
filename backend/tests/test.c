#include "test.h"

void print_failure(long *errnum, const char *format, va_list args) {
    printf("\033[1;31m(%ld) Failure\033[0;31m: ", *errnum);
    vprintf(format, args);
    printf("\033[0m\n");
}

void print_success(long *errnum, const char *format, va_list args) {
    printf("\033[1;32m(%ld) Success\033[0;32m: ", *errnum);
    vprintf(format, args);
    printf("\033[0m\n");
}

void test(long *errnum, const bool test_res, const char *format, ...) {
    va_list args;
    va_start(args, format);
    if (!test_res) *errnum++;
    if (test_res)
        print_success(errnum, format, args);
    else
        print_failure(errnum, format, args);
    va_end(args);
}
