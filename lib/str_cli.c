#include "unp.h"

void str_cli(FILE* fp, int sockfd) {
    char sendline[MAXLINE], recvline[MAXLINE];

    while(fgets(sendline, MAXLINE, fp) != NULL) {
        Writen(sockfd, sendline, strlen(sendline));

        if (Readline(sockfd, recvline, MAXLINE) == 0) {
            printf("str_cli: server terminated prematurely");
            return;
        }

        fputs(recvline, stdout);
    }
}