#include "C1.h"

int *random_array(int n) {
    int i;
    int *A;

    A = (int *)malloc(sizeof(int) * n);
    if (A == NULL) {
        fprintf(stderr, "malloc error\n");
        exit(1);
    }

    for (i = 0; i < n; i++) {
        A[i] = rand() % 1000;
    }

    return A;
}

int count(char *filename) {
    int a;
    int k;
    FILE *fp;

    fp = fopen(filename, "r");
    if (fp == NULL) {
        fprintf(stderr, "open error %s\n", filename);
        exit(1);
    }

    k = 0;
    while (fscanf(fp, "%d", &a) != EOF) {
        k++;
    }

    fclose(fp);
    return k;
}

int *read_array(char *filename, int n) {
    int i;
    int *A;
    FILE *fp;

    fp = fopen(filename, "r");
    if (fp == NULL) {
        fprintf(stderr, "open error %s\n", filename);
        exit(1);
    }

    A = (int *)malloc(sizeof(int) * n);
    if (A == NULL) {
        fprintf(stderr, "malloc error\n");
        fclose(fp);
        exit(1);
    }

    for (i = 0; i < n; i++) {
        if (fscanf(fp, "%d", &A[i]) == EOF) {
            break;
        }
    }

    fclose(fp);
    return A;
}

void show_array(int *A, int k) {
    int i;

    for (i = 0; i < k; i++) {
        if (A[i] < INT_MAX) {
            printf("%d ", A[i]);
        } else {
            printf("N ");
        }
    }
    printf("\n");
}
