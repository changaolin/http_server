#include <poll.h>
#include "dispatcher_intf.h"
#include "event_loop.h"

#define INIT_POLL_SIZE 1024

struct pollidx {
	int idxplus;
};

struct poll_dspt_data {
	int event_count;
	int nfds;
	int realloc_copy;
	struct pollfd* event_set;
	struct pollfd* event_set_copy;
};

static void* poll_init(struct event_loop*);
static int poll_add(struct event_loop*, struct channel*);
static int poll_del(struct event_loop*, struct channel*);
static int poll_update(struct event_loop*, struct channel*);
static int poll_dispatch(struct event_loop*, struct timeval*);
static void poll_clear(struct event_loop*);

const struct dispatcher poll_dspt = {
	"poll",
	poll_init,
	poll_add,
	poll_del,
	poll_update,
	poll_dispatch,
	poll_clear,
};

const struct dispatcher* get_dispatcher(void) {
	return &poll_dspt;
}
static void* poll_init(struct event_loop* loop) {
	int i;
	struct poll_dspt_data* data = malloc(sizeof(struct poll_dspt_data));
	data->event_set = malloc(sizeof(struct pollfd) * INIT_POLL_SIZE);

	for (i = 0; i < INIT_POLL_SIZE; i++) {
		data->event_set[i].fd = -1;
	}
	data->event_count = 0;
	data->nfds = 0;
	data->realloc_copy = 0;
	return data;
}

static int poll_add(struct event_loop* loop, struct channel* chan) {
	struct poll_dspt_data* data = (struct poll_dspt_data*)loop->dspt_data;
	int fd = chan->fd;
	int events = 0;
	if (chan->events & EVENT_READ) {
		events = events | POLLRDNORM;
	}
	if (chan->events & EVENT_WRITE) {
		events = events | POLLWRNORM;
	}

	int i = 0;
	for (i = 0; i < INIT_POLL_SIZE; i++) {
		if (data->event_set[i].fd < 0) {
			data->event_set[i].fd = fd;
			data->event_set[i].events = events;
			break;
		}
	}
	INFO_LOG("poll added channel fd = %d, %s", fd, loop->thread_name);
	if (i >= INIT_POLL_SIZE) {
		ERROR_LOG("too many clients, just abort it");
	}
	return 0;
}

static int poll_del(struct event_loop* loop, struct channel* chan) {
	struct poll_dspt_data* data = (struct poll_dspt_data*)loop->dspt_data;
	int fd = chan->fd;
	int i = 0;
	for (i = 0; i < INIT_POLL_SIZE; i++) {
		if (data->event_set[i].fd == fd) {
			data->event_set[i].fd = -1;
			break;
		}
	}
	INFO_LOG("poll delet channel fd = %d, %s", fd, loop->thread_name);
	if (i >= INIT_POLL_SIZE) {
		ERROR_LOG("can not find fd = %d, poll delete error!", fd);
		return -1;
	}
	return 0;
}

static int poll_update(struct event_loop* loop, struct channel* chan) {
	struct poll_dspt_data* data = (struct poll_dspt_data*)loop->dspt_data;
	int fd = chan->fd;
	int events = 0;
	if (chan->events & EVENT_READ) {
		events = events | POLLRDNORM;
	}
	if (chan->events & EVENT_WRITE) {
		events = events | POLLWRNORM;
	}

	int i = 0;
	for (i = 0; i < INIT_POLL_SIZE; i++) {
		if (data->event_set[i].fd == fd) {
			data->event_set[i].events = events;
			break;
		}
	}
	INFO_LOG("poll update channel fd = %d, %s", fd, loop->thread_name);
	if (i >= INIT_POLL_SIZE) {
		ERROR_LOG("can not find fd = %d, poll update error!", fd);
		return -1;
	}
	return 0;
}

static int poll_dispatch(struct event_loop* loop, struct timeval* tmval) {
	struct poll_dspt_data* data = (struct poll_dspt_data*)loop->dspt_data;
	int ready_number = 0;
	int timewait = tmval->tv_sec * 1000;
	if ((ready_number = poll(data->event_set, INIT_POLL_SIZE, timewait)) < 0) {
		ERROR_LOG("poll failed");
		return -1;
	}
	if (ready_number <= 0) {
		return 0;
	}
	int i;
	for (i = 0; i <= INIT_POLL_SIZE; i ++) {
		int sock_fd;
		struct pollfd pollfd = data->event_set[i];
		if ((sock_fd = pollfd.fd) < 0) {
			continue;
		}
		if (pollfd.revents <= 0) {
			continue;
		}
		INFO_LOG("get message channel i = %d, fd = %d, %s", i, sock_fd, loop->thread_name);
		if (pollfd.revents & POLLRDNORM) {
			channel_event_activate(loop, sock_fd, EVENT_READ);
		}
		if (pollfd.revents & POLLWRNORM) {
			channel_event_activate(loop, sock_fd, EVENT_WRITE);
		}
		if (--ready_number <= 0) {
			break;
		}
	}
	return 0;
}
static void poll_clear(struct event_loop* loop) {
	struct poll_dspt_data* data = (struct poll_dspt_data*)loop->dspt_data;
	free(data->event_set);
	data->event_set = NULL;
	free(data);
	loop->dspt_data = NULL;
}
