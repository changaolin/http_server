#include "common.h"
int main(int argc, char **argv) {
    int socket_fd;
    socket_fd = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in server_addr;
    bzero(&server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERVER_PORT);
    inet_pton(AF_INET, SERVER_ADDR, &server_addr.sin_addr);

    socklen_t server_len = sizeof(server_addr);
    int connect_rt = connect(socket_fd, (struct sockaddr *) &server_addr, server_len);
    if (connect_rt < 0) {
        PRINTF("connect failed ");
		return EXIT_FAILURE;
    }

    char buf[128];
    struct iovec iov[2];

    char *send_one = "hello,";
    iov[0].iov_base = send_one;
    iov[0].iov_len = strlen(send_one);
    iov[1].iov_base = buf;
	PRINTF("wait input...");
    while (fgets(buf, sizeof(buf), stdin) != NULL) {
        iov[1].iov_len = strlen(buf);
        int n = htonl(iov[1].iov_len);
        if (writev(socket_fd, iov, 2) < 0)
            PRINTF("writev failure");
			return EXIT_FAILURE;
    }
    exit(0);
}
