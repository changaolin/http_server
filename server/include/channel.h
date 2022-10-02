#ifndef CHANNEL_H
#define CHANNEL_H
#define EVENT_TMOUT 0x01
#define EVENT_READ 0x02
#define EVENT_WRITE 0x04
#define EVENT_SIGNAL 0x08
typedef int(*event_read_cb)(void* data);
typedef int(*event_write_cb)(void* data);

struct channel {
	int fd;
	int events;
	event_read_cb read_cb;
	event_write_cb write_cb;
	void* data;
};


struct channel*
channel_new(int fd, int events, event_read_cb read_cb, event_write_cb write_cb, void* data);

int channel_write_event_is_enabled(struct channel* channel);

int channel_write_event_enable(struct channel* channel);

int channel_write_event_disable(struct channel* channel);
#endif // CHANNEL_H
