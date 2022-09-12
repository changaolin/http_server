//
// Created by changaolin on 2022/9/10.
//
#include "common.h"

void read_data(int fd, char* buf, int buf_size) {
	read(fd, buf, buf_size);
	PRINTF("recv: %s", buf);
}
void send_data(int fd, char* buf, int buf_size) {
	write(fd, buf, buf_size);	
	PRINTF("send: %s", buf);
}
int main(int argc, char *argv[]) {
    int listen_fd, conn_fd;
    socklen_t cli_len;
    struct sockaddr_in server_addr, client_addr;
    listen_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (listen_fd < 0) {
        return EXIT_FAILURE;
    }
    bzero(&server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERVER_PORT);
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);

    bind(listen_fd, (struct sockaddr *) &server_addr, sizeof(server_addr));
    listen(listen_fd, 1024);
	char buf[MESSAGE_MAX_LINE];
	PRINTF("wait conn");
    conn_fd = accept(listen_fd, (struct sockaddr *) &client_addr, &cli_len);
    while (1) {
	    bzero(buf, MESSAGE_MAX_LINE);
        read_data(conn_fd, buf, MESSAGE_MAX_LINE);
		send_data(conn_fd, buf, MESSAGE_MAX_LINE);
    }
    return EXIT_SUCCESS;
}
