#ifndef HTTP_SERVER_H
#define HTTP_SERVER_H

#include "tcp_server.h"
#include "http_request.h"
#include "http_response.h"

typedef int (*req_callback)(struct http_request* req, struct http_response* rsp);

struct http_server {
	struct TCPServer* tcp_server;
	req_callback req_cb;
};
struct http_server* http_server_new(struct event_loop* loop, int port, req_callback req_cb, int thread_num);
void http_server_start(struct http_server* server);
int parse_http_request(struct buffer* input, struct http_request* req);
#endif // HTTP_SERVER_H

