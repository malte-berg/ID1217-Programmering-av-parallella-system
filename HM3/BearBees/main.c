
#include "hungrybears.h"

int main(int argc, char *argv[]){

    //Read if number of birds are specified <3
        if(argv[1] != NULL){
            hungry_bears_init(atoi(argv[1]));
        } else {
            hungry_bears_init(4);
        }

    return 0;
}
