#include <unistd.h>
#include "tcp_connection.h"
#include "event_loop.h"
#include "buffer.h"

int handle_connection_closed(struct tcp_connection* tcp_conn) {
	struct event_loop* loop = tcp_conn->loop;
	struct channel* chan = tcp_conn->chan;

	event_loop_remove_channel_event(loop, chan->fd, chan);
	if (tcp_conn->conn_closed_cb != NULL) {
		tcp_conn->conn_closed_cb(tcp_conn);
	}
	return 0;
}

int handle_read(void* data) {
	struct tcp_connection* tcp_conn = (struct tcp_connection*) data;
	struct buffer* inp_buf = tcp_conn->input_buf;
	struct channel* chan = tcp_conn->chan;

	if (buffer_socket_read(inp_buf, chan->fd) > 0) {
		if (tcp_conn->msg_cb != NULL) {
			tcp_conn->msg_cb(inp_buf, tcp_conn);
		}
	} else {
		handle_connection_closed(tcp_conn);
	}
	return 0;
}

int handle_write(void* data) {
	struct tcp_connection* tcp_conn = (struct tcp_connection*)data;
	struct event_loop* loop = tcp_conn->loop;
	assert_in_same_thread(loop);

	struct buffer* out_buf = tcp_conn->output_buf;

	struct channel* chan = tcp_conn->chan;

	ssize_t nwrited = write(chan->fd, out_buf->data + out_buf->read_index, buffer_readable_size(out_buf));

	if (nwrited <= 0) {
		INFO_LOG("handle_write for tcp_connection %s", tcp_conn->name);
		return 0;
	}
	out_buf->read_index += nwrited;

	if (buffer_readable_size(out_buf) == 0) {
		channel_write_event_disable(chan);
	}
	if (tcp_conn->write_cplt_cb != NULL) {
		tcp_conn->write_cplt_cb(tcp_conn);
	}
	return 0;
}

struct tcp_connection*
tcp_connection_new(int fd, struct event_loop* loop, connection_completed_cb cccb, connection_closed_cb cclcb, message_cb msg_cb, write_completed_cb w_cb)
{
	struct tcp_connection* tcp_conn = malloc(sizeof(struct tcp_connection));

	tcp_conn->write_cplt_cb= w_cb;
	tcp_conn->msg_cb = msg_cb;
	tcp_conn->conn_cplt_cb= cccb;
	tcp_conn->conn_closed_cb= cclcb;

	tcp_conn->loop = loop;
	tcp_conn->input_buf = buffer_new();
	tcp_conn->output_buf = buffer_new();

	tcp_conn->name = malloc(16);
	bzero(tcp_conn->name, 16);
	sprintf(tcp_conn->name, "connection-%d", fd);
	struct channel* chan = channel_new(fd, EVENT_READ, handle_read, handle_write, tcp_conn);
	tcp_conn->chan = chan;
	if (tcp_conn->conn_cplt_cb != NULL) {
		tcp_conn->conn_cplt_cb(tcp_conn);
	}
	event_loop_add_channel_event(tcp_conn->loop, fd, tcp_conn->chan);
	return tcp_conn;
}

int tcp_connection_send_data(struct tcp_connection* tcp_conn, void* data, int size) {
	size_t nwrited = 0;
	size_t nleft = size;
	int fault;

	struct channel* chan = tcp_conn->chan;
	struct buffer* out_buf = tcp_conn->output_buf;

	if (!channel_write_event_is_enabled(chan) && buffer_readable_size(out_buf) == 0) {
		nwrited = write(chan->fd, data, size);
		if (nwrited >= 0) {
			nleft = nleft - nwrited;
		} else {
			nwrited = 0;
			if (errno != EWOULDBLOCK) {
				if (errno == EPIPE || errno == ECONNRESET) {
					fault = 1;
				}
			}
		}
	}

	if (!fault && nleft > 0) {
		buffer_append(out_buf, data + nwrited, nleft);
		if (!channel_write_event_is_enabled(chan)) {
			channel_write_event_enable(chan);
		}
	}
	return nwrited;
}

int tcp_connection_send_buffer(struct tcp_connection* conn, struct buffer* buf) {
	int size = buffer_readable_size(buf);
	int result = tcp_connection_send_data(conn, buf->data + buf->read_index, size);
	buf->read_index += size;
	return result;
}
void tcp_connection_shutdown(struct tcp_connection* conn) {
	if (shutdown(conn->chan->fd, SHUT_WR) < 0) {
		ERROR_LOG("tcp conn shutdown failed, sock = %d", conn->chan->fd);
	}
}
