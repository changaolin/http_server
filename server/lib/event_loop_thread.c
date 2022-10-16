#include <assert.h>
#include <strings.h>
#include "event_loop_thread.h"
#include "event_loop.h"
void* event_loop_thread_run(void* arg) {
	struct event_loop_thread* loop_thread = (struct event_loop_thread*) arg;
	pthread_mutex_lock(&loop_thread->mutex);

	loop_thread->loop = event_loop_init_with_name(loop_thread->thread_name);
	INFO_LOG("event loop thread init and signall, %s", loop_thread->thread_name);
	pthread_cond_signal(&loop_thread->cond);
	pthread_mutex_unlock(&loop_thread->mutex);
	event_loop_run(loop_thread->loop);
	return NULL;
}

int event_loop_thread_init(struct event_loop_thread* loop_thread, int index) {
	pthread_mutex_init(&loop_thread->mutex, NULL);
	pthread_cond_init(&loop_thread->cond, NULL);
	loop_thread->loop = NULL;
	loop_thread->thread_count = 0;
	loop_thread->tid = 0;
	loop_thread->thread_name = malloc(20);
	bzero(loop_thread->thread_name, 20);
	sprintf(loop_thread->thread_name, "Thread-%d", index + 1);
	return 0;
}
struct event_loop* event_loop_thread_start(struct event_loop_thread* loop_thread) {
	pthread_create(&loop_thread->tid, NULL, &event_loop_thread_run, loop_thread);
	assert(pthread_mutex_lock(&loop_thread->mutex) == 0);
	while (loop_thread->loop == NULL) {
		assert(pthread_cond_wait(&loop_thread->cond, &loop_thread->mutex) == 0);
	}

	assert(pthread_mutex_unlock(&loop_thread->mutex) == 0);
	INFO_LOG("event loop thread started, %s", loop_thread->thread_name);
	return loop_thread->loop;
}

