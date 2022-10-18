#define _GNU_SOURCE         /* See feature_test_macros(7) */
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "include/common.h"
#include "include/http_server.h"
#include "include/event_loop.h"

int on_req(struct http_request* req, struct http_response* rsp) {
	char* url = req->url;
	char* question = memmem(url, strlen(url), "?", 1);
	char* path = NULL;
	if (question != NULL) {
		path = malloc(question - url);
		strncpy(path, url, question - url);
	} else {
		path = malloc(strlen(url));
		strncpy(path, url, strlen(url));
	}
	if (strcmp(path, "/") == 0) {
		rsp->code = OK;
		rsp->stats_msg = "OK";
		rsp->content_type = "text/html";
		rsp->body = "<html><head><title>This is a Test</title></head><body><h1>Hello</h1></body></html>";
	} else if (strcmp(path, "/network") == 0) {
		rsp->code = OK;
		rsp->stats_msg = "OK";
		rsp->content_type = "text/html";
		rsp->body = "hello, nw";
	} else {
		rsp->code = NOT_FOUND;
		rsp->stats_msg = "Not Found";
		rsp->content_type = "text/html";
		rsp->body = "NOT_FOUND";
		rsp->keep_connected = 1;
	}
	return 0;
}
int main(int argc, char* argv[]) {
	struct event_loop* loop = event_loop_init();
	struct http_server* server = http_server_new(loop, SERVER_PORT, on_req, 2);
	http_server_start(server);
	event_loop_run(loop);
	return 0;
}
