/*	Nevzat GÜNAY
	200201062
*/

#include "deque.h"

#include <stdlib.h>
#include <string.h>

#define MAX 100

struct Deque
{
        int front;
	int rear;
        int data[MAX];
	int count;
};

struct Deque *deque_new()
{
        struct Deque *q = malloc(sizeof(struct Deque));
        q->rear=-1;
	q->front=-1;
	q->data[0]=0;
	q->count=0;
        return q;
}

void deque_free(struct Deque *q)
{
        if (q != NULL)
		free(q);
}

void put_front(struct Deque *deq, void *elem){
	if(deque_is_empty(deq)){
        	deq->rear=0;
        	deq->front=0;
        	deq->data[0]=elem;
    	}
    	else{
        	deq->front=(deq->front-1+MAX)%MAX;
        	deq->data[deq->front]=elem;
    	}
	deq->count++;
}

void get_front(struct Deque *deq, void *elem){
    	elem = deq->data[deq->front];
    	if(deq->rear==deq->front){   
        	deq->rear=-1;
		deq->front=-1;
	}
    	else
        	deq->front=(deq->front+1)%MAX;
	deq->count--;
}

void put_back(struct Deque *deq, void *elem){
	if(deque_is_empty(deq)){
        	deq->rear=0;
        	deq->front=0;
        	deq->data[0]=elem;
    	}
    	else{
            	deq->rear=(deq->rear+1)%MAX;
            	deq->data[deq->rear]=elem;
	}
	deq->count++;
}

void get_back(struct Deque *deq, void *elem){
	elem = deq->data[deq->rear];
        if(deq->rear==deq->front){
        	deq->rear=-1;
		deq->front=-1;
	}
    	else
        	deq->rear=(deq->rear-1+MAX)%MAX;
	deq->count--;
}

int deque_size(struct Deque *q)
{
        return q->count;
}

int deque_is_empty(const struct Deque *q)
{
        if(q->rear==-1)
		return 1;
	else
		return 0;
}
