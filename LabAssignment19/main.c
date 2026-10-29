#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

static void init_signal(double *x, long N)
{
#pragma omp parallel for
    for (long i = 0; i < N; i++)
    {
        const double t = (double)i / (double)N;
        x[i] = sin(2.0 * M_PI * 50.0 * t) + 0.5 * cos(2.0 * M_PI * 120.0 * t);
    }
    x[N / 3] = -5.0; 
}

static void my_block(long N, int my_rank, int nthreads, long *istart, long *iend)
{
    const long base = N / nthreads, rem = N % nthreads;
    *istart = my_rank * base + (my_rank < rem ? my_rank : rem);
    *iend   = *istart + base + (my_rank < rem ? 1 : 0);
}

//FINE GRAIN: parallelize each loop 

static double fine_2norm(double *x, long N, int nthreads)
{
    double sum = 0.0;
#pragma omp parallel num_threads(nthreads)
    {
#pragma omp for reduction(+:sum)
        for (long i = 0; i < N; i++)
            sum += x[i] * x[i];
        // implicit barrier

        const double norm = sqrt(sum);
#pragma omp for
        for (long i = 0; i < N; i++)
            x[i] /= norm;
    }
    return sqrt(sum);
}

static double fine_maxnorm(double *x, long N, int nthreads)
{
    double mx = 0.0;
#pragma omp parallel num_threads(nthreads)
    {
#pragma omp for reduction(max:mx)
        for (long i = 0; i < N; i++)
            mx = fmax(mx, fabs(x[i]));
        // implicit barrier

#pragma omp for
        for (long i = 0; i < N; i++)
            x[i] /= mx;
    }
    return mx;
}

//COARSE GRAIN: each thread owns one block

static double coarse_2norm(double *x, long N, int nthreads)
{
    double sum = 0.0;
#pragma omp parallel num_threads(nthreads) reduction(+:sum)
    {
        long istart, iend;
        my_block(N, omp_get_thread_num(), omp_get_num_threads(), &istart, &iend);

        for (long i = istart; i < iend; i++) 
            sum += x[i] * x[i];
    }

    const double norm = sqrt(sum);
#pragma omp parallel num_threads(nthreads)
    {
        long istart, iend;
        my_block(N, omp_get_thread_num(), omp_get_num_threads(), &istart, &iend);
        for (long i = istart; i < iend; i++)  
            x[i] /= norm;
    }
    return norm;
}

static double coarse_maxnorm(double *x, long N, int nthreads)
{
    double mx = 0.0;
#pragma omp parallel num_threads(nthreads) reduction(max:mx)
    {
        long istart, iend;
        my_block(N, omp_get_thread_num(), omp_get_num_threads(), &istart, &iend);

        for (long i = istart; i < iend; i++)  
            mx = fmax(mx, fabs(x[i]));
    }

#pragma omp parallel num_threads(nthreads)
    {
        long istart, iend;
        my_block(N, omp_get_thread_num(), omp_get_num_threads(), &istart, &iend);
        for (long i = istart; i < iend; i++)
            x[i] /= mx;
    }
    return mx;
}

typedef double (*normalize_fn)(double *, long, int);

int main(int argc, char **argv)
{
    const long N = (argc > 1) ? atol(argv[1]) : 100000000L;  // 1e8
    const int threads[] = {1, 2, 4, 8, 16};
    const int nt = sizeof(threads) / sizeof(threads[0]);

    double *x = malloc(N * sizeof(double));
    if (!x) { fprintf(stderr, "malloc failed\n"); return 1; }

    const char *names[] = {"fine   2-norm ", "coarse 2-norm ",
                           "fine   max-norm", "coarse max-norm"};
    normalize_fn fns[] = {fine_2norm, coarse_2norm, fine_maxnorm, coarse_maxnorm};

    printf("N = %ld, cores available = %d\n\n", N, omp_get_num_procs());
    printf("%-16s %7s %12s %12s\n", "method", "threads", "norm", "time (s)");

    for (int m = 0; m < 4; m++)
    {
        for (int k = 0; k < nt; k++)
        {
            init_signal(x, N);

            const double start = omp_get_wtime();
            const double norm = fns[m](x, N, threads[k]);
            const double elapsed = omp_get_wtime() - start;

            printf("%-16s %7d %12.6e %12.6e\n",
                   names[m], threads[k], norm, elapsed);
        }
        printf("\n");
    }

    free(x);
    return 0;
}
