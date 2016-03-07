#include "set_of_ints.h"

#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#define EMPTY_BUCKET INT_MIN
#define MAXIMUM_LOAD_FACTOR 2.0f/3.0f

struct SetOfInts {
  int *values;
  int num_of_elements;
  int num_of_buckets;

};
 
int get_number_of_buckets(int number_of_elements)
{
  
  FILE *fin = fopen("prime_numbers.txt", "r+");
  if (fin == NULL) {
    fprintf(stderr, "Error opening prime numbers file !\n");
    exit(EXIT_FAILURE);
  }
  int closest_prime=0;
  while (fscanf(fin, "%d",&closest_prime) == 1){
    if((float)number_of_elements/(float)closest_prime < MAXIMUM_LOAD_FACTOR)
      return closest_prime;
       
  }
  return EXIT_FAILURE;
}

struct SetOfInts *new_set_of_ints(int number_of_elements)
{
  struct SetOfInts *si = malloc(sizeof(*si));
  if (si == NULL) {
    fprintf(stderr, "Out of memory!\n");
    exit(EXIT_FAILURE);
  }
        
  si->num_of_buckets=get_number_of_buckets(number_of_elements);
  si->values = malloc(sizeof(int) *  si->num_of_buckets);
  if (si->values == NULL) {
    fprintf(stderr, "Out of memory!\n");
    exit(EXIT_FAILURE);
  }
	
 
  for(int i = 0; i <  si->num_of_buckets; i++){
    si->values[i] = EMPTY_BUCKET;
  }

  si-> num_of_elements = 0;
  return si;
}

void free_set_of_ints(struct SetOfInts *si)
{
  if (si != NULL) {
    free(si->values);
    free(si);
  }
}

int size_of_set_of_ints(struct SetOfInts *si)
{
  return si-> num_of_elements;
}

int search_hash_table(struct SetOfInts *si, int value)
{
  int bucket_id = hash_int(si->num_of_buckets,value);

  int value_first_bucket = si->values[bucket_id];
  while (si->values[bucket_id] != EMPTY_BUCKET) 
    {
      if (si->values[bucket_id] == value)
	return si->values[bucket_id];
      else if (++bucket_id >= si->num_of_buckets)
	bucket_id = 0;
      if(value_first_bucket == si->values[bucket_id])
	break;
    }

  return -1;
}

void add_to_set_of_ints(struct SetOfInts *si, int value)
{  
  if(search_hash_table(si, value) < 0)
    {
      int bucket_id = hash_int(si->num_of_buckets,value);

      while (si->values[bucket_id] != EMPTY_BUCKET)
	if (++bucket_id >= si->num_of_buckets)
	  bucket_id = 0;

      si->values[bucket_id]=value;
      si->num_of_elements++;
    }
}

void rehash(struct SetOfInts *si, int value, int bucket_id){
  
  si->values[bucket_id]=EMPTY_BUCKET;
  int rehashed_bucket_id = hash_int(si->num_of_buckets,value);
      while (si->values[rehashed_bucket_id] != EMPTY_BUCKET)
	if (++rehashed_bucket_id >= si->num_of_buckets)
	  rehashed_bucket_id = 0;

  si->values[rehashed_bucket_id]=value;
}

void delete_from_set_of_ints(struct SetOfInts *si, int value)
{
  if(search_hash_table(si, value) > 0)
    {
      int bucket_id = hash_int(si->num_of_buckets,value);
      while(si->values[bucket_id]!=value)
	if (++bucket_id >= si->num_of_buckets)
	  bucket_id = 0;
  
      si->values[bucket_id]=EMPTY_BUCKET;
      
      if(++bucket_id >= si->num_of_buckets )
	bucket_id=0;

      while(bucket_id < si->num_of_buckets){
	if(si->values[bucket_id]!=EMPTY_BUCKET){
	  rehash(si,si->values[bucket_id],bucket_id);
	}
	bucket_id++;
      }
      si->num_of_elements--;
    }
  else{
    fprintf(stderr, "%d does not exist in the set!\n",value);
    exit(EXIT_FAILURE);
  }

}

void print_set_of_ints(struct SetOfInts *si)
{
  for(int i = 0 ; i <  si->num_of_buckets; i++)
    {
      if(si->values[i] != EMPTY_BUCKET)
	printf("%d\t", si->values[i]);
    }
}

int hash_int(int num_of_buckets, int value)
{
  return value % (num_of_buckets);
}
