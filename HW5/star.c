#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

int main (int argc, char *argv[]) {
    int rank, size;
    bool debug = false;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int NO_OF_ROUNDS = atoi(argv[1]);
    if (argc == 3) {
        debug = (strcmp(argv[2], "--DEBUG") == 0);
    }

    int proc_value = rank;

    double start_time = MPI_Wtime();
    for (int round = 0; round < NO_OF_ROUNDS; round++) {
        if (rank == 0) {
            int *buf = (int*)malloc(sizeof(int)*size);

            for (int i = 1; i < size; i++) {
                MPI_Recv(&buf[i], 1, MPI_INT, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                if (debug) {
                    printf("Collector got value %d from proc %d in round %d.\n", buf[i], i, round);
                }
                buf[i]++; /* Simulated work, adding 1 to value */
            }

            for (int i = 1; i < size; i++) {
                MPI_Send(&buf[i], 1, MPI_INT, i, 0, MPI_COMM_WORLD);
                if (debug) {
                    printf("Collector sent value %d to proc %d in round %d.\n", buf[i], i, round);
                }
            }
        } else {
            MPI_Send(&proc_value, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
            MPI_Recv(&proc_value, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        }
    }
    double exec_time = MPI_Wtime() - start_time;

    double max_time;
    MPI_Reduce(&exec_time, &max_time, 1, MPI_DOUBLE, MPI_MAX, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        printf("Total runtime: %f\n", max_time);
    }
    MPI_Finalize();
    return 0;
}
