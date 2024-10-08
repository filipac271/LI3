#include "main/mainMode.h"
#include "main/mainTests.h"

#include <stdio.h> 

int main(int argc, char **argv){
    if(argc == 3){
    
        principal(argv);
    }
    else if (argc == 4){
        teste(argv);
    }
}