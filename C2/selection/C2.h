#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

void selection_sort(int *A, int k);
void insertion_sort(int *A,int k);

int count(char *filename);
int *read_array(char *filename, int k);
void show_array(int *L, int n);