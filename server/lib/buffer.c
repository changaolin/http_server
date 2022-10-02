#include "common.h"
#include "buffer.h"
const char* CRLF = "\r\n";

struct buffer* buffer_new() {
	struct buffer* buf = malloc(sizeof(struct buffer));
	if (buf == NULL) {
		return NULL;
	}
	buf->data = malloc(INIT_BUFFER_SIZE);
	buf->total_size = INIT_BUFFER_SIZE;
	buf->read_index = 0;
	buf->write_index = 0;
	return buf;
}

void buffer_free(struct buffer* buf) {
	if (buf == NULL) {
		return;
	}
	if (buf->data != NULL) {
		free(buf->data);
		buf->data = NULL;
	}
	free(buf);
	buf = NULL;
}

int buffer_writeable_size(struct buffer* buf) {
	return buf->total_size - buf->write_index;
}

int buffer_readable_size(struct buffer* buf) {
	return buf->write_index - buf->read_index;
}

int buffer_front_spare_size(struct buffer* buf) {
	return buf->read_index;
}
