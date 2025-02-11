#include "hungrybirds.h"

int main(int argc, char *argv[]){

    if(argv[1] != NULL){
        hungry_birds_init(atoi(argv[1]));
    } else {
        hungry_birds_init(4);
    }
    
    return 0;
}