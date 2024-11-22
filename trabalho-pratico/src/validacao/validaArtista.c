#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <glib.h>
#include <unistd.h>
#include "IOManager.h"

int validaArtista (char* grupo, char* type, char* linha,Output* erros){

    int terGrupo = 1;
    int tembarra = 1;


    if(strcmp(type,"\"individual\"") == 0){
        if(!(strcmp(grupo,"\"[]\"") == 0)){
                      
           terGrupo = 0;
        } 
    }

    int tamanho = strlen(grupo);   
    if (grupo[1] != '[' || grupo[tamanho-2] != ']'){tembarra = 0;}


    if(!(terGrupo & tembarra)) outputErros(erros,linha);

    return 1;
}