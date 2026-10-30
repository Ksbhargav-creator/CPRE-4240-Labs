#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#ifdef _OPENMP
    #include <omp.h>
#endif

// main function
int main(int argc, char* argv[]){
    void usage(const char* prog_name);
    double AdaptiveInt(double x, const double a, const double b, const double TOL);

    if (argc != 3){ usage(argv[0]); }
    const int thread_count = strtol(argv[1], NULL, 10);
    const double TOL = strtod(argv[2], NULL);
    if (thread_count < 1 || TOL<5.0e-16) {usage(argv[0]);}

    const int N = 501;
    const double h = 50.0/(N-1);
    const double pi = 4.0*atan(1.0);
    const double one_over_pi = 1.0/pi;

    double* xvals = (double*) malloc(N*sizeof(double));
    double* J     = (double*) malloc(N*sizeof(double));

    // each x is an independent integral -> split the x-loop across threads
#   pragma omp parallel for num_threads(thread_count) schedule(dynamic)
    for (int i=0; i<N; i++)
    {
        xvals[i] = i*h;
        J[i] = one_over_pi*AdaptiveInt(xvals[i], 0.0, pi, TOL);
    }

    // write results serially so lines stay in order
    FILE* file = fopen("bessel.data", "w");
    for (int i=0; i<N; i++)
    { fprintf(file, "%24.15e %24.15e\n", xvals[i], J[i]); }
    fclose(file);

    printf("\n");
    printf(" thread_count = %i\n", thread_count);
    printf("          TOL = %24.15e\n", TOL);
    printf("            N = %i\n", N);
    printf("     J0(0)    = %24.15e\n", J[0]);
    printf("\n");

    free(xvals);
    free(J);
    return 0;
}

double Q(double x, const double a, const double b)
{
    double f(double x, double thetha);
    const double one_sixth = 1.666666666666667e-01;
    const double c = 0.5*(a+b);
    return one_sixth *(b-a)*(f(x,a)+4.0*f(x,c)+f(x,b));
}


double AdaptiveInt(double x,const double a, const double b, const double TOL){
    double Q(double x,const double a, const double b);

    double Qab = Q(x,a,b);
    const double c = 0.5*(a+b);
    double Qac = Q(x,a,c);
    double Qcb = Q(x,c,b);

    const double one_over_fifteen = 6.666666666666667e-02;
    const double error_est = one_over_fifteen*fabs(Qac + Qcb - Qab);

    if (error_est < TOL){ return Qac + Qcb; }
    else{
        Qac = AdaptiveInt(x,a,c,0.5*TOL);
        Qcb = AdaptiveInt(x,c,b,0.5*TOL);
        return Qac + Qcb;
    }
}

/* J0(x) = 1/pi(integral(u-limit:pi, l-lim: 0, integrand: cos(xsin(thetha)d(thetha)))*/
double f(double x, double thetha){
    return cos(x*sin(thetha));
}

// usage function
void usage(const char *prog_name)
{
   fprintf(stderr, "usage: %s <num_threads> <TOL>\n", prog_name);
   fprintf(stderr, "   num_threads and TOL should be positive\n");
   exit(1);
}
