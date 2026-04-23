#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv){
    int i,n,*A;

    if(argc != 2){
        fprintf(stderr,"Please input an integer.\n");
        exit(1);
    }

    n = atoi(argv[1]);
    A = (int*)malloc(sizeof(int)*n);
    if (A==NULL){
        fprintf(stderr, "malloc error\n");
        exit(1);
    }

    for(i = 0; i < n; i++) A[i] = i*i;
    for(i =0;i < n; i++)printf("A[%d] = %d\n",i,A[i]);

    free(A);
    return 0;
}