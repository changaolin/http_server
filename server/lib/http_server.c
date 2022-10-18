#define _GNU_SOURCE         /* See feature_test_macros(7) */
#include <string.h>
#include <assert.h>
#include "http_server.h"

int http_on_conn_cmlt(struct tcp_connection* conn) {
	INFO_LOG("conn completed");
	struct http_request* req = http_request_new();
	conn->request = req;
	return 0;
}
int process_status_line(char* start, char* end, struct http_request* req) {
	int all_size = end - start;
	// methond
	char* space = memmem(start, end - start, " ", 1);
	assert(space != NULL);
	int size = space - start;
	req->method = malloc(size - 1);
	strncpy(req->method, start, space - start);
	req->method[size + 1] = '\0';
	// url	
	start = space + 1;
	space = memmem(start, end - start, " ", 1);
	assert(space != NULL);
	size = space - start;
	req->url = malloc(size + 1);
	strncpy(req->url, start, space - start);
	req->url[size + 1] = '\0';
	// version
	start = space + 1;
	req->version = malloc(end - start + 1);
	strncpy(req->version, start, end - start);
	req->version[size + 1] = '\0';
	return all_size;
}

int parse_http_request(struct buffer* input, struct http_request* req) {
	int ok = 1;
	while (req->state != REQUEST_DONE) {
		if (req->state == REQUEST_STATUS) {
			char* crlf = buffer_find_CRLF(input);
			if (crlf) {
				int req_line_size = process_status_line(input->data + input->read_index, crlf, req);
				if (req_line_size) {
					input->read_index += req_line_size; // rea line size
					input->read_index += 2; // CRLF
					req->state = REQUEST_HEADERS;
				}
			}
		} else if (req->state == REQUEST_HEADERS) {
			char* crlf = buffer_find_CRLF(input);
			if (crlf) {
				/* <start>--<colon:>--<crlf>*/
				char* start = input->data + input->read_index;
				int req_line_size = crlf - start;
				char* colon = memmem(start, req_line_size, ": ", 2);
				if (colon != NULL) {
					char* key = malloc(colon - start + 1);
					strncpy(key, start, colon - start);
					key[colon - start] = '\0';
					char* value = malloc(crlf - colon - 2 + 1);
					strncpy(value, colon + 2, crlf - colon - 2);
					value[crlf - colon - 2] = '\0';
					http_request_add_header(req, key, value);
					input->read_index += req_line_size;
					input->read_index += 2;
				} else {
					// 读到这里说明没找到，这是最后一行
					input->read_index += 2;
					req->state = REQUEST_DONE;
				}
			
			}
		}
	}
	return ok;
}
int http_on_msg(struct buffer* input, struct tcp_connection* conn) {
	INFO_LOG("get msg from tcp conn %s", conn->name);
	struct http_request* req = (struct http_request*) conn->request;
	struct http_server* server = (struct http_server*) conn->data;
	if (server == NULL) {
		abort();
		return -1;
	}
	if (parse_http_request(input, req) == 0) {
		char* err_rsp = "HTTP/1.1 400 Bad Request\r\n\r\n";
		tcp_connection_send_data(conn, err_rsp, sizeof(err_rsp));
		tcp_connection_shutdown(conn);
	}
	if (http_request_cur_state(req) == REQUEST_DONE) {
		struct http_response* rsp = http_response_new();
		if (server->req_cb != NULL) {
			server->req_cb(req, rsp);
		}
		struct buffer* buffer = buffer_new();
		http_rsp_encode_buffer(rsp, buffer);
		tcp_connection_send_buffer(conn, buffer);
		if (http_request_close_connection(req)) {
			tcp_connection_shutdown(conn);
		}
		http_request_reset(req);
	}
	return 0;
}
int http_on_write_cmpl(struct tcp_connection* conn) {
	INFO_LOG("write completed");
	return 0;
}
int http_on_conn_closed(struct tcp_connection* conn) {
	INFO_LOG("conn closed");
	if (conn->request == NULL) {
		return 0;
	}
	http_request_clear(conn->request);
	conn->request = NULL;
	return 0;
}
struct http_server* http_server_new(struct event_loop* loop, int port, req_callback req_cb, int thread_num) {
	struct http_server* server = malloc(sizeof(struct http_server));
	server->req_cb = req_cb;
	struct acceptor* acpt = acceptor_init(port);
	server->tcp_server = tcp_server_init(loop, acpt, http_on_conn_cmlt, http_on_msg, http_on_write_cmpl, http_on_conn_closed, thread_num);
	server->tcp_server->data = server;
	return server;
}
void http_server_start(struct http_server* server) {
	tcp_server_start(server->tcp_server);
}

