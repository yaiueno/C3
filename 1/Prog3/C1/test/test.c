#include <stdio.h>

void input(int *);
void output(int, int);
int square(int);
int cube(int);

int main(void) {
    int n;

    input(&n);
    output(square(n), cube(n));

    return 0;
}

void input(int *a) {
    printf("Input an integer: ");
    scanf("%d", a);
}

void output(int a, int b) {
    printf("The square is %d.\n", a);
    printf("The cube is %d.\n", b);
}

int square(int a) {
    return a * a;
}

int cube(int a) {
    return a * a * a;
}
