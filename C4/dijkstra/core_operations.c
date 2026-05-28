#include "C4.h"

void Extract_Min(int *L, int n, int *min, int *index){
    int i, tmp_min, tmp_index;

    tmp_min = INT_MAX;
    tmp_index = -1;
    for (i = 0; i < n; i++){
        if((0 <= L[i]) && (L[i] < tmp_min)){
            tmp_min = L[i];
            tmp_index = i;
        }
    }

    L[tmp_index] = -2;
    *min =tmp_min;
    *index = tmp_index;

    return;
}

void Decrease_Key(int *L, int j, int z){
    L[j] = z;
}

void print_path(int *Path, int curr){
    if (curr == 0){
        printf("0");
        return;
    }

    print_path(Path, Path[curr]);

    printf(" → %d",curr);
}