#ifndef BUFFER_H
#define BUFFER_H
#define INIT_BUFFER_SIZE 65536
struct buffer {
	char* data;
	int read_index;
	int write_index;
	int total_size;
};

struct buffer* buffer_new();
void buffer_free(struct buffer* buf);

int buffer_writeable_size(struct buffer* buf);
int buffer_readable_size(struct buffer* buf);
int buffer_front_spare_size(struct buffer* buf);

int buffer_append(struct buffer* buf, void* data, int size);
int buffer_append_char(struct buffer* buf, char data);
int buffer_append_string(struct buffer* buf, char* data);
int buffer_socket_read(struct buffer* buf, int fd);
int buffer_read_char(struct buffer* buf);
char* buffer_find_CRLF(struct buffer* buf);
#endif // BUFFER_H
