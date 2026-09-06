#include "mpi.h"
#include <stdio.h>
int main(int argc , char* argv[])
{
	//creating local variables to store the value of rank of a process
	int rank,size;
	//initializing the the MPI environment
	MPI_Init(&argc,&argv);
	//copying the rank of the process to local variable rank
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	// copying the size of the com world (total processes)
	MPI_Comm_size(MPI_COMM_WORLD,&size);
	
	printf("my rank is %d in total of %d processes\n",rank,size);

	//terminates the environment and frees up the resources
	MPI_Finalize();
	return 0;
	}