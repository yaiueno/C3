#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    FILE *fp;
    int value;
    int count[1000] = {0};
    int i;
    int max_num = 0;
    int max_count = -1;

    if (argc != 2) {
        fprintf(stderr, "usage: %s array.txt\n", argv[0]);
        return 1;
    }

    fp = fopen(argv[1], "r");
    if (fp == NULL) {
        fprintf(stderr, "open error %s\n", argv[1]);
        return 1;
    }

    while (fscanf(fp, "%d", &value) == 1) {
        if (0 <= value && value < 1000) {
            count[value]++;
        }
    }
    fclose(fp);

    for (i = 0; i < 1000; i++) {
        if (count[i] > max_count) {
            max_count = count[i];
            max_num = i;
        }
    }

    printf("%d\n", max_num);
    return 0;
}
