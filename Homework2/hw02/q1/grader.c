/*	200201062 - Nevzat GÜNAY
	Homework 2/1
	Updated Date:Tuesday 24 March 2015
*/
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "grade_util.h"
int main(void)
{		
	float *grades;//grades is a float pointer that holds grades of students.
        int *n;
	*n=0;//it is a copy of number of students.Also,when I write int *n=0,I have segmentation fault.Therefore,I did this one.
        grades = load_grades(n);//we call the function load_grades and it reads from the file(ceng211_midterm.txt)
        printf("Number of students is %d\n", *n);//we write the number of students.
        float min = minimum_of(n, grades);//the other rows have a few changes.
        printf("Minimum is %.2f\n", min);
        float max = maximum_of(n, grades);
        printf("Maximum is %.2f\n", max);
        float average = average_of(n, grades);
        printf("Average is %.2f\n", average);

        printf("Letter grades:\n");
        for (int i = 0; i < (*n); ++i) {
                printf("%6.2f -> %s\n", grades[i], letter_grade_for((grades+i), average));
        }  
		
        return EXIT_SUCCESS;
}
