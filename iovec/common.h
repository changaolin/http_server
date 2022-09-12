//
// Created by changaolin on 2022/9/10.
//

#ifndef SOCKET_P_COMMON_H
#define SOCKET_P_COMMON_H

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <stdarg.h>
#include <string.h>
#include <strings.h>
#include <err.h>
#include <errno.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/un.h>
#include <arpa/inet.h>
#include <signal.h>
#include <sys/uio.h>

#define SERVER_PORT 12345
#define SERVER_ADDR "127.0.0.1"
#define MESSAGE_MAX_LINE 1024
#define LOCAL_SOCK "/home/cal/code/local.sock"

void write_log(const char *file, const char *function, int line, const char *fmt, ...);
//fprintf(stdout, fmt, __FILE__, __FUNCTION__, __LINE__, ##__VA_ARGS__)
#define PRINTF(fmt, ...) \
write_log(__FILE__, __FUNCTION__, __LINE__, fmt, ##__VA_ARGS__)

int read_n(int fd, void *buffer, int buffer_size, int read_size);

#endif //SOCKET_P_COMMON_H
