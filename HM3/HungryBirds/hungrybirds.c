#include "hungrybirds.h"

pthread_t *all_bbirds;
pthread_t *pbird;
int no_bbirds;

void hungry_birds_init(int temp_no_bbirds){

    all_bbirds = malloc(temp_no_bbirds * sizeof(pthread_t));
    no_bbirds = temp_no_bbirds;
    pbird = malloc(sizeof(pthread_t));

    printf("%d\n", no_bbirds);

    return;
}