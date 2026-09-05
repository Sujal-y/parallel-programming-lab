#include <stdio.h>
#include <string.h>
#include <mpi.h>

int main(int argc, char *argv[]) {
    int rank, size;
    char ch;
    char word[100];

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0) {
        printf("Enter word of length %d (e.g. PCAP): ", size);
        scanf("%s", word);
    }

    // Scatter 1 character to each process corresponding to its rank
    MPI_Scatter(word, 1, MPI_CHAR, &ch, 1, MPI_CHAR, 0, MPI_COMM_WORLD);

    // Process of rank 'r' repeats its character (r + 1) times
    int count = rank + 1;
    char local_expanded[count];
    for (int i = 0; i < count; i++) {
        local_expanded[i] = ch;
    }

    // Calculate total output length = N * (N + 1) / 2
    int total_len = size * (size + 1) / 2;
    char output_str[total_len + 1];

    // Prepare variable counts and displacements for MPI_Gatherv
    int sendcounts[size], displs[size];
    if (rank == 0) {
        int offset = 0;
        for (int i = 0; i < size; i++) {
            sendcounts[i] = i + 1;
            displs[i] = offset;
            offset += sendcounts[i];
        }
    }

    // Gather variable length chunks from all processes
    MPI_Gatherv(local_expanded, count, MPI_CHAR,
                output_str, sendcounts, displs, MPI_CHAR,
                0, MPI_COMM_WORLD);

    if (rank == 0) {
        output_str[total_len] = '\0';
        printf("Output Word: %s\n", output_str);
    }

    MPI_Finalize();
    return 0;
}
