#include <stdio.h>
#include "stack.h"

void Peek(node * top)
{
    if (top == NULL)
    {
        printf("Stack is empty.\n");
        return;
    }
 
    printf("Top node (position %d): [%.6f, %.6f]\n",
           top->position, top->value.a, top->value.b);
}
