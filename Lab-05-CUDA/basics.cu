#include<stdio.h>
#include<cuda_runtime.h>

__global__ void hello(){
	printf("hello from CUDA GPU!!\n");
}

int main(){

	hello<<<1,1>>>();
	cudaDeviceSynchronize();
	return 0;

}
