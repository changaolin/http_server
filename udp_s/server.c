#include "common.h"
static int count;
static void recvfrom_int(int sig) {
	PRINTF("recv: %d", sig);
	exit(0);
}

int main(int argc, char* argv[])
{
	int sock_fd = socket(AF_INET, SOCK_DGRAM, 0);
	struct sockaddr_in server_addr;
	bzero(&server_addr, sizeof(server_addr));

	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	server_addr.sin_port = htons(SERVER_PORT);

	bind(sock_fd, (struct sockaddr*)&server_addr, sizeof(server_addr));

	char message[MESSAGE_MAX_LINE];
	count = 0;
	signal(SIGINT, recvfrom_int);
	struct sockaddr_in client_addr;
	socklen_t client_len = sizeof(client_addr);
	while (1) {
		PRINTF("wait recv");
		int n = recvfrom(sock_fd, message, MESSAGE_MAX_LINE, 0,
			(struct sockaddr*)&client_addr, &client_len);
		message[n] = '\0';
		PRINTF("recv: %s", message);
		char send_line[MESSAGE_MAX_LINE + 3];
		sprintf(send_line, "HI %s", message);
		PRINTF("send: %s", send_line);
		sendto(sock_fd, send_line, strlen(send_line), 0,
			(struct sockaddr*)&client_addr, client_len);
		count++;
		
	}
	return EXIT_SUCCESS;
}
