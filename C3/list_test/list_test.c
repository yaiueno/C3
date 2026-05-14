#include <stdio.h>
#include <stdlib.h>
#define N 10

struct cell{
    int no;
    struct cell *next;
};

int main(){
    int i;
    struct cell *root, *tmp;

    root = (struct cell *)NULL;
    for (i = 0;i < N; i++){
        tmp = (struct cell*)malloc(sizeof(struct cell));
        tmp->no = i;
        tmp->next = root;
        root = tmp;
    }

    tmp = root;
    while(tmp != NULL){
        printf("%d", tmp->no);
        tmp = tmp->next;
    }
    printf("\n");

    while (root != NULL){
        tmp = root->next;
        free(root);
        root = tmp;
    }

    return 0;
}
