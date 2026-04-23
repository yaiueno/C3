#include "C1.h"
typedef struct {
    int id;
    int score;
}User;

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

User *read_array (char *filename, int n){
    User *A;
    FILE *fp;

    fp = fopen(filename, "r");
    if(fp == NULL){
        fprintf(stderr, "open error %s\n", filename);
        exit(1);
    }
    A= (User *)malloc(sizeof(User) * n );
    int i;
    
    for (i = 0;i < n; i++){
        A[i].id = i;
        if(fscanf(fp, "%d", &A[i].score)==EOF){
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