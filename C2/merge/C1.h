#ifndef C1_H    // もし C1_H がまだ定義されていなければ
#define C1_H    // C1_H を定義する

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
typedef struct {
    int id;
    int score;
}User;
int *random_array(int);
int count (char*);
User *read_array(char*, int);
void show_array(User*, int);
#endif