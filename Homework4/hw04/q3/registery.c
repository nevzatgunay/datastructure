/*	Nevzat GÜNAY
	200201062

Note:Please,when you compile the program,you write like this './registery < students.txt'
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_ENTRIES 10

struct Student{
	char *name;
	int id;
};

int compare_id(struct Student *elem1, struct Student *elem2);
int compare_name(const void * a, const void * b );
typedef int (*compfn)(const void*, const void*);

int main(int argc, char **argv){
	
        struct Student std[10];

	int i;
	for(i=0;i<MAX_ENTRIES;++i)
		std[i].name=malloc(sizeof(char)*10);

	i=0;
	while (i < MAX_ENTRIES){
		scanf("%s %d\n", std[i].name,&std[i].id);                
		i++;
	}

	printf("Sorted List by id:\n");
	qsort((void *)&std, 10, sizeof(struct Student), (compfn)compare_id);
	for(i=0;i<MAX_ENTRIES;++i)
		printf("[%d]%s %d\n",i+1,std[i].name,std[i].id);

	printf("Sorted List by name:\n");
	qsort((void *)&std, 10, sizeof(struct Student), (compfn)compare_name);
	for(i=0;i<MAX_ENTRIES;++i)
		printf("[%d]%s %d\n",i+1,std[i].name,std[i].id);

        return EXIT_SUCCESS;
}

int compare_id(struct Student *elem1, struct Student *elem2)
{
	if(elem1->id < elem2->id)
		return -1;
	else if(elem1->id > elem2->id)
		return 1;
	else
		return 0;
}

int compare_name(const void * a, const void * b ) {
  	return strcmp(*(char **)a, *(char **)b);
}


