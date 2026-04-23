#include <stdio.h>

void substitute(int *a, int *b) {
    *a = 10;
    *b = 100;
}

int main(void) {
    int i = 1;
    int j = 2;

    printf("i=%d j=%d\n", i, j);
    substitute(&i, &j);
    printf("i=%d j=%d\n", i, j);

    return 0;
}
