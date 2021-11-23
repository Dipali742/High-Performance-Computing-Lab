//Que 1 - Implement bubble sort using OpenMP.

#include <omp.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <time.h>

int main()
{
    clock_t start, end;
    start = clock();
    int total_threads = 8;
    int n,*arr;
    printf("\nEnter n value : ");
    scanf("%d",&n);

    arr = (int*) malloc(n * sizeof(int));
 
    printf("\nEnter array elements : \n");
    for(int i = 0; i < n; ++i)
    {
        scanf("%d",&arr[i]);
    }   


    omp_set_num_threads(total_threads);
    
    int n_per_thread = n/total_threads;
    
    printf("\nTotal number of threads : %d\n",total_threads);
    printf("Chunk size : %d\n\n",n_per_thread);

    int  third_var, reduction_variable;
   
    
    
    reduction_variable = 1;
    int nr = 0;
    while(reduction_variable)
    {
        #pragma omp parallel private(third_var)
        {
                nr++;
                reduction_variable = 0;
                #pragma omp for reduction(+:reduction_variable)
                for(int i = 0; i < n - 1; i = i + 2)
                {
                        if(arr[i] > arr[i+1] )
                        {
                                third_var = arr[i];
                                arr[i] = arr[i+1];
                                arr[i+1] = third_var;
                                ++reduction_variable;
                        }
                }
                #pragma omp for reduction(+:reduction_variable)
                for(int i = 1; i < n - 1; i = i + 2)
                {
                        if( arr[i] > arr[i+1] )
                        {
                                third_var = arr[i];
                                arr[i] = arr[i+1];
                                arr[i+1] = third_var;
                                ++reduction_variable;
                        }
                }
        }
    }

    printf("Sorted array :\n");
    for(int i=0;i<n;i++)
    {
        printf("%d ",arr[i]);
    }

    end = clock();
    double time_taken = (double)(end - start) / (double)(CLOCKS_PER_SEC);
    printf("\n\nTime taken : %0.4f seconds\n",time_taken);
  
    return 0;
}