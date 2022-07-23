#ifndef _STACK_H_
#define _STACK_H_

#include <stdbool.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

Node *push(Node *, int);
int pop(Node **);
bool is_empty(Node *);
void free_stack(Node **);

#include "stack.c"

#endif /* _STACK_H_ */