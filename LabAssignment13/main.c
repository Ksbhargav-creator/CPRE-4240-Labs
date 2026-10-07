#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "matrix.h"

// Standard normal random number (Box-Muller)
double randn()
{
    double u1 = (rand()+1.0)/(RAND_MAX+2.0);   
    double u2 = (rand()+1.0)/(RAND_MAX+2.0);
    return sqrt(-2.0*log(u1))*cos(2.0*M_PI*u2);
}

// Relative error ||x - xrec|| / ||x||
double rel_error(const vector* x, const vector* xrec)
{
    vector d = vector_sub(x,xrec);
    double err = vector_norm(&d)/vector_norm(x);
    delete_vector(&d);
    return err;
}

// Direct solve A xrec = b  (solve() overwrites its inputs, so pass copies)
vector direct_solve(const matrix* A, const vector* b)
{
    matrix Ac = matrix_copy(A);
    vector bc = vector_copy(b);
    vector xrec = solve(&Ac,&bc);
    delete_matrix(&Ac);
    delete_vector(&bc);
    return xrec;
}

// Tikhonov: (A^T A + lambda I) xrec = A^T b
vector tikhonov_solve(const matrix* A, const vector* b, const double lambda)
{
    const int n = A->cols;
    matrix AT  = matrix_transpose(A);
    matrix ATA = matrix_mult(&AT,A);
    for (int i=1; i<=n; i++)
    { mget(ATA,i,i) += lambda; }
    vector ATb = matrix_vector_mult(&AT,b);

    vector xrec = solve(&ATA,&ATb);
    delete_matrix(&AT);
    delete_matrix(&ATA);
    delete_vector(&ATb);
    return xrec;
}

int main()
{
    const int n = 128;
    const double sigma[2]  = {1.0e-4, 1.0e-2};
    const double lambda[2] = {1.0e-4, 1.0e-2};

    srand(12345);

    // Blur operator A = (1/4) tridiag(1,2,1), zero boundary condition
    matrix A = new_matrix(n,n);
    for (int i=1; i<=n; i++)
    {
        mget(A,i,i) = 2.0/4.0;
        if (i>1) { mget(A,i,i-1) = 1.0/4.0; }
        if (i<n) { mget(A,i,i+1) = 1.0/4.0; }
    }

    // True signal: x_i = 1 for n/4 <= i <= n/2, 0 else
    vector x = new_vector(n);
    for (int i=n/4; i<=n/2; i++)
    { vget(x,i) = 1.0; }

    // Blurred signal b = A x
    vector b = matrix_vector_mult(&A,&x);

    vector x0 = direct_solve(&A,&b);
    double err0 = rel_error(&x,&x0);
    printf("\n n = %d\n", n);
    printf(" No noise, direct solve:  ||x - xrec||/||x|| = %10.3e\n", err0);
    delete_vector(&x0);

    for (int s=0; s<2; s++)
    {
        // b + eps, eps_i ~ N(0, sigma^2); same noisy b used for every method
        vector bnoisy = vector_copy(&b);
        for (int i=1; i<=n; i++)
        { vget(bnoisy,i) += sigma[s]*randn(); }

        printf("\n sigma = %8.1e\n", sigma[s]);

        vector xrec = direct_solve(&A,&bnoisy);
        printf("   Direct solve:               ||x - xrec||/||x|| = %10.3e\n",
               rel_error(&x,&xrec));
        delete_vector(&xrec);

        for (int l=0; l<2; l++)
        {
            vector xtik = tikhonov_solve(&A,&bnoisy,lambda[l]);
            printf("   Tikhonov, lambda = %8.1e: ||x - xrec||/||x|| = %10.3e\n",
                   lambda[l], rel_error(&x,&xtik));
            delete_vector(&xtik);
        }

        delete_vector(&bnoisy);
    }
    printf("\n");

    delete_matrix(&A);
    delete_vector(&x);
    delete_vector(&b);
    return 0;
}