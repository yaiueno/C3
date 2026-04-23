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
        show_array(A, k);
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

void merge(int *A, int left, int right){
    int i,mid = (left + right) / 2;
    int  *B, p, q, r;

    if(left >= right){
        return;
    }else{
        B = (int*)malloc(sizeof(int) * (right - left + 1));
        p = left;
        q = mid + 1;
        r = 0;
        while ((p <= mid) && (q <= right)){
            if(A[p] < A[q]){
                B[r] = A[p];
                r++;
                p++;
            }else{
                B[r] = A[q];
                r++;
                q++;
            }
        }
        if(p > mid){
            while (q <= right){
                B[r] = A[q];
                r++;
                q++;
            }
        }else{
            while (p <= mid){
                B[r] = A[p];
                p++;
                r++;
            }
        }
        for (i = left; i <= right; i++){
            A[i] = B[i - left];
        }
        free(B);
        return;
    }
}

void merge_sort(int *A,int left, int right){
    printf("%d %d START\n", left, right);
    show_array(A, right - left);
    if (left == right){
        printf("%d %d END\n", left, right);
        return;
    }else{
        merge_sort(A, left, (left+right) / 2);
        merge_sort(A, (left + right)/2 + 1, right);
    }
    merge(A, left, right);
    printf("%d %d END\n", left, right);

    return;
}