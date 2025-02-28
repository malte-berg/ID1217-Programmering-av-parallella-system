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
    if (debug) {
        printf("Proc %d: %d\n", rank, proc_value);
    }

    // Start "timer"
    double start_time = MPI_Wtime();
    // Repeat for 1-3 rounds
    for (int round = 0; round < NO_OF_ROUNDS; round++) {
        if (rank == 0) {
            int min = proc_value, max = proc_value;
            int *min_max = (int*)malloc(2 * sizeof(int));
            min_max[0] = min;
            min_max[1] = max;

            MPI_Send(min_max, 2, MPI_INT, 1, 0, MPI_COMM_WORLD);
            MPI_Recv(min_max, 2, MPI_INT, size - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            MPI_Send(min_max, 2, MPI_INT, 1, 0, MPI_COMM_WORLD);
            if (debug){
                printf("Min: %d\tMax: %d\tRound: %d\n", min_max[0], min_max[1], round);
            }
        } else {
            int *min_max = (int*)malloc(2 * sizeof(int));

            MPI_Recv(min_max, 2, MPI_INT, rank - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            min_max[0] = (proc_value < min_max[0]) ? proc_value : min_max[0];
            min_max[1] = (proc_value > min_max[1]) ? proc_value : min_max[1];
            MPI_Send(min_max, 2, MPI_INT, (rank + 1) % size, 0, MPI_COMM_WORLD);
            MPI_Recv(min_max, 2, MPI_INT, rank - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            if (rank < size-1) {
                MPI_Send(min_max, 2, MPI_INT, rank + 1, 0, MPI_COMM_WORLD);
            }

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
