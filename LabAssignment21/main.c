#include <stdlib.h>
#include <stdio.h>
#include <mpi.h>

int main(int argc, char* argv[])
{
   // Setup MPI code
   int comm_sz, my_rank;
   MPI_Init(NULL,NULL);
   MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
   MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

   // need at least 2 processes for a ring
   if (comm_sz < 2) {
    fprintf(stderr,"usage: mpirun -np <P> ./main.exe  (P >= 2)\n");
   }

   const int next = (my_rank+1) % comm_sz;
   const int prev = (my_rank - 1 + comm_sz) % comm_sz;
   int token;

   if (my_rank == 0)
   {
        token = 1000;
        MPI_Send(&token, 1, MPI_INT, next, 0, MPI_COMM_WORLD);
        printf("Rank %i sent token %i to Rank %i\n", my_rank, token, next);
        fflush(stdout);

        MPI_Recv(&token, 1, MPI_INT, prev, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("Rank %i received token %i from Rank %i\n", my_rank, token, prev);
        printf("\n Final token = %i (expected %i)\n", token, 1000 + (comm_sz-1));
        fflush(stdout);

   }
   else
   {
        MPI_Recv(&token, 1, MPI_INT, prev, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("Rank %i received token %i from Rank %i\n", my_rank, token, prev);
        fflush(stdout);

        token = token + 1;

        MPI_Send(&token, 1, MPI_INT, next, 0, MPI_COMM_WORLD);
        printf("Rank %i sent token %i to Rank %i\n", my_rank, token, next);
        fflush(stdout);
   }

   // End program
   MPI_Finalize();
   return 0;
}