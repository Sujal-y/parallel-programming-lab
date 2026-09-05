#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include <stdio.h>
#include <stdlib.h>

#define N 1000000  // N is number of threads


//__global__ says its a gpu kernel, called from cpu and executes in gpu
__global__ void vectorAdd_MultiBlock(int *a, int *b, int *c, int n) {
    // Calculates thread index
    int tid = blockIdx.x * blockDim.x + threadIdx.x;
    
    // makes sure the thread id shouldnt exceed N
    if (tid < n) {
    		//adds to matrix c
        c[tid] = a[tid] + b[tid];
    }
}

int main() {

		//for less big numbers
    //int size = N * sizeof(int);
    // for big numbers
		size_t size = (size_t)N * sizeof(int); 

    
    // Allocate host memory for a b c (System memory)
    int *host_a = (int*)malloc(size);
    int *host_b = (int*)malloc(size);
    int *host_c = (int*)malloc(size);

		//fills the array elements in host a and b
    for(int i = 0; i < N; i++) {
        host_a[i] = i;
        host_b[i] = i * 2;
    }

		//allocates device memory in gpu vram (gpu memory)
    int *device_a, *device_b, *device_c;
    cudaMalloc((void**)&device_a, size);
    cudaMalloc((void**)&device_b, size);
    cudaMalloc((void**)&device_c, size);

		//copies the data from System to Gpu memory
    cudaMemcpy(device_a, host_a, size, cudaMemcpyHostToDevice);
    cudaMemcpy(device_b, host_b, size, cudaMemcpyHostToDevice);

    // Define standard block size
    int threadsPerBlock = 256;
    // Ceiling division formula to compute necessary blocks: (N + block - 1) / block
    int blocksPerGrid = (N + threadsPerBlock - 1) / threadsPerBlock;

    // Launch Kernal configuration: Multi-block grid layout
    vectorAdd_MultiBlock<<<blocksPerGrid, threadsPerBlock>>>(device_a, device_b, device_c, N);

		//copies the result c into system/host memory
    cudaMemcpy(host_c, device_c, size, cudaMemcpyDeviceToHost);

    printf("Option B Result - Sample Index: %d + %d = %d\n", host_a[4500], host_b[4500], host_c[4500]);

		//frees device memory and host memory
    cudaFree(device_a); cudaFree(device_b); cudaFree(device_c);
    free(host_a); free(host_b); free(host_c);
    return 0;
}

