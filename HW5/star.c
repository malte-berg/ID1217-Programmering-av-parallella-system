#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>

int main (int argc, char *argv[]) {
    int rank, size;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int NO_OF_ROUNDS = atoi(argv[1]);

    MPI_Barrier(MPI_COMM_WORLD);
    for (int r = 0; r < NO_OF_ROUNDS; r++) {
        printf("Hello world! I'm %d of %d in round %d\n", rank, size, r);
        fflush(stdout);
    }
    MPI_Finalize();
    return 0;

}
