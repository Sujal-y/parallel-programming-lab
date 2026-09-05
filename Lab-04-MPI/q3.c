#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[]) {
    int rank, size;
    int mat[4][4], row[4], res_row[4], output_mat[4][4];

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0) {
        printf("Enter 4x4 matrix elements:\n");
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                scanf("%d", &mat[i][j]);
            }
        }
    }

    // Scatter 1 row (4 elements) to each process
    MPI_Scatter(mat, 4, MPI_INT, row, 4, MPI_INT, 0, MPI_COMM_WORLD);

    // Cumulative sum across rows using MPI_Scan
    // Output row i = sum of (row 0 + row 1 + ... + row i) element-wise
    MPI_Scan(row, res_row, 4, MPI_INT, MPI_SUM, MPI_COMM_WORLD);

    // Gather all updated rows back to root
    MPI_Gather(res_row, 4, MPI_INT, output_mat, 4, MPI_INT, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        printf("\nTransformed Output Matrix:\n");
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                printf("%d\t", output_mat[i][j]);
            }
            printf("\n");
        }
    }

    MPI_Finalize();
    return 0;
}
