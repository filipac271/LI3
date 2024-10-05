#include <stdio.h> 
#include "mainMode.h"
#include "mainTests.h"



int main(int argc, char **argv){
    if(argc == 3){
      
        principal(argv);
    }
    else if (argc == 4){
        teste(argv);
 
    }

 

}