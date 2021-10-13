#include <stdio.h>
#include <mpi.h>
int main(int argc, char **argv)
{
    int rank, size;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    int tag = 100;
    MPI_Request sendReqs[3];
    MPI_Status statuses[3];

    if (rank == 0) 
    {
        int message = 10;
        MPI_Isend(&message, 1, MPI_INT, 1, tag, MPI_COMM_WORLD, &sendReqs[0]);
        MPI_Isend(&message, 1, MPI_INT, 2, tag, MPI_COMM_WORLD, &sendReqs[1]);
        MPI_Isend(&message, 1, MPI_INT, 3, tag, MPI_COMM_WORLD, &sendReqs[2]);
        MPI_Waitall(3, sendReqs, statuses);
    }
    else  
    {
        int rmessage;
        MPI_Recv(&rmessage, 1, MPI_INT, 0, tag, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        MPI_Irecv(&rmessage, 1, MPI_INT, 0, tag, MPI_COMM_WORLD, &sendReqs[1]);
        printf("Process %d received message %d with tag %d from process %d\n", rank, rmessage,tag,0);
    }

    MPI_Finalize();
    return 0;
 }