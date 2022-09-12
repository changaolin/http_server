//
// Created by changaolin on 2022/9/10.
//
#include "common.h"
#define MAX_LINE 1024
#define FD_INIT_SIZE 128

char rot13_char(char c) {
    if ((c >= 'a' && c <= 'm') || (c >= 'A' && c <= 'M'))
        return c + 13;
    else if ((c >= 'n' && c <= 'z') || (c >= 'N' && c <= 'Z'))
        return c - 13;
    else
        return c;
}

int main(int argc, char **argv) {
	int listen_fd, sock_fd;
	int n, i;
	int efd;
	struct epoll_event event;
	struct epoll_event* events;
	
	listen_fd = tcp_nonblocking_server_listen(SERVER_PORT);

	efd = epoll_create1(0);
	if (efd == -1) {
		PRINTF("epoll_create1 fail!");
		return EXIT_FAILURE;
	}

	event.data.fd = listen_fd;
	event.events = EPOLLIN | EPOLLET;
	if (epoll_ctl(efd, EPOLL_CTL_ADD, listen_fd, &event) == -1) {
		PRINTF("epoll_ctl fail!");
		return EXIT_FAILURE;
	}

	events = calloc(4096, sizeof(event));

	while (1) {
		n = epoll_wait(efd, events, 4096, -1);
		PRINTF("epoll_wait n: %d", n);
		for (i = 0; i < n; i++) {
			if ((events[i].events & EPOLLERR) || 
				(events[i].events & EPOLLHUP) ||
				(!events[i].events & EPOLLIN)
			) {
				PRINTF("epoll error!");
				close(events[i].data.fd);
				continue;
			} else if (listen_fd == events[i].data.fd) {
				struct sockaddr_storage ss;
				socklen_t slen = sizeof(ss);
				int fd = accept(listen_fd, (struct sockaddr*)&ss, &slen);
				if (fd < 0) {
					PRINTF("accept fail!");
					return EXIT_FAILURE;
				} else {
					make_nonblocking(fd);
					event.data.fd = fd;
					event.events = EPOLLIN | EPOLLET; // edge-trigger
					if (epoll_ctl(efd, EPOLL_CTL_ADD, fd, &event) == -1) {
						PRINTF("new sk add fail!");
						return EXIT_FAILURE;
					}
				}
				continue;
			} else {
				sock_fd = events[i].data.fd;
				PRINTF("get event on sock[%d]", sock_fd);
				while (1) {
					char buf[512];
					if ((n = read(sock_fd, buf, sizeof(buf))) < 0) {
						if (errno != EAGAIN) {
							PRINTF("read fail!");
							close(sock_fd);
						}
						break;
					} else if (n == 0) {
						close(sock_fd);
						break;
					} else {
						for (i = 0; i < n; i++) {
							buf[i] = rot13_char(buf[i]);
						}
						if (write(sock_fd, buf, n) < 0) {
							PRINTF("read fail!");
							close(sock_fd);
						}
						break;
					}
				}
			}
		}
	}
	free(events);
	close(listen_fd);
}
