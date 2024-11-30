#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <glib.h>
#include <unistd.h>
#include "Output.h"
#include "utilidades.h"

int validaArtista (char* grupo, char* type, char* linha,Output* erros){

    int terGrupo = 1;
    int tembarra = 1;
    int typeCorreto = 1;
   
    toLowerCase(type);
    if (!((strcmp(type,"\"individual\"") == 0)  || (strcmp(type,"\"group\"") == 0) ))
    {   
        // sleep(3);
        // printf("papkdsa%s\n",type);

        typeCorreto = 0;
    }


    if(strcmp(type,"\"individual\"") == 0){
        if(!(strcmp(grupo,"\"[]\"") == 0)){
                      
           terGrupo = 0;
        } 
    }


    

    int tamanho = strlen(grupo);   
    if (grupo[1] != '[' || grupo[tamanho-2] != ']'){tembarra = 0;}


    if(!(terGrupo & tembarra & typeCorreto)) outputErros(erros,linha);

    return (terGrupo & tembarra & typeCorreto);
}