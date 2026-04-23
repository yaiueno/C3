#include "C1.h"

int main(int argc, char **argv) {
    int n;
    int *TEST;

    if (argc != 2) {
        fprintf(stderr, "usage: %s array.txt\n", argv[0]);
        return 1;
    }

    n = count(argv[1]);
    TEST = read_array(argv[1], n);
    show_array(TEST, n);

    free(TEST);
    return 0;
}
