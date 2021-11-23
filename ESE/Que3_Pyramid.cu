%%writefile Que3_Pyramid.cu

#include<stdio.h>
#include<iostream>
using namespace std;

__global__ void Pyramid(int *gpu_num,long int *gpu_res)
{
  int space;
  for(int i = 1, k = 0; i <= *gpu_num; ++i, k = 0)
    {
        for(space = 1; space <= *gpu_num-i; ++space)
        {
            printf("  ");
        }

        while(k != 2*i-1)
        {
            
            printf("* ");
            ++k;
        }
        printf("\n");
    } 
}

int main()
{
  int Number=6;  
  int *dev_number;
  long int *res, result; 
  
  printf("\nHeight of Pyramid : %d\n",Number);
  
  
  cudaMalloc((void**)&dev_number,sizeof(int));
  cudaMalloc((void**)&res,sizeof(long int));
  
  cudaMemcpy(dev_number,&Number,sizeof(int),cudaMemcpyHostToDevice);
 
  Pyramid<<<1,1>>>(dev_number,res);

  cudaMemcpy(&result,res,sizeof(long int),cudaMemcpyDeviceToHost);

 
  return 0; 
}