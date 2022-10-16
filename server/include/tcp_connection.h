#ifndef TCP_CONNECTION_H
#define TCP_CONNECTION_H
#include "buffer.h"
struct tcp_connection;
typedef int (*connection_completed_cb)(struct tcp_connection*);
typedef int (*message_cb)(struct buffer*, struct tcp_connection*);
typedef int (*write_completed_cb)(struct tcp_connection*);
typedef int (*connection_closed_cb)(struct tcp_connection*);

struct tcp_connection {
	struct event_loop* loop;
	struct channel* chan;
	char* name;
	struct buffer* input_buf;
	struct buffer* output_buf;
	
	connection_completed_cb conn_cplt_cb;
	message_cb msg_cb;
	write_completed_cb write_cplt_cb;
	connection_closed_cb conn_closed_cb;

	void* data;
	void* request;
	void* response;
};

struct tcp_connection*
tcp_connection_new(int fd, struct event_loop* loop, connection_completed_cb cccb, connection_closed_cb cclcb, message_cb msg_cb, write_completed_cb w_cb);

int tcp_connection_send_data(struct tcp_connection* tcp_conn, void* data, int size);

int tcp_connection_send_buffer(struct tcp_connection* tcp_conn, struct buffer* buf);

void tcp_connection_shutdown(struct tcp_connection* tcp_conn);

#endif // TCP_CONNECTION_H
