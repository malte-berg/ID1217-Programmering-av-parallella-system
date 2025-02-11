#ifndef HUNGRYBIRDS_H
#define HUNGRYBIRDS_H

#define _REENTRANT

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

extern pthread_t *all_bbirds;
extern pthread_t *pbird;
extern int no_bbirds;


void hungry_birds_init(int temp_no_bbirds);

#endif