#include "lib/unp.h"
#include <limits.h> //for OPEN_MAX

int main(int argc, char **argv) {
    int i, maxi, listenfd, connfd, sockfd;
    int nready;
    ssize_t n;
    char buf[MAXLINE];
    socklen_t clilen;
    struct pollfd client[OPEN_MAX];
    struct sockaddr_in cliaddr, servaddr;

    listenfd = Socket(AF_INET, SOCK_STREAM, 0);

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family= PF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(SERV_PORT);

    Bind(listenfd, (SA*) &servaddr, sizeof(servaddr));

    Listen(listenfd, LISTENQ);

    client[0].fd = listenfd;
    client[0].events = POLLRDNORM;

    //client数组的第一项用于监听套接字，其余各项的描述符置为-1。
    for (i = 1; i < OPEN_MAX; i++) {
        client[i].fd = -1; // -1 indicates available entry
    }

    //当有新的连接准备好被接受时poll将通知我们。
    //maxi变量含有client数组当前正在使用的最大下标值。
    maxi = 0; //max index into client[] array

    for ( ; ; ) {
        nready = poll(client, maxi + 1, -1);

        //new client connection
        if (client[0].revents & POLLRDNORM) {
            clilen = sizeof(cliaddr);
            connfd = Accept(listenfd, (SA*) &cliaddr, &clilen);

            for (i = 1; i < OPEN_MAX; i++) {
                if (client[i].fd < 0) {
                    client[i].fd = connfd;
                    break;
                }
            }

            if (i == OPEN_MAX)
                err_quit("too many clients");

            client[i].events = POLLRDNORM;
            if (i > maxi)
                maxi = i;

            if (--nready <= 0)
                continue;
        }

        for (i = 1; i <= maxi; i++) {
            if ( (sockfd = client[i].fd) < 0 ) {
                if (errno == ECONNRESET) {
                    Close(sockfd);
                    client[i].fd = -1;
                } else {
                    err_sys("read error");
                } 
            } else if (n == 0) {
                Close(sockfd);
                client[i].fd = -1;
            } else {
                Writen(sockfd, buf, n);
            }

            if (--nready <= 0)
                break;
        }
    }

}