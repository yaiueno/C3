#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

void selection_sort(int *A, int k);
void insertion_sort(int *A,int k);
void merge(int *, int, int);
void merge_sort(int *, int, int);

int count(char *filename);
int *random_array(int);
int *read_array(char *filename, int k);
void show_array(int *L, int n);