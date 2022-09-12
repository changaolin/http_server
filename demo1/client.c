//
// Created by changaolin on 2022/9/10.
//

#include "common.h"

#define MAX_BUF_SIZE 10240

void send_data(int sock) {
    int n;
    char query[MAX_BUF_SIZE];
    memset(query, '1', MAX_BUF_SIZE);
    query[MAX_BUF_SIZE - 1] = '\0';
    const char *send_p = query;
    int remain = MAX_BUF_SIZE;
    while (remain > 0) {
        if ((n = send(sock, send_p, remain, 0)) <= 0) {
            PRINTF("send failed");
            return;
        }
        remain -= n;
        send_p += n;
    }
    return;
}

int main(int argc, char *argv[]) {
    int server_fd;
    struct sockaddr_in server_addr;
    bzero(&server_addr, sizeof(server_addr));
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERVER_PORT);
    inet_pton(AF_INET, SERVER_ADDR, &server_addr.sin_addr);
    int connect_rt = connect(server_fd, (struct sockaddr *) &server_addr, sizeof(server_addr));
    if (connect_rt < 0) {
        perror("connect failed!");
        return EXIT_FAILURE;
    }
    send_data(server_fd);
    return EXIT_SUCCESS;
}
