#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

// Function to handle MPI errors and print error class/string details
void handle_mpi_error(int err_code) {
    if (err_code != MPI_SUCCESS) {
        char err_string[MPI_MAX_ERROR_STRING];
        int err_len, err_class;
        MPI_Error_class(err_code, &err_class);
        MPI_Error_string(err_code, err_string, &err_len);
        printf("[Error Handler] Code: %d, Class: %d, Message: %s\n", err_code, err_class, err_string);
    }
}

int main(int argc, char *argv[]) {
    int rank, size, err;
    long long fact = 1, scan_sum = 0;

    MPI_Init(&argc, &argv);
    // Set custom error handler to return errors instead of exiting immediately
    MPI_Errhandler_set(MPI_COMM_WORLD, MPI_ERRORS_RETURN);

    err = MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    handle_mpi_error(err);

    err = MPI_Comm_size(MPI_COMM_WORLD, &size);
    handle_mpi_error(err);

    // Each process calculates factorial of (rank + 1)
    for (int i = 1; i <= rank + 1; i++) {
        fact *= i;
    }

    // MPI_Scan computes prefix sum: each process get the sum from previous one
    err = MPI_Scan(&fact, &scan_sum, 1, MPI_LONG_LONG, MPI_SUM, MPI_COMM_WORLD);
    handle_mpi_error(err);

    printf("Process %d (computes %d! = %lld): Prefix Sum = %lld\n", rank, rank + 1, fact, scan_sum);

    // The last process final will calculate the total sum of all factorials
    if (rank == size - 1) {
        printf("Total Sum of 1! + 2! + ... + %d! = %lld\n", size, scan_sum);
    }

    MPI_Finalize();
    return 0;
}
