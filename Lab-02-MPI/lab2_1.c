#include <mpi.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_WORD_SIZE 100

int main(int argc, char *argv[]) {
    int rank, size;
    char word[MAX_WORD_SIZE];
    MPI_Status status;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (size < 2) {
        if (rank == 0) {
            printf("at least 2 processes.\n");
        }
        MPI_Finalize();
        return 0;
    }

    if (rank == 0) {
        strcpy(word, "Hello World");
        printf("Process 0: Original word is: '%s'\n", word);
        fflush(stdout);

        MPI_Ssend(word, strlen(word) + 1, MPI_CHAR, 1, 0, MPI_COMM_WORLD);
        printf("Process 0 Successfully sent word to Process 1 using MPI_Ssend.\n");
        fflush(stdout);

        MPI_Recv(word, MAX_WORD_SIZE, MPI_CHAR, 1, 1, MPI_COMM_WORLD, &status);
        printf("Process 0: Received toggled word from Process 1: '%s'\n", word);
        fflush(stdout);
    } 
    else if (rank == 1) {
        MPI_Recv(word, MAX_WORD_SIZE, MPI_CHAR, 0, 0, MPI_COMM_WORLD, &status);
        printf("Process 1: Received word: '%s'\n", word);
        fflush(stdout);

        for (int i = 0; word[i] != '\0'; i++) {
            if (isupper(word[i])) {
                word[i] = tolower(word[i]);
            } else if (islower(word[i])) {
                word[i] = toupper(word[i]);
            }

        }
        printf("Process 1: Toggled word to: '%s'\n", word);
        fflush(stdout);

        MPI_Ssend(word, strlen(word) + 1, MPI_CHAR, 0, 1, MPI_COMM_WORLD);
        printf("Process 1: Sent toggled word back to Process 0 using MPI_Ssend.\n");
        fflush(stdout);
    }

    MPI_Finalize();
    return 0;
}
    
