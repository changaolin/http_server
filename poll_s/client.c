//
// Created by changaolin on 2022/9/10.
//

#include "common.h"

#define MAX_BUF_SIZE 10240

int main(int argc, char *argv[]) {
	int sock_fd = tcp_client(SERVER_ADDR, SERVER_PORT);
	if (sock_fd < 0) {
		return EXIT_FAILURE;
	}
	char recv_line[MESSAGE_MAX_LINE], send_line[MESSAGE_MAX_LINE];
	int n;
	fd_set readmask;
	fd_set allreads;
	FD_ZERO(&allreads);
	FD_SET(0, &allreads);
	FD_SET(sock_fd, &allreads);

	PRINTF("wait input...");
	while (1) {
		readmask = allreads;
		int rc = select(sock_fd + 1, &readmask, NULL, NULL, NULL);
		if (rc <= 0) { // 阻塞io
			PRINTF("select fail!");
			return EXIT_FAILURE;
		}
		if (FD_ISSET(sock_fd, &readmask)) {
			n = read(sock_fd, recv_line, MESSAGE_MAX_LINE);
			if (n == 0) {
				PRINTF("server terminated!");
				return EXIT_FAILURE;
			}
			if (n < 0) {
				PRINTF("read fail!!");
				return EXIT_FAILURE;
			}
			recv_line[n] = 0;
			PRINTF("recv: %s", recv_line);
		}
		if (FD_ISSET(0, &readmask)) {
			if (fgets(send_line, MESSAGE_MAX_LINE, stdin) != NULL) {
				int i = strlen(send_line);
				if (send_line[i-1] == '\n') {
					send_line[i-1] = '\0';
				}
				PRINTF("send: %s", send_line);
				int len = strlen(send_line);
				int rt = write(sock_fd, send_line, len);
				if (rt < 0) {
					PRINTF("write error");
					return EXIT_FAILURE;
				}
			}
		}
	}
    return EXIT_SUCCESS;
}
