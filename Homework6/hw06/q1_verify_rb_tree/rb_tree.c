#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <locale.h>

#include "student.h"

#define MAX_NAME 256
#define RBT_BLACK 0
#define RBT_RED 1

void print_student_info(int student_index);

struct RBTreeNode {
  int student_idx;

  int color;
  struct RBTreeNode *left;
  struct RBTreeNode *right;
};

struct RBTreeNode *new_node(int student_idx, int color);
void free_tree(struct RBTreeNode *root);

struct RBTreeNode *add_student(struct RBTreeNode *root, int student_idx, int sw);
int search_tree(struct RBTreeNode *root, const char *name, int *comp_counter);
void print_students(struct RBTreeNode *root);
int find_max(int comp_arr[], int n_std);
int find_min(int comp_arr[], int n_std);
int find_ave(int comp_arr[], int n_std);
int black_height(struct RBTreeNode *root, int height);

static struct RBTreeNode z = {
  .student_idx = -1,
  .color = RBT_BLACK,
  .left = &z,
  .right = &z
};

int main(int argc, char **argv)
{
  // Enabling Turkish string comparison: Set LC_COLLATE variable to
  // Turkish locale.  You might also need to enable Turkish support in
  // your OS.  For Ubuntu install the necessary package:
  //   $ sudo apt-get install language-pack-tr
  // and reopen your terminal window.
  setlocale(LC_COLLATE, "tr_TR.UTF-8");

  int n_students = sizeof(ceng112_students) / sizeof(ceng112_students[0]);
  struct RBTreeNode *root = &z;
  for (int i = 1; i < n_students; ++i) {
    root = add_student(root, i, 0);
    root->color = RBT_BLACK;
  }
		
  int b_height=black_height(root, 0);
  if(b_height !=0)
    {
      printf("Tree is balanced!\n");
      printf("Black height of red black tree %d\n",b_height);
    }
  int comp_arr[n_students];

  for (int i = 0; i < n_students; ++i) {	
    int n_comp = 0;
    int student_idx = search_tree(root, ceng112_students[i].name, &n_comp);
    if (student_idx >= 0) {
      comp_arr[i]=n_comp;
    } else {
      print_students(root);
      fprintf(stderr, "There is no student named %s\n", ceng112_students[i].name);
    }
  }
  int max_comp = find_max(comp_arr, n_students);
  int min_comp = find_min(comp_arr, n_students);
  int ave_comp = find_ave(comp_arr, n_students);

  printf("maximum number of comparision: %d\n",max_comp);
  printf("minimum number of comparision: %d\n",min_comp);
  printf("average number of comparision: %d\n",ave_comp);

  free_tree(root);

  return EXIT_SUCCESS;
}

struct RBTreeNode *new_node(int student_idx, int color)
{
  struct RBTreeNode *n = malloc(sizeof(*n));
  if (n == NULL) {
    fprintf(stderr, "Out of memory!\n");
    exit(EXIT_FAILURE);
  }

  n->student_idx = student_idx;
  n->left = &z;
  n->right = &z;
  n->color = color;

  return n;
}

void free_tree(struct RBTreeNode *root)
{
  if (root == &z)
    return;

  free_tree(root->left);
  free_tree(root->right);
  free(root);
}

struct RBTreeNode *rotate_left(struct RBTreeNode *n)
{
  struct RBTreeNode *x = n->right;
  n->right = x->left;
  x->left = n;
  return x;
}

struct RBTreeNode *rotate_right(struct RBTreeNode *n)
{
  struct RBTreeNode *x = n->left;
  n->left = x->right;
  x->right = n;
  return x;
}

struct RBTreeNode *add_student(struct RBTreeNode *root, int student_idx, int sw)
{
  if (root == &z)
    return new_node(student_idx, RBT_RED);

  if (root->left->color == RBT_RED
      && root->right->color == RBT_RED) {
    root->left->color = RBT_BLACK;
    root->right->color = RBT_BLACK;
    root->color = RBT_RED;
  }

  /* // strcoll is like strcmp but respects language order */
  int cmp_res = strcoll(ceng112_students[student_idx].name, ceng112_students[root->student_idx].name);
  if (cmp_res < 0) {
    root->left = add_student(root->left, student_idx, 0);
    if (root->color == RBT_RED && root->left->color == RBT_RED && sw)
      root = rotate_right(root);
    if (root->left->color == RBT_RED && root->left->left->color == RBT_RED) {
      root = rotate_right(root);
      root->color = RBT_BLACK;
      root->right->color = RBT_RED;
    }
  } else {
    root->right = add_student(root->right, student_idx, 1);
    if (root->color == RBT_RED && root->right->color == RBT_RED && !sw)
      root = rotate_left(root);
    if (root->right->color == RBT_RED && root->right->right->color == RBT_RED) {
      root = rotate_left(root);
      root->color = RBT_BLACK;
      root->left->color = RBT_RED;
    }
  }

  return root;
}

int search_tree(struct RBTreeNode *root, const char *name, int *comp_counter)
{
  if (root == &z)
    return 0;
		
  // strcoll is like strcmp but respects language order
  int cmp_res = strcoll(name, ceng112_students[root->student_idx].name);
  (*comp_counter)++;
  if (cmp_res == 0)
    return root->student_idx;
  else if (cmp_res < 0)
    return search_tree(root->left, name, comp_counter);
  else
    return search_tree(root->right, name, comp_counter);
}

void print_students(struct RBTreeNode *root)
{
  if (root == &z)
    return;

  if (root->left != &z)
    print_students(root->left);

  print_student_info(root->student_idx);

  if (root->right != &z)
    print_students(root->right);
}

void print_student_info(int student_idx)
{
  printf("id/name: %u / %s\n", ceng112_students[student_idx].id,
	 ceng112_students[student_idx].name);
}

int find_max(int comp_arr[], int n_std)
{
  int max_comp=comp_arr[0];
  for(int i=1; i < n_std; i++)
    {
      if(comp_arr[i] > max_comp)
	{
	  max_comp=comp_arr[i];
	}
    }
  return max_comp;
}
int find_min(int comp_arr[], int n_std)
{
  int min_comp=comp_arr[0];
  for(int i=1; i < n_std; i++)
    {
      if(comp_arr[i] < min_comp)
	{
	  min_comp=comp_arr[i];
	}
    }
  return min_comp;
}

int find_ave(int comp_arr[], int n_std)
{
  int sum=0;
  for(int i=0; i < n_std; i++)
    {
      sum+=comp_arr[i];
    }
  return sum/n_std;
}

int black_height(struct RBTreeNode *root, int height)
{
  if (root == &z)
    {
      int height = 1;
      return height;
    }
  else
    {
      int left_height = black_height(root->left, height);
      int right_height = black_height(root->right, height);
      if(left_height == right_height)
	{
	  if(root->color==RBT_BLACK)
	    {
	      int height = 0;
	      height = left_height;
	      (height)++;
	      return height;
	    }
	  return left_height;
	}
      else
	{
	  printf("Error! student idx: %d is not balanced!",root->student_idx);
	  return 0;
	}
    }
}

/* Local Variables: */
/* mode: c          */
/* compile-command: "make search-tree" */
/* End:             */
