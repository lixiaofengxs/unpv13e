#include "unp.h"

void err_sys(const char* fmt, ...) {
    printf("%s\n", fmt);
    exit(1);
}

void err_quit(const char* fmt, ...) {
    printf("%s\n", fmt);
    exit(1);
}