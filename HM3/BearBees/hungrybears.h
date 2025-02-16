#ifndef _REENTRANT
#define _REENTRANT
#endif

#ifndef HUNGRYBEARS_H
#define HUNGRYBEARS_H

#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

#define HONEYPOT_MAX_SIZE 10
#define SLEEPTIRED 20000
#define SIM_DURATION 20

//Bees and bear
extern pthread_t *honeybees;
extern pthread_t bear;
extern int no_bees;
extern int honeypot_size;

//Pot and honey
extern int honey_in_pot;
extern int *all_bees_honey_count;

void hungry_bears_init(int temp_no_bees);
void *bear_eat(void *vargp);
void *bee_buzz(void *vargp);

#endif
