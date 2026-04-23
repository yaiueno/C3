#include <stdio.h>
int square(int);
int sum(int* ,int);

int main(void){
    int n=10;
    int A[10]={1,3,5,7,9,11,13,15,17,19};
    printf("%d\n",square(n));
    printf("%d\n",sum(A,n));

    return 0;
}

int square(int a){
    return a * a;
}

int sum (int *X, int n){
    int i, s=0;

    for (i=0; i<n;i++){
        s = s +X[i]* X[i];
    }
    return s;
}