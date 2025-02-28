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
        // Middle process in centralized solution
        if (rank == 0) {
            int *buf = (int*)malloc(sizeof(int)*size);

            // Collect values (ranks) from all procs and increase value by 1
            for (int i = 1; i < size; i++) {
                MPI_Recv(&buf[i], 1, MPI_INT, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                if (debug) {
                    printf("Collector got value %d from proc %d in round %d.\n", buf[i], i, round + 1);
                }
                buf[i]++; /* Simulated "work", adding 1 to value */
            }

            // Send back values (increased ranks) to all procs
            for (int i = 1; i < size; i++) {
                MPI_Send(&buf[i], 1, MPI_INT, i, 0, MPI_COMM_WORLD);
                if (debug) {
                    printf("Collector sent value %d to proc %d in round %d.\n", buf[i], i, round + 1);
                }
            }

            // Free the buffer
            free(buf);
        } else { // All other procs, send their value and recieve their new value
            MPI_Send(&proc_value, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
            MPI_Recv(&proc_value, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        }
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
