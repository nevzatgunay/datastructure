#ifndef GRADE_UTIL_H
#define GRADE_UTIL_H

struct grades *load_grades();
float minimum_of(struct grades *notes);
float maximum_of(struct grades *notes);
float average_of(struct grades *notes);
float normalize(float grade, float average);
char *letter_grade_for(float grade, float average);

#endif
