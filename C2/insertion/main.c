#include "C2.h"

int main(int argc, char **argv){
    int n, *S;

    n = count(argv[1]);
    S = read_array(argv[1], n);

    printf("Before:");
    //show_array(S, n);

    insertion_sort(S, n);

    printf("\n After:");
    //show_array(S, n);

    free(S);
    return 0;
}