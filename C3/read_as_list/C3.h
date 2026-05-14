#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

struct cell
{
    int no;
    struct cell *next; 
};

struct cell **read_as_Alist(char *, int *);
void show_as_Alist(struct cell **, int);
void free_Alist(struct cell **,int);