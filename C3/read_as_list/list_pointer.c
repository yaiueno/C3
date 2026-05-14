#include <stdio.h>
#include <stdlib.h>

struct cell{
    int no;
    struct cell *next;
};

int main(void){
    struct cell *tmp;

    printf("The size of struct cell is %ld bytes\n", sizeof(struct cell));
    tmp = (struct cell *)malloc(sizeof(struct cell));
    tmp -> no = 100;
    tmp -> next = (struct cell *)NULL;
    
    printf("tmp->no = %d\n", tmp->no);
    printf("tmp->next = %p\n", tmp->next);
    free(tmp);

    return 0;
}