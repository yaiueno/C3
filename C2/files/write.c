#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void random_array(int k);

int main(int argc, char **argv){
    int i, n;
    
    if(argc != 2){
        fprintf(stderr, "%s length\n", argv[0]);
        return 1;
    }
    
    n = atoi(argv[1]);

    srand((unsigned int)time(0));
    random_array(n);

    return 0;
}

void random_array(int k){
    int i;

    for (i=0;i < k; i++)
    printf("%d\n",rand()%1000000);
    return;
}