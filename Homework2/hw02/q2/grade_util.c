/*	200201062 - Nevzat GÜNAY
	Homework 2/2
	Updated Date:Tuesday 24 March 2015
*/
#include <stdio.h>
#include <math.h>
#include <float.h>
#include <stdlib.h>
#include "grade_util.h"
struct grades{//this is our struct that it holds three variable.
	float *grades;//The float pointer grades is to link other new struct respectively.
	int size;//it holds size of grades that if it is equal to capacity,we will increase the capacity.
	int capacity;//this is capacity of grades that it will change with respect to size.
};
struct grades *load_grades(void){//load_grades will return struct type.
	struct grades *temp;//temp is copy of struct grades.
	temp = malloc(3*sizeof(int));//we allocate temp.
	temp->size = 0;//firstly,size is zero,it will change.
	temp->capacity = 2;//capacity is two now,it will change.	
	temp->grades = malloc(temp->capacity);//this is for float pointer grades,because it is to show the other grade continuously.
	int i = 0;//this is a counter.
        while(temp->grades+i != EOF && scanf("%f", temp->grades+i) == 1)//we reads data from the file.
	{
        	i++;//counter increase to 1.
        	temp->size+=1;//of course,size is too.
        	if(temp->size>temp->capacity)//if size is equal to capacity,we should enlarge the capacity that it holds more data.
		{
        		temp->capacity*=2;
        	}
        }
        return temp;//temp returns that load_grades should return a struct.
}

float minimum_of(struct grades *temp)//it was modified with respect to struct pointer temp.
{
        float min = FLT_MAX;
        for (int i = 0; i < (temp->size); ++i)//it will go to temp->size
                if (temp->grades[i] < min)//it reads grades and finds the minimum of grades.
                        min = temp->grades[i];
        return min;
}

float maximum_of(struct grades *temp)//it was modified with respect to struct pointer temp.
{
        float max = -FLT_MAX;
        for (int i = 0; i < temp->size ; ++i)//it will go to temp->size
                if (temp->grades[i] > max)//it reads grades and finds the maximum of grades.
                        max = temp->grades[i];
        return max;
}

float average_of(struct grades *temp)//it was modified with respect to struct pointer temp.
{
        float average = 0.0f;
        for (int i = 0; i < temp->size; ++i)//it will go to temp->size
                average += temp->grades[i];//it reads grades and finds the average of grades.
        average /= temp->size;

        return average;
}

float normalize(float grade, float average)
{
        float normalized = grade;
        if (average < 70.0f)
                normalized += 70.0f - average;
        if (normalized > 100.0f)
                normalized = 100.0f;
        return normalized;
}

char *letter_grade_for(float grade, float average)
{
        float normalized = normalize(grade, average);
        int letter_bin = round(normalized) / 5;
        char *letter_grade;
        switch (letter_bin) {
        case 20:
        case 19:
        case 18: letter_grade = "AA"; break;
        case 17: letter_grade = "BA"; break;
        case 16: letter_grade = "BB"; break;
        case 15: letter_grade = "CB"; break;
        case 14: letter_grade = "CC"; break;
        case 13: letter_grade = "DC"; break;
        case 12: letter_grade = "DD"; break;
        case 11: letter_grade = "FD"; break;
        default: letter_grade = "FF"; break;
        }
        return letter_grade;
}
