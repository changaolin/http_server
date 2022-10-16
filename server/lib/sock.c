#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <strings.h>
#include <stdio.h>
#include "sock.h"
char* sock_ntop(const struct sockaddr_in* sin, socklen_t salen) {
	char port[8] = {0};
	static char str[128];

	if (inet_ntop(AF_INET, &sin->sin_addr, str, sizeof(str)) == NULL) {
		return NULL;
	}
	if (ntohs(sin->sin_port) != 0) {
		snprintf(port, sizeof(port), ":%d", ntohs(sin->sin_port));
		strcat(str, port);
	}
	return str;
}
void make_nonblocking(int fd) {
	fcntl(fd, F_SETFL, O_NONBLOCK);
}
