#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h> // USED FOR DEBUG
#include <string.h> // -||-

int main (int argc, char *argv[]) {
    int rank, size;
    bool debug = false;

    // Init MPI
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Argument handling
    int NO_OF_ROUNDS = atoi(argv[1]);
    if (argc == 3) {
        debug = (strcmp(argv[2], "--DEBUG") == 0);
    }

    // Set initial value to the rank
    int proc_value = rank;

    // Start "timer"
    double start_time = MPI_Wtime();
    // Repeat for 1-3 rounds
    for (int round = 0; round < NO_OF_ROUNDS; round++) {

        // TODO: IMPLEMENT RING SOLUTION

    }
    // Stop "timer"
    double exec_time = MPI_Wtime() - start_time;

    double max_time;
    // Reduce with MPI_MAX to find longest proc time, "save" in root (proc 0)
    MPI_Reduce(&exec_time, &max_time, 1, MPI_DOUBLE, MPI_MAX, 0, MPI_COMM_WORLD);

    // Print result
    if (rank == 0) {
        printf("Processes:\t\t%d\n", size);
        printf("Total runtime:\t\t%f\n", max_time);
        printf("Runtime per round:\t%f\n", max_time/(double)NO_OF_ROUNDS);
    }
    MPI_Finalize();
    return 0;
}
