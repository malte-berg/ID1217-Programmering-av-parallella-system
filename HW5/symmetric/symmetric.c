#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>    // USED FOR DEBUG
#include <string.h>     // -||-
#include <time.h>       // USED FOR rand()

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

    // Randomize with time(NULL) and rank
    srand(time(NULL) + rank);
    // Set initial value to randomized int
    int proc_value = rand() % 100;

    // Start "timer"
    double start_time = MPI_Wtime();
    // Repeat for 1-3 rounds
    for (int round = 0; round < NO_OF_ROUNDS; round++) {
        int new, min = proc_value, max = proc_value;

        for (int i = 0; i < size; i++) {
            if (rank == i) continue; // Skip self

            // Avoiding deadlock
            if (rank % 2 == 0 && i % 2 == 1) { // even to odd
                MPI_Send(&proc_value, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
                MPI_Recv(&new, 1, MPI_INT, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            } else if (rank % 2 == 1 && i % 2 == 0) { // odd to even
                MPI_Recv(&new, 1, MPI_INT, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                MPI_Send(&proc_value, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
            }
            // even to even and odd to odd
            else if (rank < i) {
                MPI_Send(&proc_value, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
                MPI_Recv(&new, 1, MPI_INT, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            } else if (rank > i) {
                MPI_Recv(&new, 1, MPI_INT, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                MPI_Send(&proc_value, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
            }
            if (debug) {
                printf("Proc %d recieved value %d from proc %d (Round %d)\n", rank, new, i, round);
                fflush(stdout);
            }
            max = (new > max) ? new : max;
            min = (new < min) ? new : min;
        }
        if (debug) {
            if (rank == 0) {
                printf("\tMin:\t%d\tMax:\t%d (Round %d)\n", min, max, round);
                fflush(stdout);
            }
        }
        MPI_Barrier(MPI_COMM_WORLD);

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
