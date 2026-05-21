#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

struct cell{
    int no;
    int w;
    struct cell *next;
};

struct cell **read_as_Alist(char *, int *);
void show_as_Alist(struct cell **,int );
void free_Alist(struct cell **,int);

void show_array(int *,int);

void Extract_Min(int *, int, int *, int *);
void Decrease_Key(int *, int, int);