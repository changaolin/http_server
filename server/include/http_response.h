#ifndef HTTP_RESPONSE_H
#define HTTP_RESPONSE_H
#include "buffer.h"
struct response_header {
	char* key;
	char* value;
};

enum http_rsp_stats_code {
	UNKNOWN,
	OK = 200,
	MOVED_PERMANENTLY = 301,
	BAD_REQUEST = 400,
	NOT_FOUND = 404,
};
struct http_response {
	enum http_rsp_stats_code code;
	char* stats_msg;
	char* content_type;
	char* body;
	struct response_header* headers;
	int response_header_cnt;
	int keep_connected;
};
struct http_response* http_response_new();
void http_rsp_encode_buffer(struct http_response* rsp, struct buffer* buf);
#endif // HTTP_RESPONSE_H
