#include "common.h"
#include "http_request.h"
#define INIT_REQEST_HEADER_SIZE 128
const char* HTTP1_0 = "HTTP1.0";
const char* HTTP1_1 = "HTTP1.1";
const char* KEEP_ALIVE = "Keep-Alive";
const char* CLOSE = "close";

struct http_request* http_request_new() {
	struct http_request* req = malloc(sizeof(struct http_request));
	req->method = NULL;
	req->state = REQUEST_STATUS;
	req->version = NULL;
	req->url = NULL;
	req->headers = malloc(sizeof(struct http_request) * INIT_REQEST_HEADER_SIZE);
	req->req_header_count = 0;
	return req;
}
void http_request_clear(struct http_request* req) {
	int i;
	if (req->headers == NULL) {
		free(req);
		return;
	}
	for (i = 0; i < req->req_header_count; i++) {
		free(req->headers[i].key);
		free(req->headers[i].value);
	}
	free(req->headers);
}
void http_request_reset(struct http_request* req) {
	req->method = NULL;
	req->state = REQUEST_STATUS;
	req->version = NULL;
	req->url = NULL;
	req->req_header_count = 0;
}
void http_request_add_header(struct http_request* req, char* key, char* value) {
	req->headers[req->req_header_count].key = key;
	req->headers[req->req_header_count].value = value;
	req->req_header_count++;
}
char* http_request_get_header(struct http_request* req, char* key) {
	int i;
	if (req->headers == NULL) return NULL;
	for (i = 0; i < req->req_header_count; i++) {
		if (strncmp(req->headers[i].key, key, strlen(req->headers[i].key)) == 0) {
			return req->headers[i].value;
		}
	}
	return NULL;
}

enum http_req_state http_request_cur_state(struct http_request* req) {
	return req->state;
}

int http_request_close_connection(struct http_request* req) {
	char* conn = http_request_get_header(req, "Connection");
	if (conn != NULL && strncmp(conn, CLOSE, strlen(CLOSE)) == 0) {
		return 1;
	}
	if (req->version != NULL && strncmp(req->version, HTTP1_0, strlen(HTTP1_0)) == 0 && 
		strncmp(conn, KEEP_ALIVE, strlen(KEEP_ALIVE)) == 1) {
		return 1;
	}
	return 0;
}
