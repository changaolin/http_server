//
// Created by changaolin on 2022/9/10.
//
#include "common.h"

void read_data(int fd) {
    int n;
    char buf[1024];
    int times = 0;
    while (1) {
        PRINTF("block in read");
        if ((n = read_n(fd, buf, 1024, 1024)) == 0) {
            return;
        }
        times++;
        PRINTF("times: %d", times);
    }
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
    while (1) {
        conn_fd = accept(listen_fd, (struct sockaddr *) &client_addr, &cli_len);
        read_data(conn_fd);
        close(conn_fd);
        break;
    }
    return EXIT_SUCCESS;
}