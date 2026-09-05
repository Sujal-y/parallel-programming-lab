#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include <stdio.h>
#include <stdlib.h>

// 1. Kernel Definition
__global__ void vectorAdd(const int *a, const int *b, int *c, int n) {
    // Calculate the unique global index for this thread
    int tid = blockIdx.x * blockDim.x + threadIdx.x;
    
    // Boundary check: ensure we don't access memory past N
    if (tid < n) {
        c[tid] = a[tid] + b[tid];
    }
}

int main() {
    // 2. Define the Vector Length N
    // Change this value to whatever you like; the grid scales automatically.
    const int N = 7500; 
    const int size = N * sizeof(int);

    // 3. Allocate Host (CPU) Memory
    int *h_a = (int*)malloc(size);
    int *h_b = (int*)malloc(size);
    int *h_c = (int*)malloc(size);

    // Initialize data on the host
    for (int i = 0; i < N; i++) {
        h_a[i] = i;        // e.g., 0, 1, 2, ...
        h_b[i] = i * 2;    // e.g., 0, 2, 4, ...
    }

    // 4. Allocate Device (GPU) Memory
    int *d_a, *d_b, *d_c;
    cudaMalloc((void**)&d_a, size);
    cudaMalloc((void**)&d_b, size);
    cudaMalloc((void**)&d_c, size);

    // 5. Copy Data from Host to Device
    cudaMemcpy(d_a, h_a, size, cudaMemcpyHostToDevice);
    cudaMemcpy(d_b, h_b, size, cudaMemcpyHostToDevice);

    // 6. Define Constant Threads and Vary Blocks
    const int threadsPerBlock = 256; 
    
    // Ceiling division formula: calculates the exact number of blocks needed
    int blocksPerGrid = (N + threadsPerBlock - 1) / threadsPerBlock;

    printf("Vector Length (N): %d\n", N);
    printf("Threads Per Block (Constant): %d\n", threadsPerBlock);
    printf("Calculated Blocks Per Grid (Varying): %d\n\n", blocksPerGrid);

    // 7. Launch Kernel
    vectorAdd<<<blocksPerGrid, threadsPerBlock>>>(d_a, d_b, d_c, N);

    // 8. Copy Result Back to Host
    cudaMemcpy(h_c, d_c, size, cudaMemcpyDeviceToHost);

    // 9. Verify Results (Testing a few indices across the range)
    printf("Verification Samples:\n");
    printf("Index 0    : %d + %d = %d\n", h_a[0], h_b[0], h_c[0]);
    printf("Index 2000 : %d + %d = %d\n", h_a[2000], h_b[2000], h_c[2000]);
    printf("Index %d : %d + %d = %d\n", N-1, h_a[N-1], h_b[N-1], h_c[N-1]);

    // 10. Cleanup Memory
    cudaFree(d_a);
    cudaFree(d_b);
    cudaFree(d_c);
    free(h_a);
    free(h_b);
    free(h_c);

    return 0;
}

