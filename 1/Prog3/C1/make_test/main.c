#include "test.h"

int main(void) {
    int n;

    input(&n);
    output(square(n), cube(n));

    return 0;
}
