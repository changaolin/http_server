#include <sys/socket.h>
#include <assert.h>
#include <unistd.h>
#include "log.h"
#include "channel_map.h"
#include "event_loop.h"

void assert_in_same_thread(struct event_loop* loop) {
	if (loop->owner_thread_id != pthread_self()) {
		ERROR_LOG("not in the same thread");
		exit(-1);
	}
}
int is_in_same_thread(struct event_loop* loop) {
	return loop->owner_thread_id == pthread_self();
}
int event_loop_handle_pending_channel(struct event_loop* loop) {
	pthread_mutex_lock(&loop->mutex);
	loop->is_handle_pending = 1;
	struct channel_element* element = loop->pending_head;
	while (element != NULL) {
		struct channel* chan = element->channel;
		int fd = chan->fd;
		switch (element->type) {
			case 1:
				event_loop_handle_pending_add(loop, fd, chan);
				break;
			case 2:
				event_loop_handle_pending_remove(loop, fd, chan);
				break;
			case 3:
				event_loop_handle_pending_update(loop, fd, chan);
				break;
			default:
				WARNING_LOG("event_loop_handle_pending_channel error, type is [%d]", element->type);
		}
		element = element->next;
	}
	loop->pending_head = loop->pending_tail = NULL;
	loop->is_handle_pending = 0;
	pthread_mutex_unlock(&loop->mutex);
	return 0;
}
void event_loop_channel_buffer_nolock(struct event_loop* loop, int fd, struct channel* chan, int type) {
	struct channel_element* element = malloc(sizeof(struct channel_element));
	element->channel = chan;
	element->type = type;
	element->next = NULL;
	if (loop->pending_head == NULL) {
		loop->pending_head = loop->pending_tail = element;
	} else {
		loop->pending_tail->next = element;
		loop->pending_tail = element;
	}
}
int event_loop_do_channel_event(struct event_loop* loop, int fd, struct channel* chan, int type) {
	pthread_mutex_lock(&loop->mutex);
	assert(loop->is_handle_pending == 0);
	event_loop_channel_buffer_nolock(loop, fd, chan, type);
	pthread_mutex_unlock(&loop->mutex);
	if (!is_in_same_thread(loop)) {
		event_loop_wakeup(loop);
	} else {
		event_loop_handle_pending_channel(loop);
	}
	return 0;
}

int event_loop_add_channel_event(struct event_loop* loop, int fd, struct channel* chan) {
	return event_loop_do_channel_event(loop, fd, chan, 1);
}
int event_loop_remove_channel_event(struct event_loop* loop, int fd, struct channel* chan) {
	return event_loop_do_channel_event(loop, fd, chan, 2);
}
int event_loop_update_channel_event(struct event_loop* loop, int fd, struct channel* chan) {
	return event_loop_do_channel_event(loop, fd, chan, 3);
}

int event_loop_handle_pending_add(struct event_loop* loop, int fd, struct channel* chan) {
	INFO_LOG("add channel fd = '%d, %s'", fd, loop->thread_name);
	struct channel_map* map = loop->channel_map;
	if (fd < 0) {
		return 0;
	}
	if (fd >= map->nentries) {
		if (map_make_space(map, fd, sizeof(struct channel*)) == -1) {
			return -1;
		}
	}
	if (map->entries[fd] == NULL) {
		map->entries[fd] = chan;
		loop->dspt->add(loop, chan);
		return 1;
	}
	return 0;
}

int event_loop_handle_pending_remove(struct event_loop* loop, int fd, struct channel* chan) {
	struct channel_map* map = loop->channel_map;
	assert(fd == chan->fd);
	if (fd < 0) {
		return 0;
	}
	if (fd >= map->nentries) {
		return -1;
	}
	chan = map->entries[fd];
	int retval = 1;
	if (loop->dspt->del(loop, chan) == -1) {
		retval = -1;
	}
	map->entries[fd] = NULL;
	return retval;
}

int event_loop_handle_pending_update(struct event_loop* loop, int fd, struct channel* chan) {
	INFO_LOG("update channel fd = '%d, %s'", fd, loop->thread_name);
	struct channel_map* map = loop->channel_map;
	if (fd < 0) {
		return 0;
	}
	if (map->entries[fd] == NULL) {
		return -1;
	}

	loop->dspt->update(loop, chan);
}

int channel_event_activate(struct event_loop* loop, int fd, int revents) {
	struct channel_map* map = loop->channel_map;
	INFO_LOG("activate channel fd = '%d', revents = '%d, %s'", fd, revents, loop->thread_name);
	if (fd < 0) {
		return 0;
	}
	if (fd >= map->nentries) {
		return -1;
	}

	struct channel* chan = map->entries[fd];
	assert(fd == chan->fd);

	if (revents & EVENT_READ) {
		if (chan->read_cb) {
			chan->read_cb(chan->data);
		}
	}
	if (revents & EVENT_WRITE) {
		if (chan->write_cb) {
			chan->write_cb(chan->data);
		}
	}
	return 0;
}

void event_loop_wakeup(struct event_loop* loop) {
	char one = 'a';
	ssize_t n = write(loop->sockt_pair[0], &one, sizeof(one));
	if (n != sizeof(one)) {
		ERROR_LOG("wakeup event loop thread failed");
	}
}


int handle_wakeup(void* data) {
	struct event_loop* loop = (struct event_loop*) data;
	char one;
	ssize_t n = read(loop->sockt_pair[1], &one, sizeof(one));
	if (n != sizeof(one)) {
		ERROR_LOG("handle wakeuo failed!");
	}
	INFO_LOG("wakeup %s", loop->thread_name);
}

struct event_loop* event_loop_init() {
	return event_loop_init_with_name(NULL);
}
struct event_loop* event_loop_init_with_name(char* thread_name) {
	struct event_loop* loop = malloc(sizeof(struct event_loop));
	pthread_mutex_init(&loop->mutex, NULL);
	pthread_cond_init(&loop->cond, NULL);

	if (thread_name == NULL) {
		loop->thread_name = "main_thread";
	} else {
		loop->thread_name = thread_name;
	}

	loop->quit = 0;
	loop->channel_map = malloc(sizeof(struct channel_map));
	map_init(loop->channel_map);
	loop->dspt = get_dispatcher();
	loop->dspt_data = loop->dspt->init(loop);

	loop->owner_thread_id = pthread_self();
	if (socketpair(AF_UNIX, SOCK_STREAM, 0, loop->sockt_pair) < 0) { // #include <sys/socket.h>
		ERROR_LOG("socketpair set failed");
	}
	loop->is_handle_pending = 0;
	loop->pending_head = loop->pending_tail = NULL;
	struct channel* chan = channel_new(loop->sockt_pair[1], EVENT_READ, handle_wakeup, NULL, loop);
	event_loop_add_channel_event(loop, loop->sockt_pair[1], chan);
	return loop;
}

int event_loop_run(struct event_loop* loop) {
	assert(loop != NULL);
	if (loop->owner_thread_id != pthread_self()) {
		exit(1);
	}
	INFO_LOG("event loop run, %s", loop->thread_name);
	struct timeval tmval;
	tmval.tv_sec = 1;
	while (!loop->quit) {
		loop->dspt->dispatch(loop, &tmval);
		event_loop_handle_pending_channel(loop);
	}
	INFO_LOG("event loop end, %s", loop->thread_name);
	return 0;
}
