#ifndef SOCK_H
#define SOCK_H
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
char* sock_ntop(const struct sockaddr_in* sin, socklen_t salen);
void make_nonblocking(int fd);
#endif // SOCK_H
