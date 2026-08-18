#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
    int rank, size;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int received_val;
    int result;

    if (rank == 0) {
        int* array = (int*)malloc(size * sizeof(int));
        
        printf("Root process (Rank 0) detected %d total processes.\n", size);
        printf("Enter %d elements for the array:\n", size);
        for (int i = 0; i < size; i++) {
            scanf("%d", &array[i]);
        }

        // Calculate total buffer size 
        int buffer_size = size * (sizeof(int) + MPI_BSEND_OVERHEAD);
        void* buffer = malloc(buffer_size);

        MPI_Buffer_attach(buffer, buffer_size);

        for (int i = 0; i < size; i++) {
            MPI_Bsend(&array[i], 1, MPI_INT, i, 0, MPI_COMM_WORLD);
        }

        free(array);
    }

    MPI_Recv(&received_val, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

    if (rank % 2 == 0) {
        result = received_val * received_val;
        printf("Process %d (EVEN): Received %d, Square = %d\n", rank, received_val, result);
    } else {
        result = received_val * received_val * received_val;
        printf("Process %d (ODD) : Received %d, Cube = %d\n", rank, received_val, result);
    }

    if (rank == 0) {
        int detached_buffer_size;
        void* detached_buffer;
        
        MPI_Buffer_detach(&detached_buffer, &detached_buffer_size);
        free(detached_buffer);
    }

    MPI_Finalize();
    return 0;
}
