#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#ifdef _OPENMP
#  include <omp.h>
#endif

void usage(const char* prog_name)
{
   fprintf(stderr, "usage: %s <thread_count> <N>\n", prog_name);
   fprintf(stderr, "   thread_count should be positive, N should be >= 3\n");
   exit(1);
}

int main(int argc, char* argv[])
{
   if (argc != 3) { usage(argv[0]); }
   const int thread_count = strtol(argv[1], NULL, 10);
   const int N            = strtol(argv[2], NULL, 10);
   if (thread_count <= 0 || N < 3) { usage(argv[0]); }

   const int M = N - 2;   // blurred image is (N-2) x (N-2) 

   int* img  = malloc((size_t)N * N * sizeof(int));
   int* blur = malloc((size_t)M * M * sizeof(int));

   srand(time(NULL));
   for (int i = 0; i < N; i++)
      for (int j = 0; j < N; j++)
         img[i*N + j] = rand() % 256;

   const double time1 = omp_get_wtime();

#  pragma omp parallel for num_threads(thread_count)

   for (int i = 0; i < M; i++)
   {
      for (int j = 0; j < M; j++)
      {
         int sum = 0;
         
         for (int di = 0; di <= 1; di++)
            for (int dj = 0; dj <= 1; dj++)
               sum += img[(di + i) * N + (dj + j)];   

         blur[i*M + j] = sum / 9;                  
      }
   }

   const double time2 = omp_get_wtime();
   const double clock_time = time2 - time1;

   printf(" N = %d, threads = %d, walltime = %11.5e (sec)\n",
          N, thread_count, clock_time);

   free(img);
   free(blur);
   return 0;
}