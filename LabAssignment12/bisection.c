#include <stdio.h>
#include "stack.h"

int Bisection(double (*func)(double), Interval start,
              double tol, int maxIter, double *root)
{
    node* top = NULL;
 
    if (func(start.a) * func(start.b) > 0)
    {
        printf("f(a) and f(b) have the same sign; no root guaranteed.\n");
        return 0;
    }
 
    Push(start, &top);
    int iter = 0;
 
    while (top != NULL && iter < maxIter)
    {
        Interval cur = top->value;
        Pop(&top);
        iter++;
 
        double mid = cur.a + (cur.b - cur.a) / 2.0;
        double fmid = func(mid);
 
        printf("Iter %2d: [%.6f, %.6f]  mid = %.6f  f(mid) = %.6e\n",
               iter, cur.a, cur.b, mid, fmid);
 
        if (fmid == 0.0 || (cur.b - cur.a) / 2.0 < tol)
        {
            *root = mid;
            FreeStack(&top);
            return 1;
        }
 
        /* Push whichever half still has a sign change */
        Interval next;
        if (func(cur.a) * fmid < 0)
        {
            next.a = cur.a;
            next.b = mid;
        }
        else
        {
            next.a = mid;
            next.b = cur.b;
        }
        Push(next, &top);
    }
 
    FreeStack(&top);
    return 0;
}
