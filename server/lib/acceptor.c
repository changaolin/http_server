#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include "common.h"
#include "acceptor.h"

#define LISTENQ 1024
struct acceptor* acceptor_init(int port) {
	struct acceptor* acpt = malloc(sizeof(struct acceptor));
	if (acpt == NULL) {
		return NULL;
	}
	acpt->listen_port = port;
	acpt->listen_fd = socket(AF_INET, SOCK_STREAM, 0);

	make_nonblocking(acpt->listen_fd);

	struct sockaddr_in server_addr;
	bzero(&server_addr, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	server_addr.sin_port = htons(port);

	int on = 1;
	setsockopt(acpt->listen_fd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));

	int ret = bind(acpt->listen_fd, (struct sockaddr*)&server_addr, sizeof(server_addr));
	if (ret < 0) {
		ERROR_LOG("bind failed: errno:%d", errno);
		return NULL;
	}

	ret = listen(acpt->listen_fd, LISTENQ);
	if (ret < 0) {
		ERROR_LOG("listen failed: errno:%d", errno);
		return NULL;
	}
	return acpt;
}

