#include "test.h"

void input(int *a) {
    int z;

    printf("Input an integer: ");
    z = scanf("%d", a);
    (void)z;
}

void output(int a, int b) {
    printf("The square is %d. ", a);
    printf("The cube is %d.\n", b);
}
