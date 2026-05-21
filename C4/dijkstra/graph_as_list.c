#include "C4.h"

struct cell **read_as_Alist(char *filename,int *n){
    int i,p,q,r,c;
    struct cell **root,*tmp;
    FILE *fp;
    fp = fopen(filename, "r");
    if(fp == NULL){
        fprintf(stderr, "open error %s\n",filename);
        exit(1);
    }

    fscanf(fp, "%d", &c);
    root = (struct cell **)malloc(sizeof(struct cell*) * c);

    for(i = 0; i < c; i++){
        root[i] = (struct cell *)NULL;
    }

    while(fscanf(fp, "%d %d %d",&p,&q,&r) != EOF){
        tmp = (struct cell *)malloc(sizeof(struct cell));

        tmp->no = q;
        tmp->w = r;
        tmp->next = root[p];
        root[p] = tmp;

        tmp = (struct cell*)malloc(sizeof(struct cell));

        tmp->no = p;
        tmp->w = r;
        tmp->next = root[q];
        root[q] = tmp;
    }

    fclose(fp);
    *n = c;
    return root;
}

void show_as_Alist(struct cell **root, int c){
    int i;
    struct cell *tmp;

    for(i = 0; i < c;i++){
        printf("%d:",i);
        tmp = root[i];
        while(tmp != NULL){
            printf("[%d, %d]", tmp->no, tmp->w);
            tmp = tmp->next;
        }
        printf("\n");
    }
}

void free_Alist(struct cell **root,int c){
    int i;
    struct cell *tmp;

    for(i = 0; i < c;i++){
        tmp = root[i];
        while(tmp != NULL){
            tmp = root[i]->next;
            free(root[i]);
            root[i] = tmp;
        }
    }
    return;
}