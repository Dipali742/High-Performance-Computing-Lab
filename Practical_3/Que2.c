#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//(1xn) * (nxm) = (1xm)  
//size of resultant matrix - 1xm

#define N 10 /* number of rows in matrix A */
#define M 500 /* number of columns in matrix B */


#define threads_cnt 32

int main (int argc, char *argv[])
{
    clock_t start, end;
  
    /* Recording the starting clock tick.*/
    start = clock();

    int tid, nthreads, i, j, k;

    //1d vector - a
    //2d matrix - b
    //resultant 1d vector - c
    int a[N], b[N][M], c[M];
    
    omp_set_num_threads(threads_cnt);

    printf("\nNumber of Threads : %d\n\n",threads_cnt);
    #pragma omp parallel shared(a,b,c,nthreads) private(tid,i,j,k)
    {
        tid = omp_get_thread_num();
        if (tid == 0)
        {
            nthreads = omp_get_num_threads();
        }

        /*** Initialize matrices ***/
        #pragma omp for
            for (i=0; i<N; i++)
               a[i] = i;
        
        #pragma omp for
            for (i=0; i<N; i++)
                for (j=0; j<M; j++)
                    b[i][j]= i*j;
         
        #pragma omp for
            for (i=0; i<M; i++)
                c[i]= 0;

        #pragma omp for
            for (i=0; i<M; i++)
            {
                //printf("Thread=%d did row=%d\n",tid,i);
                for(j=0; j<N; j++)
                {
                    c[i] += a[j] * b[j][i];
                }
            }
     }

    printf("\n1D Vector :\n");
    for (i=0; i<N; i++)
    {
        printf("%d ", a[i]);
    }
    printf("\n");
    
    printf("\n2D matrix:\n");
    for (i=0; i<N; i++)
    {
        for (j=0; j<M; j++)
            printf("%d ", b[i][j]);
        printf("\n");
    }
    printf("\n");

    printf("Resultant vector:\n");
    for (i=0; i<M; i++)
    {
        printf("%d ", c[i]);
    }
    printf("\n");
    
    end = clock();
    double time_taken = (double)(end - start) / (double)(CLOCKS_PER_SEC);
    printf("\nTime taken : %0.4f seconds\n",time_taken);
  
    return(0);
}