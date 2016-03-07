#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <time.h>

#include "set_of_ints.h"

int main(int argc, char **argv)
{
  int n = 10;
  if (argc > 1)
    n = atoi(argv[1]);

  int max_value = 1000;
  if (argc > 2)
    max_value = atoi(argv[2]);

  if (max_value < n) {
    fprintf(stderr, "Maximum value can not be smaller than the number of random numbers!");
    return EXIT_FAILURE;
  }

  struct SetOfInts *si = new_set_of_ints(n);

  srand(time(0));
  while (size_of_set_of_ints(si) < n) {
    int new_int = (rand() % max_value) + 1;
    add_to_set_of_ints(si, new_int);
  }

  print_set_of_ints(si);
  printf("\n");
  int value=0;
  printf("Enter the element that you want to delete: \n");
  scanf("%d", &value);
  delete_from_set_of_ints(si ,value);
  print_set_of_ints(si);
  printf("\n");
  free_set_of_ints(si);

  return EXIT_SUCCESS;
}
 
/* Local Variables: */
/* mode: c          */
/* compile-command: "make rand-uniq" */
/* End:             */
