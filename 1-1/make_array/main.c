#include "C1.h"

int main(int argc, char ** argv){
    int n, *TEST;

    n = count(argv[1]);
    TEST = read_array(argv[1],n);
    show_array(TEST,n);

    free(TEST);

    return 0;
}