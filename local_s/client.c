#include "common.h"

int main(int argc, char* argv[]) 
{
	int sock_fd = socket(AF_LOCAL, SOCK_STREAM, 0);
	struct sockaddr_un server_addr;
	bzero(&server_addr, sizeof(server_addr));

	server_addr.sun_family = AF_LOCAL;
	strcpy(server_addr.sun_path, LOCAL_SOCK);
	if (connect(sock_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
		PRINTF("connect fail!\n");
		close(sock_fd);
		return EXIT_FAILURE;
	}
	PRINTF("conn success!");
	char send_line[MESSAGE_MAX_LINE];
	char recv_line[MESSAGE_MAX_LINE];
	bzero(send_line, MESSAGE_MAX_LINE);

	PRINTF("wait input...");
	while(fgets(send_line, MESSAGE_MAX_LINE, stdin) != NULL) {
		int n_bytes = strlen(send_line);
		PRINTF("write...");
		if (write(sock_fd, send_line, n_bytes) != n_bytes) {
			PRINTF("write fail1");
			close(sock_fd);
			return EXIT_FAILURE;
		}
		PRINTF("read...");
		if (read(sock_fd, recv_line, MESSAGE_MAX_LINE) == 0) {
			PRINTF("read fail!");
			close(sock_fd);
			return EXIT_FAILURE;
		}
		fputs(recv_line, stdout);
		fputs("\n", stdout);
	}
	close(sock_fd);
	return EXIT_SUCCESS;
}
