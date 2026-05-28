#include "C4.h"

int main(int argc, char **argv){
    int i, *L, *S, *path, n, min, index, target;
    struct cell **root, *tmp;
    target = atoi(argv[2]);
    root = read_as_Alist(argv[1], &n);

    L = (int *)malloc(sizeof(int) * n);
    S = (int *)malloc(sizeof(int) * n);
    path = (int *)malloc(sizeof(int) * n);

    L[0] = 0;
    path[0] = 0;
    S[0] = INT_MAX;
    for(i = 1; i < n; i++){
        L[i] = INT_MAX;
        S[i] = INT_MAX;
        path[i] = -1;
    }
    
    printf("\n");
    for (i = 0;i < n;i++){
        Extract_Min(L,n,&min, &index);
        printf("A");
        if(index < 0)
            break;
        else
            S[index] = min;
        show_array(S,n);
        tmp = root[index];
        while(tmp != NULL){
            if(S[index] + tmp->w < L[tmp->no]){ 
                Decrease_Key(L,tmp->no, S[index] + tmp->w);
                path[tmp->no] = index;
            }
        tmp = tmp->next;
        }
        
    }
    show_array(L,n);
    printf("\n");
    show_array(S,n);
    printf("\n");
    printf("%d",S[target]);
    printf("\n");
    print_path(path, target);
    printf("\n");
    free(L);
    free(S);
    free_Alist(root,n);
    return 0;
}