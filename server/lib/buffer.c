#define _GNU_SOURCE         /* See feature_test_macros(7) */
#include <string.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
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

void make_room(struct buffer* buf, int size) {
	if (buffer_writeable_size(buf) >= size) {
		return;
	}
	if (buffer_front_spare_size(buf) + buffer_writeable_size(buf) >= size) {
		int readable = buffer_readable_size(buf);
		int i = 0;
		for (i = 0; i < readable; i++) {
			memcpy(buf->data + i, buf->data + buf->read_index + i, 1);
		}
		buf->read_index = 0;
		buf->write_index = readable;
	} else {
		void* tmp = realloc(buf->data, buf->total_size + size);
		if (tmp == NULL) {
			return;
		}
		buf->data = tmp;
		buf->total_size += size;
	}
}
int buffer_append(struct buffer* buf, void* data, int size) {
	if (data == NULL) {
		return -1;
	}
	make_room(buf, size);
	memcpy(buf->data + buf->write_index, data, size);
	buf->write_index += size;
	return 0;
}

int buffer_append_char(struct buffer* buf, char data) {
	make_room(buf, 1);
	buf->data[buf->write_index++] = data;
	return 0;
}
int buffer_append_string(struct buffer* buf, char* data) {
	if (data == NULL) {
		return 0;
	}
	int size = strlen(data);
	buffer_append(buf, data, size);
	return 0;
}
int buffer_socket_read(struct buffer* buf, int fd) {
	char add_buf[INIT_BUFFER_SIZE];
	struct iovec vec[2];
	int max_writable = buffer_writeable_size(buf);
	vec[0].iov_base = buf->data + buf->write_index;
	vec[0].iov_len = max_writable;
	vec[1].iov_base = add_buf;
	vec[1].iov_len = sizeof(add_buf);

	int result = readv(fd, vec, 2);
	if (result < 0) {
		return -1;
	} else if (result <= max_writable) {
		buf->write_index += result;
	} else {
		buf->write_index = buf->total_size;
		buffer_append(buf, add_buf, result - max_writable);
	}
	return result;
}
char* buffer_find_CRLF(struct buffer* buf) {
	char* crlf = memmem(buf->data + buf->read_index, buffer_readable_size(buf), CRLF, 2);
	return crlf;
}
