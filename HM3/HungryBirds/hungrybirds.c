#include "hungrybirds.h"

pthread_t *all_bbirds;
pthread_t *pbird;
int no_bbirds;
int no_worms;

void *bbird_hungy(void *vargp){ //Vargp is not used
    //Checks if there are any worms in the dish
    /*while(1){
        printf("Im hungy <3\n");
        sleep(3);
    }*/

}

void *pbird_work(void *vargp){


}

void hungry_birds_init(int temp_no_bbirds){

    //Initialize all of the birds
    all_bbirds = malloc(temp_no_bbirds * sizeof(pthread_t));
    no_bbirds = temp_no_bbirds;
    pbird = malloc(sizeof(pthread_t));

    //Make 'em hungy <3
    for(int i = 0; i < no_bbirds; i++){
        //Birds at set index is hungyfied
        pthread_create(&all_bbirds[i],NULL, bbird_hungy, NULL);
    }
    //Activate parent
    pthread_create(&pbird, NULL, pbird, NULL);

    //The simulation runs for 20 seconds in total -- set in h
    sleep(SIMDURATION);
    return;
}
