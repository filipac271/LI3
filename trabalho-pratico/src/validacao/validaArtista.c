#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <glib.h>
#include <unistd.h>

int validaArtista (char* grupo, char* type){

    if(strcmp(type,"individual") == 0){
        if(!(strcmp(grupo,"\"[]\"") == 0)){
            return 0;
        } 
    }



    return 1;
}