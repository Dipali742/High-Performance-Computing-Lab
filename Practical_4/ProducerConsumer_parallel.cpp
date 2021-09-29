#include <stdio.h>
#include <stdlib.h>
#include<omp.h>
#include <time.h>

int full = 0;
int empty = 5, x = 0;

omp_lock_t mutex;


void producer()
{
	omp_set_lock(&mutex);
	if(empty == 0)
	{
		printf("Thread Number : %d -> Buffer is full!\n",omp_get_thread_num());
		omp_unset_lock(&mutex);
		return;
	}
	++full;

	--empty;

	x++;
	printf("Thread Number : %d -> Producer produces " "item %d\n",omp_get_thread_num(), x);

	omp_unset_lock(&mutex);
}

void consumer()
{
	omp_set_lock(&mutex);
	if(full == 0)
	{
		printf("Thread Number : %d -> Buffer is empty!\n",omp_get_thread_num());
		x=0;
		omp_unset_lock(&mutex);
		return;
	}

	--full;

	++empty;
	printf("Thread Number : %d -> Consumer consumes " "item %d\n",omp_get_thread_num(), x);
	x--;

	omp_unset_lock(&mutex);
}

// Driver Code
int main()
{
	clock_t start, end;
    start = clock();
    printf("Buffer size : %d\n\n",empty);
	omp_init_lock(&mutex);
	#pragma omp parallel 
    {
    	// printf("");
    	// printf("");
    	producer();

    	consumer();
    }
    
  	omp_destroy_lock(&mutex);

  	end = clock();
    double time_taken = (double)(end - start) / (double)(CLOCKS_PER_SEC);
    printf("\nTime taken : %0.4f seconds\n",time_taken);
  
}