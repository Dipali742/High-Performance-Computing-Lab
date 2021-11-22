%%writefile GlobalMemory.cu

#include<stdio.h>
#include<cuda.h>

__global__ void arradd(int *x,int *y,int *z){
	int index=blockIdx.x;
  z[index]=x[index]+y[index];
  printf("\nElements at index %d : %d + %d = %d",index,x[index],y[index],z[index]);
}

int main(){

	int n=3;
	int a[3]={5,8,9};
	int b[3]={10,11,12};
	int c[n];
	int *x,*y,*z;
	int i;
	
	cudaMalloc((void**)&x,n*sizeof(int));
	cudaMalloc((void**)&y,n*sizeof(int));
	cudaMalloc((void**)&z,n*sizeof(int));
	cudaMemcpy(x,a,n*sizeof(int),cudaMemcpyHostToDevice);
	cudaMemcpy(y,b,n*sizeof(int),cudaMemcpyHostToDevice);
  arradd<<<n,1>>>(x,y,z);
   
    cudaMemcpy(c,z,n*sizeof(int),cudaMemcpyDeviceToHost);
    printf("\nResultant vector:");
    for(i=0;i<n;i++){
    	printf("%d ",c[i]);
    }
    printf("\n");
    cudaFree(x);
    cudaFree(y);
    cudaFree(z);
    return 0;

}