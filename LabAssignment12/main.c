#include <stdio.h>
#include <math.h>
#include "stack.h"

double f(double x)
{
    return x * x - 2*x + 1;     
}

int main(void)
{
    node* demo = NULL;
    Interval i1 = { 1.0, 2.0 };
    Interval i2 = { 1.5, 2.0 };
    Interval i3 = { 1.5, 1.75 };
 
    Push(i1, &demo);
    Push(i2, &demo);
    Push(i3, &demo);
 
    Peek(demo);
    Display(demo);
 
    printf("\nPop,Peek and push demo.\n");
    Pop(&demo);
    Peek(demo);
    Display(demo);
    FreeStack(&demo);
    printf("\n");
 
    double root;
    Interval start = { 1.0, 2.0 };
    if (Bisection(f, start, 1e-6, 100, &root))
        printf("\nRoot found: %.6f  (f(root) = %.2e)\n", root, f(root));
    else
        printf("\nRoot not found.\n");
 
    return 0;
}

