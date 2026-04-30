#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv){
    int i,j,n, **TEST, *base;

    if(argc != 2){
        fprintf(stderr, "%s integer.\n", argv[0]);
        exit(1);
    }

    n = atoi(argv[1]);
    TEST = (int **)malloc(sizeof(int*) * n);
    base = (int*)malloc(sizeof(int) * n * n);
    if((TEST == NULL) || (base == NULL)){
        fprintf(stderr, "malloc error\n");
        exit(1);
    }

    for(i = 0; i < n; i++)
        TEST[i] = base + (i * n);

    for (i = 0;i < n;i++){
        for(j = 0; j < n;j++){
            TEST[i][j] = i * j;
            printf("%3d", TEST[i][j]);
        }
        printf("\n");
    }
    free(TEST[0]);
    free(TEST);

    return 0;
}