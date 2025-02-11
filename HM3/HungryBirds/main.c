#include "hungrybirds.h"

int main(int argc, char *argv[]){

    //Read if number of birds are specified <3
    if(argv[1] != NULL){
        hungry_birds_init(atoi(argv[1]));
    } else {
        hungry_birds_init(4);
    }
    
    return 0;
}