#ifndef HTTP_REQUEST_H
#define HTTP_REQUEST_H
struct req_header {
	char* key;
	char* value;
};
enum http_req_state {
	REQUEST_STATUS, // 等待解析 
	REQUEST_HEADERS, // 等待解析 header
	REQUEST_BODY,  // 等待解析body
	REQUEST_DONE // 解析完成
};

struct http_request {
	char* version;
	char* method;
	char* url;
	enum http_req_state state;
	struct req_header* headers;
	int req_header_count;
};
struct http_request* http_request_new();
void http_request_clear(struct http_request* req);
void http_request_reset(struct http_request* req);
void http_request_add_header(struct http_request* req, char* key, char* value);
char* http_request_get_header(struct http_request* req, char* key);
enum http_req_state http_request_cur_state(struct http_request* req);
int http_request_close_connection(struct http_request* req);
#endif // HTTP_REQUEST_H
