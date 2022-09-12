#include "common.h"
int main(int argc, char* argv[])
{
	int listen_fd, conn_fd;
	socklen_t client_len;
	struct sockaddr_un server_addr;
	struct sockaddr_un client_addr;
	listen_fd = socket(AF_LOCAL, SOCK_STREAM, 0);
	char* local_path = LOCAL_SOCK;
	/*
     unlink()会删除参数pathname 指定的文件.
	 如果该文件名为最后连接点, 但有其他进程打开了此文件,
	 则在所有关于此文件的文件描述词皆关闭后才会删除.
	 如果参数pathname 为一符号连接, 则此连接会被删除
	*/
	unlink(local_path);

	bzero(&server_addr, sizeof(server_addr));
	server_addr.sun_family = AF_LOCAL;
	strcpy(server_addr.sun_path, local_path);
	int ret = bind(listen_fd, (struct sockaddr*)&server_addr, sizeof(server_addr));
	if (ret < 0) {
		PRINTF("bind fail!");
		return EXIT_FAILURE;
	}
	PRINTF("listen...");
	ret = listen(listen_fd, 1024);
	if (ret < 0) {
		PRINTF("listen fail!");
		return EXIT_FAILURE;
	}
	client_len = sizeof(client_addr);
	PRINTF("wait accept...");
	conn_fd = accept(listen_fd, (struct sockaddr*)&client_addr, &client_len);
	if (conn_fd < 0) {
		if (errno == EINTR) {
			PRINTF("accept fail!");
		} else {
			PRINTF("accept fail!");
		}
		return EXIT_FAILURE;
	}

	char buf[MESSAGE_MAX_LINE];
	while (1) {
		bzero(buf, MESSAGE_MAX_LINE);
		PRINTF("read...");
		if (read(conn_fd, buf, MESSAGE_MAX_LINE) == 0) {
			PRINTF("client quit!");
			break;
		}
		PRINTF("recvb: %s", buf);
		char send_line[MESSAGE_MAX_LINE + 3];

		sprintf(send_line, "HI %s", buf);
		PRINTF("write...");
		int n_bytes = strlen(send_line);
		if (write(conn_fd, send_line, n_bytes) != n_bytes) {
			PRINTF("write fail!");
			return EXIT_FAILURE;
		}
	}
	close(listen_fd);
	close(conn_fd);
	return EXIT_SUCCESS;
}
