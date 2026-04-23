#include "C2.h"

int main(int argc, char **argv){
    int n;
    

    n = count(argv[1]);
    TEST = read_array(argv[1], n);

    printf("Before:");
    show_array(TEST, n);
    
    merge_sort(TEST, 0, n-1);
    printf("After:");
    show_array(TEST, n);

    free(TEST);
    return 0;
}