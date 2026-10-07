#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

void Pop(node ** top)
{
    if (*top == NULL)
    {
        printf("Stack is empty, nothing to pop.\n");
        return;
    }
 
    node* temp = *top;
    *top = temp->next;
    free(temp);
 
    node* ptr = *top;
    while (ptr != NULL)
    {
        ptr->position = ptr->position - 1;
        ptr = ptr->next;
    }
}
