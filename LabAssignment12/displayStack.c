#include <stdio.h>
#include "stack.h"

void Display(node * top)
{
    if (top == NULL){return;}

    printf("Stack (top first):\n");
    node* ptr = top;
    printf(" -------------------------------------\n");
    printf("Position: Interaval[a,b]");
    while (ptr != NULL)
    {
        printf("%d: [%.6f, %.6f]\n",
               ptr->position, ptr->value.a, ptr->value.b);
        ptr = ptr->next;
    }
    printf(" --------------------------------------\n");
}

void FreeStack(node ** top)
{
    while (*top != NULL)
        Pop(top);
}

