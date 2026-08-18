#include <mpi.h>
#include <stdio.h>
#include <math.h>

int main(int argc, char *argv[]) {
    int rank, size;
   
    
    MPI_Init(&argc, &argv);

   
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int num1 =50, num2 =10;
    
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
    printf("multiply: %d\n",mul);
    }
    else if(rank == 3){
    int div = num1/num2;
    printf("division: %d\n",div);
    }
    
   
    
    
    MPI_Finalize();
    return 0;
}
