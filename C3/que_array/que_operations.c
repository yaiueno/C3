#include "C3.h"

int *init_queue(int k, int *head,int *tail){
    int i, *A;
     
    A = (int*)malloc(sizeof(int) * k);

    for(i=0;i<k;i++)A[i] = INT_MAX;
    *head = 0;
    *tail = 0;

    return A;
}

void enqueue(int *Q,int a,int *tail){
    Q[*tail] = a;
    *tail = *tail + 1;

    return;
}

int dequeue(int *Q, int *head){
    *head = *head + 1;
    return Q[*head -1];
}