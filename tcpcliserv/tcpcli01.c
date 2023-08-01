#include "lib/unp.h"

int main(int argc, char** argv) {
    int sockfd;
    struct sockaddr_in servaddr;

    if (argc != 2) {
        printf("usage: tcpcli <IPaddress>");
        return -1;
    }

    sockfd = Socket(PF_INET, SOCK_STREAM, 0);

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(SERV_PORT);
    inet_pton(AF_INET, argv[1], &servaddr.sin_addr.s_addr);

    Connect(sockfd, (struct sockaddr*) &servaddr, sizeof(servaddr));

    str_cli(stdin, sockfd);

    exit(0);
}