#ifndef __UNP_H
#define __UNP_H

#include <errno.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <signal.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SA struct sockaddr

typedef void Sigfunc(int);

/* Define some port number that can be used for our examples */
#define	SERV_PORT		 9877			/* TCP and UDP */
#define	SERV_PORT_STR	"9877"			/* TCP and UDP */

#define	LISTENQ		1024    /* 2nd argument to listen() */

#define	MAXLINE		4096	/* max text line length */
#define	BUFFSIZE	8192	/* buffer size for reads and writes */

//readn.c
ssize_t readn(int, void *, size_t);
size_t  Readn(int, void *, size_t);

//writen.c
ssize_t writen(int, const void *, size_t);
void    Writen(int, void *, size_t);

//readline.c
ssize_t Readline(int, void *, size_t);
ssize_t readline(int, void *, size_t);

void str_echo(int);
void str_cli(FILE *, int);

int Socket(int, int, int);
void Bind(int, const SA *, socklen_t);
void Listen(int, int);
int Accept(int, SA *, socklen_t *);
void Connect(int, const SA *, socklen_t);
void Close(int);

Sigfunc *Signal(int, Sigfunc *);

void err_sys(const char*, ...);
void err_quit(const char*, ...);

#endif