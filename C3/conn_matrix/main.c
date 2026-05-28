#include "C3.h"

int main(int argc, char **argv){
    int i, j, *VISIT, *Q, n, **A, tail, head;
    
    A = read_as_matrix(argv[1], &n);
    VISIT = (int*)malloc(sizeof(int) * n);
    Q = init_queue(n, &head, &tail);

    VISIT[0] = 1;
    for (i = 1; i < n;i++){
        VISIT[i] = 0;
    }
    enqueue(Q, 0, &tail);
    while (head < tail){
        i = dequeue(Q, &head);
        printf("%d:\n", i);
        for(j = 0;j < n;j++){
            if(A[i][j] == 1 && VISIT[j] == 0){
                VISIT[j] = 1;
                enqueue(Q,j,&tail);
                show_array(Q, n);
            }
        }
    }
    show_array(VISIT, n);
    free(A[0]);
    free(A);

    free(VISIT);
    free(Q);
    return 0;
}