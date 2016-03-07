/*	Nevzat GÜNAY
	200201062
*/

#include "stack.h"

#include <stdlib.h>

#include "array.h"

struct Node {
        int *elem;
	struct Node *next;
};

struct Stack{
        struct Node *head;
        struct Node *tail;
	int n_elems;
	int elem_size;
};

static struct Node *new_node(void *elem, int elem_size)
{
        struct Node *n = malloc(sizeof(struct Node));
        n->elem = malloc(elem_size);
        memcpy(n->elem, elem, elem_size);
        n->next = NULL;
        return n;
	
}

struct Stack *stack_new(int elem_size)
{
        struct Stack *s = malloc(sizeof(struct Stack));
	s->elem_size=elem_size;
	s->n_elems=0;
	s->head = NULL;
        s->tail = NULL;       
	return s;

}

static void free_node(struct Node *n)
{
        if (n != NULL) {
                free(n->elem);
                free(n);
        }
}

void stack_free(struct Stack *s)
{
        while (s != NULL) {
		struct Node *temp = s;
		temp=temp->next;
		free_node(temp);
        }
}

void stack_push(struct Stack *s, void *elem)
{
	struct Node *n = new_node(elem, s->elem_size);

        if (s->head == NULL) {
                s->head = n;
                s->tail = n;
        } else {
                s->head->next = n;
                s->head = n;
        }
        s->n_elems++;

}

void stack_pop(struct Stack *s)
{
	memcpy(s->head->elem, s->tail->elem, s->elem_size);
        struct Node *to_del = s->tail;
        s->tail = s->tail->next;
        free_node(to_del);		
        s->n_elems--;
}

void *stack_peek(struct Stack *s)
{
        return s->head->elem;
}

int stack_size(const struct Stack *s)
{
        return s->n_elems;
}

int stack_is_empty(const struct Stack *s)
{
        return s->n_elems == 0;
}

