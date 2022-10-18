#include "common.h"
#include "event_loop.h"
#include "channel.h"
struct channel*
channel_new(int fd, int events, event_read_cb read_cb, event_write_cb write_cb, void* data)
{
	struct channel* chan = malloc(sizeof(struct channel));
	if (chan == NULL) {
		return NULL;
	}
	chan->fd = fd;
	chan->events = events;
	chan->read_cb = read_cb;
	chan->write_cb = write_cb;
	chan->data = data;
	return chan;
}

int channel_write_event_is_enabled(struct channel* channel)
{
	return channel->events & EVENT_WRITE;
}

int channel_write_event_enable(struct channel* channel)
{
	struct event_loop* loop = (struct event_loop*)channel->data;
	channel->events = channel->events | EVENT_WRITE;
	event_loop_update_channel_event(loop, channel->fd, channel);
	return 0;
}

int channel_write_event_disable(struct channel* channel)
{
	struct event_loop* loop = (struct event_loop*)channel->data;
	channel->events = channel->events | ~EVENT_WRITE;
	event_loop_update_channel_event(loop, channel->fd, channel);
	return 0;
}
