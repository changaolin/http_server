#ifndef EVENT_LOOP_H
#define EVENT_LOOP_H
#include <pthread.h>
#include "common.h"
#include "channel.h"
#include "dispatcher_intf.h"

struct channel_element {
	int type; // 1 add. 2 del
	struct channel* channel;
	struct channel_element* next;
};

struct event_loop {
	int quit;
	const struct dispatcher* dspt;
	void* dspt_data;
	struct channel_map* channel_map;
	int is_handle_pending;
	struct channel_element* pending_head;
	struct channel_element* pending_tail;
	pthread_t owner_thread_id;
	pthread_mutex_t mutex;
	pthread_cond_t cond;
	int sockt_pair[2];
	char* thread_name;
};

int event_loop_handle_pending_channel(struct event_loop* loop);
void event_loop_channel_buffer_nolock(struct event_loop* loop, int fd, struct channel* chan, int type); 

struct event_loop* event_loop_init();
struct event_loop* event_loop_init_with_name(char* thread_name);
void event_loop_wakeup(struct event_loop* loop);
int event_loop_run(struct event_loop* loop);
int event_loop_add_channel_event(struct event_loop* loop, int fd, struct channel* chan);
int event_loop_remove_channel_event(struct event_loop* loop, int fd, struct channel* chan);
int event_loop_update_channel_event(struct event_loop* loop, int fd, struct channel* chan);
int event_loop_handle_pending_add(struct event_loop* loop, int fd, struct channel* chan);
int event_loop_handle_pending_remove(struct event_loop* loop, int fd, struct channel* chan);
int event_loop_handle_pending_update(struct event_loop* loop, int fd, struct channel* chan);
int channel_event_activate(struct event_loop* loop, int fd, int revents);

void assert_in_same_thread(struct event_loop* loop);
int is_in_same_thread(struct event_loop* loop);
#endif // EVENT_LOOP_H
