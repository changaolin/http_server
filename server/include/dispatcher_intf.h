#ifndef DISPATCHER_H
#define DISPATCHER_H
#include <sys/time.h>
struct event_loop;
struct channel;
struct dispatcher {
	const char* name;
	void* (*init)(struct event_loop*);
	int (*add)(struct event_loop*, struct channel* channel);
	int (*del)(struct event_loop*, struct channel* channel);
	int (*update)(struct event_loop*, struct channel* channel);
	int (*dispatch)(struct event_loop*, struct timeval*);
	void (*clear)(struct event_loop*);
};
const struct dispatcher* get_dispatcher(void);
#endif // DISPATCHER_H
