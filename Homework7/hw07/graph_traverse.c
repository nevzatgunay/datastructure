/*	Nevzat GÜNAY
	200201062
	
Note:It was included five new function and one 2-dimensional array.
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <time.h>

#include "queue.h"

#define NV 8

struct NeighborInfo {
        int id;
        struct NeighborInfo *next;
};

struct Vertex {
        char name;
        struct NeighborInfo *neighbors;
};

void add_edge(struct Vertex *g, int v0, int v1);
void make_neighbors(struct Vertex *g, int v0, int v1);
void free_graph_list(struct Vertex *g, int nv);

void print_adjaceny_lists(struct Vertex *g, int nv);
void print_depth_first(struct Vertex *g, int id, int *marks);
void print_breadth_first(struct Vertex *g, int id, int *marks);

/*<--new functions and array declaration start-->*/
void init_adjacency();
void make_adjacency(int v0,int v1);
void print_adjacency_matrix();
void print_depth_first_adjacency(int adj[8][8], int id, int *marks);
void print_breadth_first_adjacency(int adj[8][8], int id, int *marks);

int adj[8][8];
/*<--new functions and array declaration finish-->*/

int main(int argc, char **argv)
{
	init_adjacency();//initialize the adjacency matrix

        struct Vertex g_list[NV];
        for (int i = 0; i < NV; ++i) {
                g_list[i].name = 'A' + i;
                g_list[i].neighbors = NULL;
        }

        make_neighbors(g_list, 0, 1);
        make_neighbors(g_list, 0, 2);
        make_neighbors(g_list, 0, 5);
        make_neighbors(g_list, 0, 6);
        make_neighbors(g_list, 0, 7);
        make_neighbors(g_list, 1, 7);
        make_neighbors(g_list, 2, 7);
        make_neighbors(g_list, 3, 4);
        make_neighbors(g_list, 3, 5);
        make_neighbors(g_list, 4, 5);
        make_neighbors(g_list, 4, 6);
        make_neighbors(g_list, 4, 7);

        print_adjaceny_lists(g_list, NV);
	
	print_adjacency_matrix();//printing adjacency matrix

        // marks for already visited nodes
        int marks[NV];

        // print starting from 0
        printf("Depth First from 0: ");
        memset(marks, 0, NV*sizeof(marks[0]));
        print_depth_first_adjacency(adj,0,marks);//calling function
        printf("\n");

        // print starting from 4
        printf("Depth First from 4: ");
        memset(marks, 0, NV*sizeof(marks[0]));
        print_depth_first_adjacency(adj,4,marks);//calling function
        printf("\n");

        // print starting from 0
        printf("Breadth First from 0: ");
        memset(marks, 0, NV*sizeof(marks[0]));
	print_breadth_first_adjacency(adj,0,marks);//calling function
        printf("\n");

        // print starting from 4
        printf("Breadth First from 4: ");
        memset(marks, 0, NV*sizeof(marks[0]));
        print_breadth_first_adjacency(adj,4,marks);//calling function
        printf("\n");

        free_graph_list(g_list, NV);

        return EXIT_SUCCESS;
}

void add_edge(struct Vertex *g, int v0, int v1)
{
        struct NeighborInfo *ninfo = malloc(sizeof(*ninfo));
        ninfo->id = v1;
        ninfo->next = g[v0].neighbors;
        g[v0].neighbors = ninfo;
	make_adjacency(v0,v1);//calling function
	make_adjacency(v1,v0);//calling function
}

void make_neighbors(struct Vertex *g, int v0, int v1)
{
        add_edge(g, v0, v1);
        add_edge(g, v1, v0);
}

void free_graph_list(struct Vertex *g, int nv)
{
        for (int i = 0; i < nv; ++i) {
                while (g[i].neighbors != NULL) {
                        struct NeighborInfo *to_del = g[i].neighbors;
                        g[i].neighbors = g[i].neighbors->next;
                        free(to_del);
                }
        }
}

/*<-- new functions start-->*/
void init_adjacency()
{
	for(int i=0;i<8;i++)
		for(int j=0;j<8;j++)
			adj[i][j]=0;
}

void make_adjacency(int v0,int v1)
{
	adj[v0][v1]=1;
}

void print_adjacency_matrix()
{	
	printf("\n----Adjacency Matrix----\n");
	printf("\n    A B C D E F G H \n");
	for(int i=0;i<8;i++){
		printf("%c [ ",'A'+i);
		for(int j=0;j<8;j++)
			printf("%d ",adj[i][j]);
		printf("]\n");
	}
	printf("\n");
}

void print_adjaceny_lists(struct Vertex *g, int nv)
{
        printf("Adjacency List:\n");
        for (int i = 0; i < nv; ++i) {
                printf("%c: ", g[i].name);
                struct NeighborInfo *n = g[i].neighbors;
                while (n != NULL) {
                        printf("%c ", g[n->id].name);
                        n = n->next;
                }
                printf("\n");
        }
}

void print_depth_first_adjacency(int adj[8][8], int id, int *marks)
{
        printf("%c ", 'A'+id);
        marks[id] = 1;
	int i;
	for(i=7;i>=0;i--)
		if(!marks[i] && adj[id][i])
			print_depth_first_adjacency(adj,i,marks);
}

void print_breadth_first_adjacency(int adj[8][8], int id, int *marks)
{
	struct Queue *q=queue_new(sizeof(int));
	marks[id]=1;
	queue_put(q,&id);
	while(!queue_is_empty(q)){
		int w;
		queue_get(q,&w);
		printf("%c ",'A'+w);
		
		for(int u=7;u>=0;u--){
			if(adj[w][u] && marks[u]==0){
				queue_put(q,&u);
				marks[u]=1;
			}
			
		}
		
	}
	
	queue_free(q);
}

/*<-- new functions finish-->*/

/* Local Variables: */
/* mode: c          */
/* compile-command: "make graph-traverse" */
/* End:             */
