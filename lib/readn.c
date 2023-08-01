#include "unp.h"

//read n bytes from a descriptor.
ssize_t readn(int fd, void* vptr, size_t n) {
    size_t nleft;
    size_t nread;
    char* ptr;

    ptr = vptr;
    nleft = n;

    while(nleft > 0) {
        if ((nread = read(fd, ptr, nleft)) < 0) {
            if (errno == EINTR)
                nread = 0; //and call read() again
            else
                return -1;
        } else if (nread == 0) {
            break; //EOF
        }

        nleft -= nread;
        ptr += nread;
    }

    //返回实际读到的字节数
    return n - nleft; //return n >= 0
}

size_t Readn(int fd, void* ptr, size_t nbytes) {
    size_t n;
    if ((n = readn(fd, ptr, nbytes)) < 0) {
        printf("readn error");
        return -1;
    }
        
    return n;
}