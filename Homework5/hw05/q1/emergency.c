/*	Nevzat GÜNAY
	200201062
	
	Note:Please,while you run the program,you write this "./emergency < patients.txt".
*/

#include<stdio.h>
#include<stdlib.h>

#define MAX 7

struct Patient {
	int national_id;
	int condition;
};

struct Patient pt[MAX];
int front=-1, rear=-1;

void pqueue_insert(int national_id,int condition);
void control(int national_id,int condition);
void pqueue_delete(int condition);
void pqueue_print();

int main(void){
	
	int national_id,condition;
	int i=0,j=0;
        while(i<MAX){
		scanf("%d %d\n", &national_id, &condition);
               	pqueue_insert(national_id,condition);
		pqueue_print();
		i++;
		if(i%3==0){
			printf("Popped Out the Lowest Condition's Id-->[%d]\n",pt[front].condition);
        		pqueue_delete(pt[0].condition);
			
			pqueue_print();
		}
		
	}
	if(i==MAX){
			while(i>j && front>-1){
				printf("Popped Out the Lowest Condition's Id-->[%d]\n",pt[front].national_id);
        			pqueue_delete(pt[0].condition);
				j++;
			}
	}
	return 0;
}

void pqueue_insert(int national_id,int condition)
{
	if (rear >= MAX - 1){
        	printf("PQueue Overflow\n");
        	return;
    	}
    	if((front == -1) && (rear == -1)){
        	front++;
        	rear++;
        	pt[rear].national_id = national_id;
		pt[rear].condition = condition;
        	return;
    	}    
    	else
        	control(national_id,condition);
    	rear++;
}

void control(int national_id,int condition)
{
    	int i,j;
 
    	for(i = 0; i <= rear; i++){
        	if (condition>= pt[i].condition){
            		for (j = rear + 1; j > i; j--){
                		pt[j].national_id = pt[j - 1].national_id;
                		pt[j].condition = pt[j - 1].condition;
            		}
            	pt[i].condition = condition;
	    	pt[i].national_id = national_id;
            	return;
        	}
    	}
    	pt[i].condition = condition;
    	pt[i].national_id = national_id;
}

void pqueue_delete(int condition)
{
    	if((front==-1) && (rear==-1)){
        	printf("PQueue Is Empty\n");
   	}
 
    	for(int i = 0; i <= rear; i++){
        	if(condition == pt[i].condition){
            		for(; i < rear; i++){
                		pt[i].condition = pt[i + 1].condition;
				pt[i].national_id = pt[i+1].national_id;
            	}
 
        	pt[i].condition = -99;
        	pt[i].national_id = -99;
        	rear--;
 
        	if (rear == -1) 
            		front = -1;
        	return;
        }
}
    	printf("%d Not Found in PQueue\n", condition);
}

void pqueue_print()
{
	printf("\nNational Id and Condition List\n");
	printf("------------------------------\n");
	
    	if ((front == -1) && (rear == -1)){
        	printf("PQueue Is Empty\n");
    	}
 
    	for(; front <= rear; front++){
        	printf("National Id-->[%d] and Condition-->[%d]\n", pt[front].national_id,pt[front].condition);
    	}
 
    	front = 0;
}

