#include <mpi.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    int rank, size, x;
    
    MPI_Init(&argc, &argv); 
    
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size); 
    
    MPI_Status status; 
    
    if (rank == 0) {
        printf("Enter the value in master Process:\n"); 
        
        if (scanf("%d", &x) != 1) {
            x = 0; 
        }
        
        MPI_Send(&x, 1, MPI_INT, 1, 1, MPI_COMM_WORLD);
        
        printf("I have sent %d from Process 0\n", x); 
        fflush(stdout);
    } 
    else if (rank == 1) { // 7. Added condition to ensure only Process 1 tries to receive
        MPI_Recv(&x, 1, MPI_INT, 0, 1, MPI_COMM_WORLD, &status);
        fprintf(stdout, "I have received %d in process 1\n", x);
        fflush(stdout);
    }
    
    MPI_Finalize();
    return 0;
}
