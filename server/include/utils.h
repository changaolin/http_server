#ifndef UTILS_H
#define UTILS_H
#include "event_loop.h"
void assert_in_same_thread(struct event_loop* loop);
int is_in_same_thread(struct event_loop* loop);
#endif // UTILS_H
