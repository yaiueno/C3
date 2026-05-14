#include "C3.h"

int main(int argc, char **argv){
    int n;
    struct cell **root;
    root = read_as_Alist(argv[1], &n);
    show_as_Alist(root, n);
    free_Alist(root, n);

    return 0;
}