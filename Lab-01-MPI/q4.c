#include <mpi.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
    int rank, size;
    
  
    // Initialize MPI
    MPI_Init(&argc, &argv);

    // Get the rank and size of the current process
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    char string[] = "hello";
    int length = strlen(string); 
    
    // Only processes up to the length of the string to avoid an out-of-bounds error
    if(rank < length){
    
        // Subtracting 32 from a lowercase letter converts it to uppercase in ASCII
        string[rank] -= 32;
        printf("rank: %d string: %s \n",rank,string);

}

    // Finalize MPI environment
    MPI_Finalize();
    return 0;
}
