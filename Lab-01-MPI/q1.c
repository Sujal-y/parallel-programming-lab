#include <mpi.h>
#include <stdio.h>
#include <math.h>

int main(int argc, char *argv[]) {
    int rank, size;
    
    // Define the integer constant 'x'
    const int x = 2; 

    // Initialize MPI
    MPI_Init(&argc, &argv);

    // Get the rank and size of the current process
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Calculate pow(x, rank)
    // pow() returns a double, so we cast it to double (or int)
    double result = pow(x, rank);

    // Print the result from each process
    printf("Process Rank %d: %d^%d = %.0f\n", rank, x, rank, result);

    // Finalize MPI environment
    MPI_Finalize();
    return 0;
}
