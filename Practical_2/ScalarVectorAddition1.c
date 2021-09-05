#include <stdlib.h>  
#include <stdio.h>   
#include <omp.h>     


//firstprivate - shared - private
int main (int argc, char *argv[]) 
{
	int * a;
	int * c; 
        
    int n = 8;             
	int n_per_thread;                 
	int total_threads = 4;   
	int i;     
      
    a = (int *) malloc(sizeof(int)*n);
	c = (int *) malloc(sizeof(int)*n);

    for(i=0; i<n; i++) 
    {
        a[i] = i;
    }
     
        
	omp_set_num_threads(total_threads);
	
	n_per_thread = n/total_threads;
	
	printf("\nTotal number of threads : %d\n",total_threads);
    printf("Chunk size : %d\n\n",n_per_thread);

	#pragma omp parallel for firstprivate(a) shared(c) private(i) 
        for(i=0; i<n; i++) 
        {
			c[i] = a[i]+1;
			printf("Thread %d works on element%d\n", omp_get_thread_num(), i);
        }
	
	printf("\nScalar Vector Addition :\n");
	printf("i\ta[i]\t+\t1\t=\tc[i]\n");
    for(i=0; i<n; i++) 
    {
		printf("%d\t%d\t\t%d\t\t%d\n", i, a[i], 1, c[i]);
    }
	
    free(a);  
    free(c);
	
	return 0;
}