/*	200201062 - Nevzat GÜNAY
	Homework 2/2
	Updated Date:Tuesday 24 March 2015
*/
#include <stdlib.h>
#include <stdio.h>
#include "grade_util.h"
struct grades{//this is our struct that it holds three variable.The float pointer grades is to link other new struct respectively.
	float *grades;//The float pointer grades is to link other new struct respectively.
	int size;//it holds size of grades that we do not care changing it
	int capacity;//this is capacity of grades that we do not care changing it.
};
int main(void)
{
     	struct grades* temp;//temp is a copy of grades struct that will change continuously and will hold grades of students.
        temp = load_grades();//we call load_grades.
        printf("Number of students is %d\n", temp->size);//temp->size gives us the number of students.
        float min = minimum_of(temp);//The other rows look like the original code.
        printf("Minimum is %.2f\n", min);
        float max = maximum_of(temp);
        printf("Maximum is %.2f\n", max);
        float average = average_of(temp);
        printf("Average is %.2f\n", average);
        printf("Letter grades:\n");
        for(int i=0; i< temp->size; i++) 
	{
                char *letter_grade = letter_grade_for(temp->grades[i], average);
                printf("%6.2f -> %s\n", temp->grades[i], letter_grade);//temp->grades[i] gives us respectively the grade of i's student.
        }
        return EXIT_SUCCESS;
}
