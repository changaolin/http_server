#include <signal.h>
#include "log.h"
#include "tcp_server.h"
int tcp_server(int port) {
	int listen_fd = socket(AF_INET, SOCK_STREAM, 0);
	struct sockaddr_in server_addr;
	bzero(&server_addr, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	server_addr.sin_port = htons(port);

	int on = 1;
	setsockopt(listen_fd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));

	int ret = bind(listen_fd, (struct sockaddr*)&server_addr, sizeof(server_addr));

	if (ret < 0) {
		ERROR_LOG("bind failed");
		return -1;
	}
	ret = listen(listen_fd, 1024);
	if (ret < 0) {
		ERROR_LOG("listen failed");
		return -1;
	}
	signal(SIGPIPE, SIG_IGN);

	int connfd;
	struct sockaddr_in client_addr;
	socklen_t client_len = sizeof(client_addr);
	connfd = accept(listen_fd, (struct sockaddr*)&client_addr, &client_len);
	if (connfd < 0) {
		ERROR_LOG("accept failed!");
		return -1;
	}
	return connfd;
}
int tcp_server_listen(int port) {
	int listen_fd = socket(AF_INET, SOCK_STREAM, 0);
	struct sockaddr_in server_addr;
	bzero(&server_addr, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	server_addr.sin_port = htons(port);

	int on = 1;
	setsockopt(listen_fd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));

	int ret = bind(listen_fd, (struct sockaddr*)&server_addr, sizeof(server_addr));

	if (ret < 0) {
		ERROR_LOG("bind failed");
		return -1;
	}
	ret = listen(listen_fd, 1024);
	if (ret < 0) {
		ERROR_LOG("listen failed");
		return -1;
	}
	signal(SIGPIPE, SIG_IGN);
	return listen_fd;
}
int tcp_nonblocking_server_listen(int port) {
	int listen_fd = socket(AF_INET, SOCK_STREAM, 0);
	make_nonblocking(listen_fd);
	struct sockaddr_in server_addr;
	bzero(&server_addr, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	server_addr.sin_port = htons(port);

	int on = 1;
	setsockopt(listen_fd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));

	int ret = bind(listen_fd, (struct sockaddr*)&server_addr, sizeof(server_addr));

	if (ret < 0) {
		ERROR_LOG("bind failed");
		return -1;
	}
	ret = listen(listen_fd, 1024);
	if (ret < 0) {
		ERROR_LOG("listen failed");
		return -1;
	}
	signal(SIGPIPE, SIG_IGN);
	return listen_fd;
}
struct TCPServer*
tcp_server_init(struct event_loop* loop, struct acceptor* acpt, connection_completed_cb cccb,
	message_cb msg_cb, write_completed_cb write_cb, connection_closed_cb cclcb, int thread_num) {
	struct TCPServer* server = malloc(sizeof(struct TCPServer));
	server->loop = loop;
	server->acpt = acpt;
	server->conn_cplt_cb = cccb;
	server->msg_cb= msg_cb;
	server->conn_closed_cb = cclcb;
	server->thread_num = thread_num;
	server->pool = thread_pool_new(loop, thread_num);
	server->data = NULL;
	return server;
}
int handle_conn_established(void* data) {
	struct TCPServer* server = (struct TCPServer*) data;
	struct acceptor* acpt = server->acpt;
	int listen_fd = acpt->listen_fd;

	struct sockaddr_in client_addr = {0};
	socklen_t client_len = sizeof(client_addr);
	int conn_fd = accept(listen_fd, (struct sockaddr*)&client_addr, &client_len);

	make_nonblocking(conn_fd);

	INFO_LOG("new connection established, sock = %d", conn_fd);
	struct event_loop* loop = thread_pool_get_loop(server->pool);
	struct tcp_connection* conn = tcp_connection_new(conn_fd, loop, server->conn_cplt_cb, 
			server->conn_closed_cb, server->msg_cb, server->write_cplt_cb);
	if (server->data != NULL ) {
		conn->data = server->data;
	}
	return 0;

}
void tcp_server_start(struct TCPServer* tcp_server) {
	struct acceptor* acpt = tcp_server->acpt;
	struct event_loop* loop = tcp_server->loop;

	thread_pool_start(tcp_server->pool);
	struct channel* chan = channel_new(acpt->listen_fd, EVENT_READ, handle_conn_established, NULL, tcp_server);
	event_loop_add_channel_event(loop, chan->fd, chan);
	return;
}

void tcp_server_set_data(struct TCPServer* tcp_server, void* data) {
	if (data != NULL) {
		tcp_server->data = data;
	}
} 
