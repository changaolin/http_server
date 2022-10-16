#include "common.h"
#include "http_response.h"
#define INIT_RESPONSE_HEADER_SIZE 128

struct http_response* http_response_new() {
	struct http_response* rsp = malloc(sizeof(struct http_response));
	rsp->body = NULL;
	rsp->code = UNKNOWN;
	rsp->headers = malloc(sizeof(struct http_response) * INIT_BUFFER_SIZE);
	rsp->response_header_cnt = 0;
	rsp->keep_connected = 0;
	return rsp;
}

void http_rsp_encode_buffer(struct http_response* rsp, struct buffer* buf) {
	int i;
	char tmp_char[64];
	snprintf(tmp_char, sizeof(tmp_char), "HTTP/1.1 %d ", rsp->code);
	buffer_append_string(buf, tmp_char);
	buffer_append_string(buf, rsp->stats_msg);
	buffer_append_string(buf, "\r\n");
	if (rsp->keep_connected) {
		buffer_append_string(buf, "Connection: close\r\n");
	} else {
		snprintf(tmp_char, sizeof(tmp_char), "Content-Length: %zd\r\n", strlen(rsp->body));
		buffer_append_string(buf, tmp_char);
		buffer_append_string(buf, "Connection: Keep-Alive\r\n");
	}
	if (rsp->headers != NULL && rsp->response_header_cnt > 0) {
		for (i = 0; i < rsp->response_header_cnt; i++) {
			buffer_append_string(buf, rsp->headers[i].key);
			buffer_append_string(buf, ": ");
			buffer_append_string(buf, rsp->headers[i].value);
			buffer_append_string(buf, "\r\n");
		} 
	}
	buffer_append_string(buf, "\r\n");
	buffer_append_string(buf, rsp->body);
}
