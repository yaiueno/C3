#include <stdio.h>
#include <stdlib.h>
#include <limits.h>


int **read_as_matrix(char *, int *);
void show_as_matrix(int **, int);

void show_array(int *, int);
int *init_queue(int, int*, int*);
void enqueue(int *, int, int *);
int dequeue(int*, int*);