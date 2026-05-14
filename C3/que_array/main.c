#include "C3.h"

int main(){
    int sum = 0, n;
    int *Q, head, tail;

    n = 10;
    Q = init_queue(n, &head, &tail);

    enqueue(Q, 2, &tail);
    enqueue(Q, 4, &tail);
    enqueue(Q, 6, &tail);
    printf("(1)sum = %d\n",sum);

    sum += dequeue(Q, &head);
    sum += dequeue(Q, &head);
    printf("(2)sum = %d\n", sum);

    enqueue(Q, 1, &tail);
    enqueue(Q, 3, &tail);
    enqueue(Q, 5, &tail);
    printf("(3)sum = %d\n", sum);

    sum += dequeue(Q, &head);
    sum += dequeue(Q, &head);
    printf("(4)sum = %d\n", sum);

    free(Q);
    return 0;
}