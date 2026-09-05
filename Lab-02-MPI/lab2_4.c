#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[]) {
    int rank, size;
    int value;
    MPI_Status status;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (size < 2) {
        if (rank == 0) {
            printf("Run with at least 2 processes.\n");
        }
        MPI_Finalize();
        return 0;
    }

    if (rank == 0) {
        printf("Root process (Rank 0): Enter an integer value: ");
        fflush(stdout);
        scanf("%d", &value);

        printf("Process 0 initial value: %d\n", value);
        value += 1;
        printf("Process 0 sends incremented value %d to Process 1\n", value);
        MPI_Send(&value, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);

        // Receive final value from the last process (size - 1)
        MPI_Recv(&value, 1, MPI_INT, size - 1, 0, MPI_COMM_WORLD, &status);
        printf("Process 0 received final value %d from Process %d\n", value, size - 1);
    } else {
        // Receive from previous process (rank - 1)
        MPI_Recv(&value, 1, MPI_INT, rank - 1, 0, MPI_COMM_WORLD, &status);
        printf("Process %d received value %d from Process %d\n", rank, value, rank - 1);

        value += 1; // Increment the value

        // Send to next process (wraps around to 0 if last process)
        int next_rank = (rank + 1) % size;
        printf("Process %d sends incremented value %d to Process %d\n", rank, value, next_rank);
        MPI_Send(&value, 1, MPI_INT, next_rank, 0, MPI_COMM_WORLD);
    }

    MPI_Finalize();
    return 0;
}