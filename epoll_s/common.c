//
// Created by changaolin on 2022/9/10.
//

#include "common.h"

#define MAX_LOG_LINE_SIZE 4096

void write_log(const char *file, const char *function,
               int line, const char *fmt, ...) {
    char buf[MAX_LOG_LINE_SIZE + 1];
    char *file_name = strrchr(file, '/') + 1;
    int len = sprintf(buf, "[%s::%s:%d]", file_name, function, line);
    va_list arg;
    va_start(arg, fmt);
    len += vsnprintf(buf + len, MAX_LOG_LINE_SIZE - len, fmt, arg);
    va_end(arg);
    fprintf(stderr, "%s\n", buf);
}

int read_n(int fd, void *buffer, int buffer_size, int read_size) {
    if (buffer_size < read_size) {
        return -1;
    }
    char *read_p = (char *) buffer;
    int len = read_size;
    int result;
    while (len > 0) {
        result = read(fd, read_p, len);
        if (result == 0) break; // EOF, 收到 FIN包
        if (result < 0) {
            // 非阻塞io的情况下，没有数据可读
            if (errno == EINTR) continue;
            else return -1;
        }
        len -= result;
        read_p += result;
    }
    return read_size - len; // 返回实际读取的字符数
}

int tcp_client(char* addr, int port) {
	int sock = socket(AF_INET, SOCK_STREAM, 0);
	struct sockaddr_in server_addr;
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(port);
    inet_pton(AF_INET, addr, &server_addr.sin_addr);
	int co_rt = connect(sock, (struct sockaddr*)&server_addr, sizeof(server_addr));
	if (co_rt < 0) {
		PRINTF("connect fail!");
		return -1;
	}
	return sock;
}

int tcp_server(char* addr, int port, int listen_count) {
	int sock = socket(AF_INET, SOCK_STREAM, 0);
	struct sockaddr_in server_addr;
    bzero(&server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERVER_PORT);
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);

    bind(sock, (struct sockaddr *) &server_addr, sizeof(server_addr));
    listen(sock, listen_count);
	PRINTF("listen... sk:%d", sock);
	return sock;
}
int tcp_nonblocking_server_listen(int port) {
    int listenfd;
    listenfd = socket(AF_INET, SOCK_STREAM, 0);
	make_nonblocking(listenfd);

    struct sockaddr_in server_addr;
    bzero(&server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(port);

    int on = 1;
    setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));

    int rt1 = bind(listenfd, (struct sockaddr *) &server_addr, sizeof(server_addr));
    if (rt1 < 0) {
        PRINTF("bind failed ");
		return -1;
    }

    int rt2 = listen(listenfd, 1024);
    if (rt2 < 0) {
        PRINTF("listen failed ");
    }

    signal(SIGPIPE, SIG_IGN);

    return listenfd;
}
void make_nonblocking(int fd) {
    fcntl(fd, F_SETFL, O_NONBLOCK);
}
