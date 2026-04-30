#include "C3.h"

int **read_as_matrix(char *filename,int *n){
    int **A, *base, i,j,p,q,c;
    FILE *fp;

    fp = fopen(filename, "r");
    if(fp == NULL){
        fprintf(stderr, "open error %s\n", filename);
        exit(1);
    }
    fscanf(fp, "%d", &c);

    A = (int**)malloc(sizeof(int*) * c);
    base = (int*)malloc(sizeof(int) * c * c);
    if((A == NULL)||(base == NULL)){
        fprintf(stderr, "malloc error\n");
        exit(1);
    }

    for(i = 0;i < c;i++)
        A[i] = base + (i * c);
    for(i = 0;i < c;i++){
        for (j = 0; j < c;j++){
            A[i][j] = 0;
        }
    }

    while (fscanf(fp, "%d %d", &p, &q) != EOF){
        A[p][q] = 1;
        A[q][p] = 1;
    }

    *n = c;

    fclose(fp);
    return A;
}

void show_as_matrix(int **A, int k){
    int i, j;

    for (i = 0; i < k;i++ ){
        for(j=0;j<k;j++){
            printf("%d ", A[i][j]);
        }
        printf("\n");
    }
}