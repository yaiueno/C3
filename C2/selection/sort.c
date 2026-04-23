#include "C2.h"

void selection_sort(int *A, int k){
    int i, j, p, min;
    
    for (i = 0; i < k-1; i++){
        min = A[i];
        p = i;
        for(j = i + 1;j < k;j++){
            if(A[j] < min){
                min = A[j];
                p = j;
            }
        }
        A[p] = A[i];
        A[i] = min;
        //show_array(A, k);
    }
    return;
}

void insertion_sort(int *A, int n){
    int i, j, tmp;
    
    for(i = 1; i < n; i++){
        tmp = A[i];
        j = i;
        while (0 < j){
            A[j] = A[j-1];
                if(A[j-1]<tmp){
                    break;
                }
            j--;
        }
        A[j] = tmp;
        //show_array(A, n);
    }
}