#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
  

int temp[1000];
  
int main(int argc, char* argv[])
{
    int n=14;
    
    int pid, np,elements_per_process,n_elements_recieved;
    
    int a[14]={1,1,2,2,1,1,2,2,1,1,2,2,1,3};
    
    MPI_Status status;
   
    MPI_Init(&argc, &argv);
  
    MPI_Comm_rank(MPI_COMM_WORLD, &pid);
    MPI_Comm_size(MPI_COMM_WORLD, &np);
  
    if (pid == 0) 
    {
        
        int index, i;
        elements_per_process = n / np;
  
        if (np > 1) 
        {
            for (i = 1; i < np - 1; i++) 
            {
                index = i * elements_per_process;
  
                MPI_Send(&elements_per_process,1, MPI_INT, i, 0,MPI_COMM_WORLD);
                MPI_Send(&a[index],elements_per_process,MPI_INT, i, 0,MPI_COMM_WORLD);
            }
  
            // last process adds remaining elements
            index = i * elements_per_process;
            int elements_left = n - index;
  
            MPI_Send(&elements_left,1, MPI_INT,i, 0,MPI_COMM_WORLD);
            MPI_Send(&a[index],elements_left,MPI_INT, i, 0,MPI_COMM_WORLD);
        }
  
        int product = 1;
        for (i = 0; i < elements_per_process; i++)
            product *= a[i];
        printf("Partial product from process P%d (root) : %d \n",pid,product);
        // collects partial products from other processes
        int tmp;
        for (i = 1; i < np; i++) {
            MPI_Recv(&tmp, 1, MPI_INT,MPI_ANY_SOURCE, 0,MPI_COMM_WORLD,&status);
            int sender = status.MPI_SOURCE;
  
            product *= tmp;
        }
  
        // prints the final product of array
        printf("Product of array elements is : %d\n", product);
    }

    else 
    {
        MPI_Recv(&n_elements_recieved,1, MPI_INT, 0, 0, MPI_COMM_WORLD,&status);
  
        MPI_Recv(&temp, n_elements_recieved,MPI_INT, 0, 0,MPI_COMM_WORLD,&status);
  
        int partial_product = 1;
        for (int i = 0; i < n_elements_recieved; i++)
            partial_product *= temp[i];
        printf("Partial product from process P%d : %d \n",pid,partial_product);
        
        MPI_Send(&partial_product, 1, MPI_INT,0, 0, MPI_COMM_WORLD);
    }
  
    MPI_Finalize();
   
    return 0;
}