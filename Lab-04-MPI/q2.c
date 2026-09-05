#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[]) {
    int rank, size;
    int matrix[3][3], row[3], target;
    int local_count = 0, total_count = 0;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0) {
        printf("Enter elements of 3x3 matrix:\n");
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                scanf("%d", &matrix[i][j]);
            }
        }
        printf("Enter element to search: ");
        scanf("%d", &target);
    }

    // Broadcast the search key 
    MPI_Bcast(&target, 1, MPI_INT, 0, MPI_COMM_WORLD);

    // Scatter 3 elements to each of the 3 processes
    MPI_Scatter(matrix, 3, MPI_INT, row, 3, MPI_INT, 0, MPI_COMM_WORLD);

    // Count the number of occurrences of target in the assigned row
    for (int j = 0; j < 3; j++) {
        if (row[j] == target) local_count++;
    }

    // Reduce all local counts into a single total at root using MPI_SUM
    MPI_Reduce(&local_count, &total_count, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        printf("Total occurrences of element %d in the matrix: %d\n", target, total_count);
    }

    MPI_Finalize();
    return 0;
}
