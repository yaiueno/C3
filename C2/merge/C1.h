#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
typedef struct {
    int id;
    int score;
}User;
int *random_array(int);
int count (char*);
int *read_array(char*, int);
void show_array(int*, int);