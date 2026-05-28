#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void random_graph(int n);

int main(int argc, char **argv){
    int n;

    n = atoi(argv[1]);
    srand((unsigned int)time(0));
    random_graph(n);

    return 0;
}

void random_graph(int n){
    int i,j;
    printf("%d\n", n);

    for(i = 0;i < n; i++){
        for(j = i +1; j < n;j++){
            if(rand()% 1000 < 1)printf("%d %d\n", i, j);
        }
    }
    return;
}