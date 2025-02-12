#ifndef _REENTRANT
#define _REENTRANT
#endif

#ifndef HUNGRYBIRDS_H
#define HUNGRYBIRDS_H

//User defined constants
#define DISHSIZE 10
#define SIMDURATION 20
#define SLEEPNOHUNGY 20000

//Standard Includes <3
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>
#include <signal.h>

//Birds
extern pthread_t *all_bbirds;
extern pthread_t pbird;
extern int no_bbirds;
extern int no_worms;

//Dish and Worms
extern int worms_in_dish;
extern int *all_bbirds_worm_count;

void hungry_birds_init(int temp_no_bbirds); //Initializes all of the preqs

void *bbird_hungy(void *vargp); //The birds want to eat

void *pbird_work(void *vargp);  //Activate parent-bird
#endif
