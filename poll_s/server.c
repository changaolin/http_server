//
// Created by changaolin on 2022/9/10.
//
#include "common.h"
#define MAX_E_COUNT 128
int main(int argc, char *argv[]) {
	int listen_fd, conn_fd;
	int ready_number;
	int n;
	char buf[MESSAGE_MAX_LINE];
	struct sockaddr_in client_addr; 
	listen_fd = tcp_server(SERVER_ADDR, SERVER_PORT, 1024);
	struct pollfd event_set[MAX_E_COUNT];
	event_set[0].fd = listen_fd;
	event_set[0].events = POLLRDNORM;

	int i;
	for(i = 1; i < MAX_E_COUNT; i++) {
		event_set[i].fd = -1;
	}
	while (1) {
		PRINTF("wait pool...");
		ready_number = poll(event_set, MAX_E_COUNT, -1);
		if (ready_number < 0) {
			PRINTF("poll fail!");
			return EXIT_FAILURE;
		}
		PRINTF("pool recv...");
		if (event_set[0].revents & POLLRDNORM) {
			socklen_t client_len = sizeof(client_addr);
			conn_fd = accept(listen_fd, (struct sockaddr*)&client_addr, &client_len);
			for (i = 1; i < MAX_E_COUNT; i++) {
				if (event_set[i].fd < 0) {
					event_set[i].fd = conn_fd;
					event_set[i].events = POLLRDNORM;
					break;
				}
			}
			if (i == MAX_E_COUNT) {
				PRINTF("too much conn!");
				return EXIT_FAILURE;
			}
			if (--ready_number <= 0) {
				continue;
			}
		}
		for (i = 1; i < MAX_E_COUNT; i++) {
			int sock_fd = event_set[i].fd;
			if (sock_fd < 0) {
				continue;
			}
			if (event_set[i].revents & (POLLRDNORM | POLLERR)) {
				n = read(sock_fd, buf, MESSAGE_MAX_LINE);
				if (n < 0) {
					PRINTF("read error!");
					return EXIT_FAILURE;
				}
				if (n == 0 || errno == ECONNRESET) {
					close(sock_fd);
					event_set[i].fd = -1;
				}
				buf[n] = '\0';
				PRINTF("recv: %s", buf);
				if (write(sock_fd, buf, n) < 0) {
					PRINTF("write error!");
					return EXIT_FAILURE;
				}
				PRINTF("send: %s", buf);
				if (--ready_number <= 0) {
					break;
				}
			}
		}
	}
    return EXIT_SUCCESS;
}
