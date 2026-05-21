#include "C4.h"

int main(int argc, char **argv){
    int i, *L, *S, n, min, index;
    struct cell **root, *tmp;

    root = read_as_Alist(argv[1], &n);

    L = (int *)malloc(sizeof(int) * n);
    S = (int *)malloc(sizeof(int) * n);

    L[0] = 0;
    S[0] = INT_MAX;
    for(i = 1; i < n; i++){
        L[i] = INT_MAX;
        S[i] = INT_MAX;
    }

    printf("\n");
    for (i = 0;i < n;i++){
        Extract_Min(L,n,&index, &min);
        if(index < 0)
            break;
        else
            S[index] = min;
        show_array(S,n);
        tmp = root[index];
        while(tmp != NULL){
            if(S[index] + tmp->w < L[tmp->no]){
                Decrease_Key(L,tmp->no, S[index] + tmp->w);
            }
        }
        tmp = tmp->next;
    }
    show_array(L,n);
    printf("\n");
    show_array(S,n);
    free(L);
    free(S);
    free_Alist(root,n);

    return 0;
}