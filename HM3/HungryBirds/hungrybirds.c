#include "hungrybirds.h"
#include <semaphore.h>
#include <signal.h>
#include <time.h>


//Birds
pthread_t *all_bbirds;
pthread_t pbird;
int no_bbirds;
int no_worms;
int worm_count;

//Semaphores
sem_t sem_mutex;
sem_t empty;
sem_t not_empty;

//Dish and worms
int worms_in_dish;

//Fairness testing
int *all_bbirds_worm_count;

void *bbird_hungy(void *vargp){ //Vargp is not used

    long bbird_index = (long)vargp;
    all_bbirds_worm_count[bbird_index] = 0;
    //Awaits semaphore to be unlocked! Continues to be hungry for the entire sim_dur
    while(1) {

        //If there are worms in the dish, each birds needs mutex access
        sem_wait(&sem_mutex);
        sem_wait(&not_empty);
        if(worms_in_dish != 0){
            //There are worms in the dish
            printf("Bbird No: %ld is Consuming worm: %d\n", bbird_index, worm_count++);
            //Keeping track of how many worms each bird has gotten
            all_bbirds_worm_count[bbird_index]++;
            worms_in_dish--; //Worm is eaten
            sem_post(&not_empty);
        } else {
            //Dish is empty
            printf("EMPTY!");
            sem_post(&empty);
        }
        //printf("ThreadId: %d\n", pthread_self());
        sem_post(&sem_mutex);
        usleep(SLEEPNOHUNGY);// The birds are not hungry, is changed in .h
    }
}

void *pbird_work(void *vargp){
    //Runs through the entire simulation
    while(1) {
        sem_wait(&empty); //Waits for call that the dish is empty
        printf("Refilling dish\n");
        worms_in_dish = DISHSIZE;
        sem_post(&not_empty);
    }
}

void hungry_birds_init(int temp_no_bbirds){

    worm_count = 0;

    //Semaphore init
    sem_init(&sem_mutex, 0, 1);
    sem_init(&empty, 0, 0);
    sem_init(&not_empty, 0, 1);

    //Initialize all of the birds
    all_bbirds = malloc(temp_no_bbirds * sizeof(pthread_t));
    all_bbirds_worm_count = malloc(temp_no_bbirds * sizeof(int));
    no_bbirds = temp_no_bbirds;

    //Initialize dish
    worms_in_dish = DISHSIZE;
    long i;
    //Make 'em hungy <3
    for(i = 0; i < no_bbirds; i++){
        //Birds at set index is hungyfied
        pthread_create(&all_bbirds[i],NULL, bbird_hungy, (void*)i);
    }

    //Activate parent
    pthread_create(&pbird, NULL, pbird_work, NULL);

    //The simulation runs for 20 seconds in total -- set in .h
    sleep(SIMDURATION);
    for(i = 0; i < no_bbirds; i++){
        //Birds at set index is hungyfied
        pthread_kill(all_bbirds[i], 0);
    }
    pthread_kill(pbird, 0);

    for(int y = 0; y < no_bbirds; y++){
        printf("Bbird index: %d got this many %d worms! \n", y, all_bbirds_worm_count[y]);
    }
    return;
}
