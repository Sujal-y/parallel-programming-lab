#include <mpi.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    int rank, size;

    // Initialize the MPI environment
    MPI_Init(&argc, &argv);

    // Get the rank and size of the current process
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // if rank is 0 or even find prime from 0 to 49
    if(rank%2 == 0){
        for (int i = 0; i < 50; i++) {
        int prime = 1;
        if (i < 2) {
            prime = 0;
        }
        for (int j = 2; j <= i / 2; j++) {
            if (i % j == 0) {
                prime = 0;
                break;
            }
        }
        if (prime) {
            printf("Rank %d: %d is prime\n", rank, i);
        }
        }
    }
    // if its 1 or odd find prime from 50 to 100
    else{
        for (int i = 50; i <= 100; i++) {
        int prime = 1;

        for (int j = 2; j <= i / 2; j++) {
            if (i % j == 0) {
                prime = 0;
                break;
            }
        }

        if (prime) {
            printf("Rank %d: %d is prime\n", rank, i);
        }
        
        }
    }

    // Finalize MPI environment
    MPI_Finalize();

    return 0;
}