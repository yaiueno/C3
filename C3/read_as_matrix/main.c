#include "C3.h"

int main(int argc, char **argv){
    int n, **A;
    A = read_as_matrix(argv[1], &n);
    show_as_matrix(A, n);

    free(A[0]);
    free(A);
    return 0;
}