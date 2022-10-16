#ifndef TCP_SERVER_H
#define TCP_SERVER_H
#include "thread_pool.h"
#include "acceptor.h"
#include "tcp_connection.h"
struct TCPServer {
	int potr;
	struct event_loop* loop;
	struct acceptor* acpt;
	connection_completed_cb conn_cplt_cb;
	message_cb msg_cb;
	write_completed_cb write_cplt_cb;
	connection_closed_cb conn_closed_cb;

	int thread_num;
	struct thread_pool* pool;
	void* data;
};

struct TCPServer*
tcp_server_init(struct event_loop* loop, struct acceptor* acpt, connection_completed_cb cccb,
	message_cb msg_cb, write_completed_cb write_cb, connection_closed_cb cclcb, int thread_num);

void tcp_server_start(struct TCPServer* tcp_server);

void tcp_server_set_data(struct TCPServer* tcp_server, void* data); 
#endif // TCP_SERVER_H
