#include "C1.h"
#include "C2.h"

int main(int argc, char **argv){
    int n;
    User *Test;
    

    n = count(argv[1]);
    Test = read_array(argv[1], n);

    printf("Before:");
    show_array(Test, n);
    
    merge_sort(Test, 0, n-1);
    printf("After:");
    show_array(Test, n);


    printf("%d %d %d %d %d\n",Test[9999].id,Test[19999].id,Test[29999].id,Test[39999].id,Test[49999].id);
    free(Test);
    return 0;
}