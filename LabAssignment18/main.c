#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#ifdef _OPENMP
#  include <omp.h>
#endif

const double S0    = 100.0;   /* asset price today   */
const double K     = 100.0;   /* strike              */
const double r     = 0.05;    /* risk-free rate      */
const double sigma = 0.2;     /* volatility          */
const double T     = 1.0;     /* time to maturity    */

void   usage(const char *prog_name);
double func(const double S);                      
double CompSimpson(const double a, const double b,
                   const int N, const int thread_count);
double BlackScholesCall(void);

int main(int argc, char *argv[])
{
   if (argc != 3) { usage(argv[0]); }
   const int thread_count = strtol(argv[1], NULL, 10);
   const int N            = strtol(argv[2], NULL, 10);

   if (thread_count < 1 || N < 2 || N % 2 != 0) { usage(argv[0]); }

   const double a = K;          
   const double b = 5*S0;          

   const double time1 = omp_get_wtime();
   const double C_simp = exp(-1*r*T) * CompSimpson(a, b, N, thread_count);   
   const double time2 = omp_get_wtime();

   const double C_bs = BlackScholesCall();
   const double err  = fabs(C_simp - C_bs);

   printf("\n N = %i, threads = %i\n", N, thread_count);
   printf(" Simpson C       = %23.15e\n", C_simp);
   printf(" Black-Scholes C = %23.15e\n", C_bs);
   printf(" err = %12.5e, time = %12.5e\n\n", err, time2 - time1);
   return 0;
}

/* Composite Simpson:
 *   I ~ (h/3) [ f(x_0) + 4 f(x_1) + 2 f(x_2) + 4 f(x_3) + ... + 4 f(x_{N-1}) + f(x_N) ]
 */
double CompSimpson(const double a, const double b,
                   const int N, const int thread_count)
{
   const double h = (b - a)/N;

   double S = func(a) + func(b);                

#  pragma omp parallel for num_threads(thread_count) \
   reduction(+: S)
   for (int i = 1; i < N; i++)
   {
      const double w = 2 + 2*(i % 2);       
      S += w * func(a + i*h);         
   }

   return (h/3)*S;                   
}

/*(S - K) * p(S), with p(S) the lognormal density from the slide */
double func(const double S)
{
   const double mu = log(S0) + (r - pow(sigma, 2)/2)*T;         
   const double z  = log(S) - mu;
   const double p  = (1/(S*sigma*sqrt(2*M_PI*T)))*exp((-1*pow(z,2))/(2*sigma*sigma*T));        
   return (S - K) * p;
}

/* Black-Scholes:  C = S0 N(d1) - K e^{-rT} N(d2)
 *   d1 = [ ln(S0/K) + (r + sigma^2/2) T ] / (sigma sqrt(T)),   d2 = d1 - sigma sqrt(T)
 *   N(x) = standard normal CDF = 0.5 * erfc(-x / sqrt(2))     (erfc is in math.h)
 */
double BlackScholesCall(void)
{
   const double d1 = (log(S0/K) + (r + (sigma*sigma)/2)*T)/(sigma*sqrt(T));
   const double d2 = d1 - (sigma * sqrt(T));
   const double N1 = 0.5 * erfc((-1*d1)/sqrt(2));
   const double N2 = 0.5 * erfc((-1*d2)/sqrt(2));
   return S0 * N1 - K * exp(-r * T) * N2;
}

void usage(const char *prog_name)
{
   fprintf(stderr, "usage: %s <num_threads> <num_intervals>\n", prog_name);
   fprintf(stderr, "   num_threads should be positive\n");
   fprintf(stderr, "   num_intervals should be positive and even\n");
   exit(1);
}