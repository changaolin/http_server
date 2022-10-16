#include <assert.h>
#include "event_loop.h"
#include "thread_pool.h"
struct thread_pool* thread_pool_new(struct event_loop* loop, int thread_number) {
	struct thread_pool* pool = malloc(sizeof(struct thread_pool));
	pool->main_loop = loop;
	pool->position = 0;
	pool->thread_number = thread_number;
	pool->started = 0;
	pool->loop_threads = NULL;
	return pool;
}
void thread_pool_start(struct thread_pool* pool) {
	assert(!pool->started);
	assert_in_same_thread(pool->main_loop);
	pool->started = 1;
	pool->loop_threads = malloc(pool->thread_number * sizeof(struct event_loop_thread));
	for (int i = 0; i < pool->thread_number; i++) {
		event_loop_thread_init(&pool->loop_threads[i], i);
		event_loop_thread_start(&pool->loop_threads[i]);
	}
}

struct event_loop* thread_pool_get_loop(struct thread_pool* pool) {
	assert(pool->started);
	assert_in_same_thread(pool->main_loop);

	struct event_loop* selected = pool->main_loop;

	if (pool->thread_number > 0) {
		selected = pool->loop_threads[pool->position].loop;
		if (++pool->position >= pool->thread_number) {
			pool->position = 0;
		}
	}
	return selected;
}
