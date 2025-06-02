#define TASK_H
#ifdef TASK_H

#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define M_PI 3.14159265358979323846
#define M_E 2.71828182845904523536

typedef struct node {
    int type;
    char value[50];
    struct node *prev;
} node;

typedef struct oper {
    size_t rank;
    char name[10];
} oper;

char *stacked(const char* string);
void free_stack(node *h);

#endif
