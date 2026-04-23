#include "C1.h"

int count(char *filename){
    int a,k;
    FILE *fp;

    fp = fopen(filename, "r");
    if(fp == NULL){
        fprintf(stderr, "open error %s\n", filename);
        exit(1);
    }
    k = 0;
    while(fscanf(fp, "%d", &a) != EOF){
        k++;
     }
    fclose(fp);
    return k;
}

int *read_array (char *filename, int n){
    int i, *A;
    FILE *fp;

    fp = fopen(filename, "r");
    if(fp == NULL){
        fprintf(stderr, "open error %s\n", filename);
        exit(1);
    }
    A= (int*)malloc(sizeof(int) * n );
    for (i = 0;i < n; i++){
        if(fscanf(fp, "%d", &A[i])==EOF){
            break;
        }
    }
    fclose(fp);
    return A;
}

void show_array(int *A, int cnt){
    int i;

    for (i=0; i < cnt; i++){
        if(A[i] < INT_MAX)
            printf("%d", A[i]);
        else
            printf("N ");
    }
    printf("\n");
    
    return;
}