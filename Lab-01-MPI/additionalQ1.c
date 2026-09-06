#include <mpi.h>
#include <stdio.h>

int reverse_digit(int num) {
    int remainder = 0, reversed = 0;

    while (num != 0) {
        remainder = num % 10;              // Extract the last digit
        reversed = reversed * 10 + remainder; // Append digit to reversed number
        num = num / 10;                    // Remove the last digit
    }

    return reversed;
}

int main(int argc, char *argv[]) {
    int rank, size;

    // Initialize the MPI environment
    MPI_Init(&argc, &argv);

    // Get the rank and size of the current process
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Input array
    int array[9] = {18, 523, 301, 1234, 2, 14, 108, 150, 1928};

    // Each process reverses one element
    int newNum = reverse_digit(array[rank]);

    // Gather the reversed numbers into the array on rank 0
    int output[9];

    //gather funtion is in later labs
    MPI_Gather(&newNum, 1, MPI_INT,
               output, 1, MPI_INT,
               0, MPI_COMM_WORLD);

    // Process 0 prints the output array
    if (rank == 0) {
        printf("Output: ");

        for (int i = 0; i < 9; i++) {
            printf("%d ", output[i]);
        }

        printf("\n");
    }

    // Finalize MPI environment
    MPI_Finalize();

    return 0;
}