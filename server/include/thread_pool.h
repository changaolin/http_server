#ifndef THREAD_POOL_H
#define THREAD_POOL_H
#include "event_loop.h"
#include "event_loop_thread.h"

struct thread_pool {
	struct event_loop* main_loop;
	int started;
	int thread_number;
	struct event_loop_thread* loop_threads;
	int position;
};

struct thread_pool* thread_pool_new(struct event_loop* loop, int thread_number);
void thread_pool_start(struct thread_pool*);
struct event_loop* thread_pool_get_loop(struct thread_pool*);
#endif // THREAD_POOL_H
