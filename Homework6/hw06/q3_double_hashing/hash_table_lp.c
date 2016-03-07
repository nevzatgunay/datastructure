#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <locale.h>

#include "student.h"

#define MAX_NAME 256

struct HTNode {
  char *key;
  int value;
};

void ht_node_set(struct HTNode *n, const char *key, int value);

struct HashTable {
  int n_buckets;
  struct HTNode *buckets;

  int n_keys;
};

struct HashTable *hash_table_new(int initial_size);
void hash_table_free(struct HashTable *ht);

void hash_table_insert(struct HashTable *ht, char *key, int value);
int hash_table_find(struct HashTable *ht, char *key);
void hash_table_print(struct HashTable *ht);

int hash_string(const char *s);
int hash2_string(const char *s);

int main(int argc, char **argv)
{
  
  int n_students = sizeof(ceng112_students) / sizeof(ceng112_students[0]);
  struct HashTable *ht = hash_table_new(n_students*1.5);
  for (int i = 0; i < n_students; ++i)
    hash_table_insert(ht, ceng112_students[i].name, ceng112_students[i].id);

  char name[MAX_NAME];
  printf("Enter student name: ");
  fgets(name, MAX_NAME, stdin);
  int lname = strlen(name);
  if (name[lname-1] == '\n')
    name[lname-1] = '\0';

  int student_id = hash_table_find(ht, name);
  if (student_id >= 0) {
    printf("%s -> %d\n", name, student_id);
  } else {
    hash_table_print(ht);
    fprintf(stderr, "There is no student named %s\n", name);
  }

  hash_table_free(ht);

  return EXIT_SUCCESS;
}

struct HashTable *hash_table_new(int initial_size)
{
  struct HashTable *ht = malloc(sizeof(*ht));
  if (ht == NULL) {
    fprintf(stderr, "Out of memory!\n");
    exit(EXIT_FAILURE);
  }

  ht->n_buckets = initial_size;
  ht->buckets = malloc(initial_size*sizeof(struct HTNode));
  if (ht->buckets == NULL) {
    fprintf(stderr, "Out of memory!\n");
    exit(EXIT_FAILURE);
  }
  for (int i = 0; i < ht->n_buckets; ++i)
    ht->buckets[i].key = NULL;

  ht->n_keys = 0;

  return ht;
}

void hash_table_free(struct HashTable *ht)
{
  if (ht) {
    for (int i = 0; i < ht->n_buckets; ++i)
      free(ht->buckets[i].key);
    free(ht->buckets);
    free(ht);
  }
}

void hash_table_insert(struct HashTable *ht, char *key, int value)
{
  int i = 0;
  int hash = hash_string(key);
  int bucket_id = abs(hash % ht->n_buckets);
  int hash_2 = 0;
  while (ht->buckets[bucket_id].key != NULL)
    {
      if(i==0)
           hash_2 = hash2_string(key);
      i++;
      int final_hash = hash + hash_2 * i;
      bucket_id = abs(final_hash % ht->n_buckets);
    }

  ht_node_set(&ht->buckets[bucket_id], key, value);
  ++ht->n_keys;
}

int hash_table_find(struct HashTable *ht, char *key)
{
  int i = 0;
  int hash = hash_string(key);
  int bucket_id = abs(hash % ht->n_buckets);
  int hash_2 = 0;
  while (ht->buckets[bucket_id].key != NULL) {
    if (strcmp(ht->buckets[bucket_id].key, key) == 0)
      {                 
	return ht->buckets[bucket_id].value;
      }
    else
      {
	if(i==0)
	      hash_2 = hash2_string(key);
	i++;
        int final_hash= hash + hash_2 * i;
	bucket_id = abs(final_hash % ht->n_buckets);
      }
                       
  }

  return -1;
}

void hash_table_print(struct HashTable *ht)
{
  for (int i = 0; i < ht->n_buckets; ++i)
    if (ht->buckets[i].key != NULL)
      printf("%s -> %d\n", ht->buckets[i].key, ht->buckets[i].value);
}

void ht_node_set(struct HTNode *n, const char *key, int value)
{
  free(n->key);
  n->key = malloc(strlen(key)+1);
  if (n->key == NULL) {
    fprintf(stderr, "Out of memory!\n");
    exit(EXIT_FAILURE);
  }
  strcpy(n->key, key);

  n->value = value;
}

int hash_string(const char *s)
{
  int h = 0;
  while (*s != '\0')
    h = (31*h + (int)*(s++));

  return h;
}

int hash2_string(const char *s){

  return 7 - (strlen(s) % 7 );

}
