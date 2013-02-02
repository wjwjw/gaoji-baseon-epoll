#include <sys/socket.h>
#include <sys/epoll.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <syslog.h>

#define MAXLINE         4096    /* max text line length */

void     err_sys(const char *, ...);
void     err_dump(const char *, ...);
void     err_msg(const char *, ...);
void     err_quit(const char *, ...);

