#include <mpi.h>
#include <stdio.h>
#include <math.h>

int main(int argc, char *argv[]) {
    int rank, size;
   
    // Initialize the MPI environment
    MPI_Init(&argc, &argv);

    // copy the rank and size to local variables
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Input variables
    int num1 =50, num2 =10;
    
    // Applies one arithmetic operation for each rank up to 4 (add, sub, mul, div)
    if(rank ==0){
        int sum = num1+num2;
        printf("addition: %d \n",sum);
    }
    else if(rank == 1){
        int sub = num1-num2;
        printf("subtraction: %d\n",sub);
    }
    else if(rank == 2){
        int mul = num1*num2;
        printf("multiplication: %d\n",mul);
    }
    else if(rank == 3){

        if(num2 == 0){
            printf("division by 0 is not possible\n");
            MPI_Finalize();
            return 0;
        }

        int div = num1/num2;
        printf("division: %d\n",div);
    }
    
    // Terminates the environment
    MPI_Finalize();
    return 0;
}
