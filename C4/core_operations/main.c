#include "C4.h"

int main(int argc, char **argv){
    int n, min=INT_MAX, index, L[10] = {2, 5, 3, 4, INT_MAX, INT_MAX, 7, 5, INT_MAX, 1};

    n = 10;
    show_array(L, n);
    printf("\n");

    printf("(1)\n");
    Extract_Min(L, n, &min, &index);
    printf("%d %d\n", min, index);
    show_array(L, n);
    printf("\n");

    printf("(2)\n");
    Decrease_Key(L, 4, 5);
    show_array(L, n);
    printf("\n");

    printf("(3)\n");
    Extract_Min(L, n, &min, &index);
    printf("%d %d\n", min, index);
    show_array(L, n);
    printf("\n");

    printf("(4)\n");
    Decrease_Key(L, 6, 2);
    show_array(L, n);
    printf("\n");

    printf("(5)\n");
    Extract_Min(L, n, &min, &index);
    printf("%d %d\n", min, index);
    show_array(L, n);
    
    return 0;
}