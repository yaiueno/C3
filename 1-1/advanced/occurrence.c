#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

int count(char*);
int *read_array(char*, int);
void show_array(int*, int);

int main(int argc, char **argv){
    int i,n ,*TEST ,sum = 0;

    n = count(argv[1]);
    TEST = read_array(argv[1], n);

    int counter[1000] = {0};
    i=0;
    while(i<n){
        counter[TEST[i]] = counter[TEST[i]] + 1;
        i++;
    }
    i=0;
    int most=0;
    while(i<1000){
        if(counter[i]>counter[most]){
            most = i;
        }
        i++;
    }

    free(TEST);
    printf("%d\n",most);
    return 0;
}

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