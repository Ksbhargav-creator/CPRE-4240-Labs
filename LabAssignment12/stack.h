#ifndef STACK_H
#define STACK_H

#include <stdio.h>

typedef struct {
    double a, b;            
} Interval;
 
typedef struct node {
    Interval value;
    int position;          
    struct node *next;
} node;

void Push(const Interval input, node **top);
void Pop(node **top);
void Peek(node *top);
void Display(node *top);
void FreeStack(node **top);
int  Bisection(double (*func)(double), Interval start,
               double tol, int maxIter, double *root);
#endif
