#include "mpi.h"
#include <stdio.h>

int main(int argc, char *argv[])  
{
      int numtasks, rank, next, prev, buf[2], tag1=1, tag2=2,tag=0,rc,count;
      // MPI_Request reqs[4];   // required variable for non-blocking calls
      // MPI_Status stats[4];   // required variable for Waitall routine
      MPI_Status Stat;
      // MPI_Init(&argc,&argv);
      // MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
      // MPI_Comm_rank(MPI_COMM_WORLD, &rank);

      // determine left and right neighbors
      prev = rank-1;
      next = rank+1;
    //   if (rank == 0)  {
    //         prev = numtasks - 1;

    //   }
    //   if (rank == (numtasks - 1)) {
    //       next = 0;  
    //   } 


    //   MPI_Recv(&buf[0], 1, MPI_INT, prev, tag1, MPI_COMM_WORLD,&Stat);
    //   MPI_Recv(&buf[1], 1, MPI_INT, next, tag2, MPI_COMM_WORLD,&Stat);
    //    MPI_Send(&rank, 1, MPI_INT, prev, tag1, MPI_COMM_WORLD);
    // MPI_Send(&rank, 1, MPI_INT, next, tag1, MPI_COMM_WORLD);


      char inmsg, outmsg='x';
      // MPI_Status Stat;

      MPI_Init(&argc,&argv);
      MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
      MPI_Comm_rank(MPI_COMM_WORLD, &rank);

      if (rank == 0) {
        prev = numtasks - 1;
        rc = MPI_Send(&rank, 1, MPI_INT, next, tag, MPI_COMM_WORLD);
        rc = MPI_Recv(&buf[1], 1, MPI_INT, next, tag, MPI_COMM_WORLD,&Stat);
        } 

      else if (rank == 1) {
       next = 0;
        rc = MPI_Recv(&buf[0], 1, MPI_INT, prev, tag, MPI_COMM_WORLD,&Stat);
        rc = MPI_Send(&rank, 1, MPI_INT, prev, tag, MPI_COMM_WORLD);
        }

      rc = MPI_Get_count(&Stat, MPI_INT, &count);
      printf("Task %d: Received %d char(s) from task %d with tag %d \n",
             rank, count, Stat.MPI_SOURCE, Stat.MPI_TAG);


      MPI_Finalize();
}