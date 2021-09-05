#include <stdlib.h>  
#include <stdio.h>   
#include <omp.h>     
#define ARRAY_SIZE 6    
#define NUM_THREADS 2    

int main (int argc, char *argv[]) 
{
	int * a;
	int * c;
        
    int n = ARRAY_SIZE;             
	int n_per_thread;                 
	int total_threads = NUM_THREADS;   
	int i;     
      
    a = (int *) malloc(sizeof(int)*n);
	c = (int *) malloc(sizeof(int)*n);

    for(i=0; i<n; i++) 
    {
        a[i] = i + 5;
    }
         
        
	omp_set_num_threads(total_threads);
	
	n_per_thread = n/total_threads;
	


	#pragma omp parallel 
    {
		int id, i, Nthrds, istart, iend;
		 id = omp_get_thread_num();
		 Nthrds = omp_get_num_threads();
		 istart = id*n/Nthrds;
		 iend = (id+1)*n/Nthrds;
		 if(id == Nthrds-1) iend = n;
		 for(i = istart; i<iend; i++)
		 {
		 	c[i] = 10+a[i];
		 }
		 
	}
		
		printf("i\ta[i]\t+\t1\t=\tc[i]\n");
        for(i=0; i<n; i++) 
        {
			printf("%d\t%d\t\t1\t\t%d\n", i, a[i],  c[i]);
        }
        free(a); 
        free(c);
	
	return 0;
}