#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include "Output.h"
#include "utilidades.h"

int validaArtista (char* grupo, char* type, char* linha,Output* erros){

   
    toLowerCase(type);
    if (!((strcmp(type,"\"individual\"") == 0)  || (strcmp(type,"\"group\"") == 0) ))
    {   
        outputErros(erros,linha);
        return 0;
    }


    if(strcmp(type,"\"individual\"") == 0){
        if(!(strcmp(grupo,"\"[]\"") == 0))
        {
            outputErros(erros,linha);
            return 0;
        } 
    }


    

    int tamanho = strlen(grupo);   
    if (grupo[1] != '[' || grupo[tamanho-2] != ']'){
        outputErros(erros,linha);
        return 0;
    }



    return 1;
}