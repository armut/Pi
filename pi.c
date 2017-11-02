#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <time.h>
#include <math.h>

int main(int argc, char** argv)
{
   int pid;
   int nop;
   const int TOTAL_NUMBER_OF_POINTS = atoi(argv[1]);
   int inside_points = 0;
   int current_total = 0;
   int gl_inside_points;
   int gl_current_total;
   double pi;
   double time_measurement;

   MPI_Init(&argc, &argv);
   MPI_Barrier(MPI_COMM_WORLD);
   time_measurement = - MPI_Wtime();
   MPI_Comm_rank(MPI_COMM_WORLD, &pid);
   MPI_Comm_size(MPI_COMM_WORLD, &nop);

   srand(pid);

   for(int i = pid; i < TOTAL_NUMBER_OF_POINTS; i += nop)
   {
      double random_x = (double)rand() / (double)RAND_MAX;
      double random_y = (double)rand() / (double)RAND_MAX;
      double magnitude = random_x * random_x + random_y * random_y;

      if(magnitude <= 1)
         inside_points++;
      current_total++;
   }

   MPI_Reduce(&inside_points, &gl_inside_points, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
   MPI_Reduce(&current_total, &gl_current_total, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

   time_measurement += MPI_Wtime();
   MPI_Finalize();

   if(gl_current_total == TOTAL_NUMBER_OF_POINTS)
   {
      pi = 4 * (double)gl_inside_points / (double)gl_current_total;
      printf("%d,%d,%f,%f\n", nop, TOTAL_NUMBER_OF_POINTS, time_measurement, pi);
   }

   return 0;
}

