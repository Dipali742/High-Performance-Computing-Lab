//Que 2 - Implement MPI program using all to all broadcast.

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <mpi.h>

float *fillArray(int num_elements) 
{
    float *arr = (float *)malloc(sizeof(float) * num_elements);
    
    int i;
    for (i = 0; i < num_elements; i++) 
    {
      arr[i] = i+2;
    }
    return arr;
}

float calculate_avg(float *array, int num_elements) 
{
  float sum = 0.f;
  int i;
  for (i = 0; i < num_elements; i++) 
  {
    sum += array[i];
  }
  return sum / num_elements;
}

int main(int argc, char** argv) 
{
  

  int num_elements_per_proc = atoi(argv[1]);
  srand(time(NULL));

  MPI_Init(NULL, NULL);

  int world_rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
  int world_size;
  MPI_Comm_size(MPI_COMM_WORLD, &world_size);

  
  float *arr = NULL;
  if (world_rank == 0) 
  {
    arr = fillArray(num_elements_per_proc * world_size);
  }

  
  float *sub_arr = (float *)malloc(sizeof(float) * num_elements_per_proc);
 

  MPI_Scatter(arr, num_elements_per_proc, MPI_FLOAT, sub_arr,
              num_elements_per_proc, MPI_FLOAT, 0, MPI_COMM_WORLD);

  float sub_avg = calculate_avg(sub_arr, num_elements_per_proc);

  float *sub_avgs = (float *)malloc(sizeof(float) * world_size);
  
  MPI_Allgather(&sub_avg, 1, MPI_FLOAT, sub_avgs, 1, MPI_FLOAT, MPI_COMM_WORLD);

  float avg = calculate_avg(sub_avgs, world_size);
  printf("Average of all elements from process %d is %f\n", world_rank, avg);

  if (world_rank == 0) 
  {
    free(arr);
  }
  free(sub_avgs);
  free(sub_arr);

  MPI_Barrier(MPI_COMM_WORLD);
  MPI_Finalize();
}