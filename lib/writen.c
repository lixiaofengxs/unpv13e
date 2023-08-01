#include "unp.h"

ssize_t writen(int fd, const void* vptr, size_t n) {
    size_t nleft;
    size_t nwritten;
    const char* ptr;

    ptr = vptr;
    nleft = n;

    while(nleft > 0) {
        if ((nwritten = write(fd, ptr, n)) <= 0) {
            if (nwritten < 0 && errno == EINTR)
                nwritten = 0; //and call() write again
            else
                return -1;
        }

        nleft -= nwritten;
        ptr += nwritten;
    }

    return n;
}

void Writen(int fd, void* vptr, size_t nbytes) {
    if (writen(fd, vptr, nbytes) != nbytes) {
        printf("writen error.");
    }
}