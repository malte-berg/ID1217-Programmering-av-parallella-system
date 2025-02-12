#include "hungrybears.h"

//Bees and bear
pthread_t *honeybees;
pthread_t bear;
int no_bees;
int honeypot_size;

//Semaphores
sem_t sem_mutex;
sem_t full;
sem_t not_full;

//Honey and pot
int honey_in_pot;
int honey_counter;

//Fairness testing
int *all_bees_honey_count;

void *bee_buzz(void *vargp){

    long bee_index = (long)vargp;
    //Awaits semaphore to be unlocked! Continues to add honey for the entire sim_dur
    while(1) {

        //If there is space in the pot, each bee needs mutex access
        sem_wait(&sem_mutex);
        sem_wait(&not_full);
        if(honey_in_pot < HONEYPOT_MAX_SIZE){
            //There are empty spaces in the honeypot
            printf("Bee No: %ld has added honey: %d\n", bee_index, honey_counter++);
            //Keeping track of how much honey each bee has added
            all_bees_honey_count[bee_index]++;

            //The bee that adds the last honey signals if the pot is full after
            if (++honey_in_pot == HONEYPOT_MAX_SIZE) {
                printf("FULL!\n");
                sem_post(&full);
            } else {
                sem_post(&not_full);
            }
        }
        sem_post(&sem_mutex);
        usleep(SLEEPTIRED);
    }
}

void *bear_eat(void *vargp){
    //Runs through the entire simulation
    while(1) {
        sem_wait(&full); //Waits for call that the pot is full
        printf("Yum, not hungy, go sleep\n");

        //Eats all of the honey in the pot
        honey_in_pot = 0;
        //Signals that the pot is empty
        sem_post(&not_full);
    }
}

void hungry_bears_init(int temp_no_bees){

    //Semaphore init
    sem_init(&sem_mutex, 0, 1);
    sem_init(&full, 0, 0);
    sem_init(&not_full, 0, 1);

    //Initialize all of the bees
    honeybees = malloc(temp_no_bees * sizeof(pthread_t));
    all_bees_honey_count = malloc(temp_no_bees * sizeof(int));
    no_bees = temp_no_bees;

    //Initialize the honeypot
    honeypot_size = HONEYPOT_MAX_SIZE;
    honey_in_pot = 0;
    long i;

    //Make 'em produce honey <3
    for(i = 0; i < no_bees; i++){
        //All of the bees are activated
        pthread_create(&honeybees[i],NULL, bee_buzz, (void*)i);
    }
    //Activate bear
    pthread_create(&bear, NULL, bear_eat, NULL);

    //The simulation runs for 20 seconds in total -- set in .h
    sleep(SIM_DURATION);
    for(i = 0; i < no_bees; i++){
        //Kill all of the bees after the simulation is done
        pthread_kill(honeybees[i], 0);
    }
    pthread_kill(bear, 0);

    for(int y = 0; y < no_bees; y++){
        printf("Bee index: %d got this many %d honeys! \n", y, all_bees_honey_count[y]);
    }
    return;
}
