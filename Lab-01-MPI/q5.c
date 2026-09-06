#include<mpi.h>
#include <stdio.h>

// Returns factorial of N
long factorial(int n) {
    long long fact = 1;
    for (int i = 1; i <= n; i++) fact *= i;
    return fact;
}

// Returns the fibonacci number for N
int fibonacci(int n) {
    if (n <= 0) return 0;
    if (n == 1) return 1;
    int a = 0, b = 1, c;
    for (int i = 2; i <= n; i++) {
        c = a + b;
        a = b;
        b = c;
    }
    return b;
}

int main(int argc , char *argv[]){
	int rank,size;

    //Initializing the environment and copying data to local variables
	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD , &rank);
	MPI_Comm_size(MPI_COMM_WORLD , &size);

    // Even rank prints its factorial
	if(rank%2 ==0){
	printf("rank: %d : fact:- %ld \n",rank,factorial(rank));
	}
    // Odd rank prints its fib number
	else{
	printf("rank %d : fib :- %d \n",rank ,fibonacci(rank));
	}

    MPI_Finalize();
    return 0;
}
