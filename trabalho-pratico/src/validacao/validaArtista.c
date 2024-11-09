#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <glib.h>
#include <unistd.h>
#include "IOManager.h"

int validaArtista (char* grupo, char* type, char* linha,Output* erros){

    if(strcmp(type,"individual") == 0){
        if(!(strcmp(grupo,"\"[]\"") == 0)){

            outputErros(erros,linha);
            
            return 0;
        } 
    }



    return 1;
}