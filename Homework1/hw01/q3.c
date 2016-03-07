/*	Nevzat Günay
	200201062
*/

//	This program only runs with grade_util.c and grade_util.h files,so please be careful!.In addition,before you compile the program,you can write "gcc -Wall -g -std=c99 q3.c grade_util.c -o q3 -lm" and "./q3 < ceng211_midterm.txt"

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <float.h>
#include "grade_util.h"

#define MAX_N_STUDENTS 500
#define N_BINS 20
#define N_COLUMNS 80

void compute_histogram(int bins[], int n_students, float grades[]);
void draw_histogram(int bins[], int n_columns);

int main(void)
{
        float grades[MAX_N_STUDENTS];
        int n = load_grades(grades, MAX_N_STUDENTS);
	

        int bins[N_BINS];
        compute_histogram(bins, n, grades);

        draw_histogram(bins, N_COLUMNS);

        return EXIT_SUCCESS;
}

void compute_histogram(int bins[], int n_students, float grades[])
{
        float min = minimum_of(n_students, grades);
        float max = maximum_of(n_students, grades);
        float range = max - min;
        float bin_size = range / N_BINS;

        for (int i = 0; i < N_BINS; ++i)
                bins[i] = 0;

        for (int i = 0; i < n_students; ++i) {
                int bin_id = (grades[i] - min) / bin_size;
                if (bin_id == N_BINS)
                        bin_id = N_BINS-1;
                bins[bin_id]++;
        }
}

//Just this block was modified by me.

void draw_histogram(int bins[], int n_columns)
{
	int bar_length[20],max=0,j;//bar_length holds size of a bar,j holds indexes of the columns.
        for (int i = 0; i < N_BINS; ++i)
                if (bins[i] > max)
                        max = bins[i];
		
        float col_size = max / (float)n_columns;
        for (int i = 0; i < N_BINS; ++i) {
                int nc = ceilf(bins[i] / col_size);
                bar_length[j] = ceilf(nc);
                j++;
        }
        max = ceilf(max / col_size);
        for(int j = 0; j < max;--max){ //actually,we manipulated the original code and then,we rotated it that it is vertical.
        	for(int i = N_BINS-1; i > -1; --i){
        		if(bar_length[i] >= max){
        			printf("||");//it is just to put a character '|'
        		}
        		else{
        			printf("  ");//space character is for columns.
        		}
  			}
  			printf("\n");
  		}
}

