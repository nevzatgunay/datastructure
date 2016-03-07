/*	Nevzat GÜNAY
	200201062
*/

#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#define MAX_ELEMENTS 20

struct Table {
	int capacity;
	struct Table *next;
	struct Table *prev;
};

void add_random(struct Table *head);
void print_list(struct Table *head);
void insertion_sort(struct Table **q);

int main(){
	srand(time(0));	
	int i;
	struct Table *table = (struct Table *)malloc(sizeof(struct Table));

        for (i = 0; i < MAX_ELEMENTS; ++i)
                add_random(table);
	
	printf("Unsorted List:\n");
	print_list(table->next);
	printf("\n");
	struct Table **temp=&table;
	insertion_sort(temp);
	printf("Sorted List:\n");
	print_list(table->next);
	return 0;
}

void add_random(struct Table *head)
{

        while(head->next!=NULL)
        {
                head = head->next;
        }
        head->next = (struct Table *)malloc(sizeof(struct Table));
        (head->next)->prev = head;
        head = head->next;
       	head->capacity = 2+rand()%8;
        head->next = NULL;
}

void print_list(struct Table *head)
{
        if(head==NULL)
        {
                return;
        }
        printf("[%d] ",head->capacity);
        print_list(head->next);
}

void insertion_sort(struct Table **q)
{
	int n;
	struct Table *cur;
	cur=*q;
	if (cur->next==NULL)
		return;
	
	struct Table *ptr,*tmp;
	cur=cur->next;
	while(cur!=NULL)
	{
		n=0;
		ptr=cur;
		tmp=cur->prev;
		cur=cur->next;
		while (tmp!=NULL && tmp->capacity>ptr->capacity)
		{
			n++;
			tmp=tmp->prev;
		}
		if (n)
		{
			
			ptr->prev->next=ptr->next;
			if (ptr->next!=NULL)
			ptr->next->prev=ptr->prev;
	
			if (tmp==NULL)
			{
				tmp=*q;
				ptr->prev=NULL;
				ptr->next=tmp;
				ptr->next->prev=ptr;
				*q=ptr;
			}
			else
			{
				tmp=tmp->next;
				tmp->prev->next=ptr;
				ptr->prev=tmp->prev;
				tmp->prev=ptr;
				ptr->next=tmp;
			}
		}
	}
}

