/*	Nevzat GÜNAY
	200201062
*/

#ifndef DEQUE_H
#define DEQUE_H

struct Deque;

struct Deque *deque_new();

void deque_free(struct Deque *q);

void put_front(struct Deque *deq, void *elem);
void get_front(struct Deque *deq, void *elem);

void put_back(struct Deque *deq, void *elem);
void get_back(struct Deque *deq, void *elem);

int deque_size(struct Deque *q);
int deque_is_empty(const struct Deque *q);

#endif
