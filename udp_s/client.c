#include "common.h"

int main(int argc, char* argv[]) 
{
	int sock_fd = socket(AF_INET, SOCK_DGRAM, 0);
	struct sockaddr_in server_addr;
	bzero(&server_addr, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(SERVER_PORT);
	inet_pton(AF_INET, SERVER_ADDR, &server_addr.sin_addr);
	socklen_t server_len = sizeof(server_addr);

	char send_line[MESSAGE_MAX_LINE];
	char recv_line[MESSAGE_MAX_LINE + 1];
	socklen_t len;
	int n;
	fputs("wait input...\n", stdout);
	while (fgets(send_line, MESSAGE_MAX_LINE, stdin) != NULL) {
		int i = strlen(send_line);
		if (send_line[i-1] == '\n') {
			send_line[i-1] = '\0';
		}
		PRINTF("now sending: %s", send_line);
		int rt = sendto(sock_fd, send_line, strlen(send_line), 0,
			(struct sockaddr*)&server_addr, server_len);
		if (rt < 0) {
			PRINTF("send fail!");
			close(sock_fd);
			return EXIT_FAILURE;
		}
		len = 0;
		PRINTF("wait recv...");
		n = recvfrom(sock_fd, recv_line, MESSAGE_MAX_LINE, 0,
			(struct sockaddr*)&server_addr, &len);
		if (n < 0) {
			PRINTF("recv fail!");
			close(sock_fd);
			return EXIT_FAILURE;
		}
		recv_line[n] = '\0';
		fputs(recv_line, stdout);
		fputs("\n", stdout);
	}
	return EXIT_SUCCESS;
}
