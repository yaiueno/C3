#include <stdio.h>

void substitute(int *a, int *b){
    *a = 10;
    *b = 100;
    return;
}

int main(){
    int i = 1, j = 2;
    printf("i=%d j=%d\n", i, j);
    substitute(&i,&j);
    printf("i=%d j=%d\n", i, j);

    return 0;
}