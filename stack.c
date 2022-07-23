#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "stack.h"

Node *push(Node *node, int data)
{
    Node *new_node = NULL;

    new_node = (Node *)malloc(sizeof(Node));
    new_node->data = data;
    new_node->next = node;

    return new_node;
}

int pop(Node **node)
{
    if (is_empty(*node)) {
        return false;
    }

    Node *auxiliar = *node;
    int data = auxiliar->data;

    *node = (*node)->next;
    free(auxiliar);

    return data;
}

bool is_empty(Node *node)
{
    if (node != NULL) {
        return false;
    }

    return true;
}

void free_stack(Node **stack)
{
    if (is_empty(*stack)) {
        return;
    }

    Node *walker = *stack, *auxiliar = NULL;

    while (walker != NULL) {
        auxiliar = walker;
        walker = walker->next;
        auxiliar->data = 0;
        auxiliar->next = NULL;
        free(auxiliar);
    }

    *stack = NULL;
}
