#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

int count(char *);
int *read_array(char *, int);
void show_array(int *, int);

int main(int argc, char **argv) {
    int i;
    int n;
    int *TEST;
    int sum = 0;

    if (argc != 2) {
        fprintf(stderr, "usage: %s array.txt\n", argv[0]);
        return 1;
    }

    n = count(argv[1]);
    TEST = read_array(argv[1], n);

    show_array(TEST, n);

    for (i = 0; i < n; i++) {
        sum = sum + TEST[i];
    }
    printf("%d\n", sum);

    free(TEST);
    return 0;
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

void show_array(int *A, int cnt) {
    int i;

    for (i = 0; i < cnt; i++) {
        if (A[i] < INT_MAX) {
            printf("%d ", A[i]);
        } else {
            printf("N ");
        }
    }
    printf("\n");
}
