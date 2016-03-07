#ifndef SET_OF_INTS_H
#define SET_OF_INTS_H

struct SetOfInts;

struct SetOfInts *new_set_of_ints(int n);
void free_set_of_ints(struct SetOfInts *si);

int size_of_set_of_ints(struct SetOfInts *si);
void add_to_set_of_ints(struct SetOfInts *si, int value);
void print_set_of_ints(struct SetOfInts *si);
void delete_from_set_of_ints(struct SetOfInts *si, int value);
int get_number_of_buckets(int number_of_elements);
int check_for_removal(struct SetOfInts* si, int value);
int hash_int(int num_of_buckets, int value);
void rehash(struct SetOfInts *si,int value,int bucket_id);
#endif
