#include "utilidades.h"
#include "ctype.h"
#include "stdio.h"
#include "unistd.h"
#include"Output.h"


int validaHistory(char* plataform,char* duration, Output* Erros, char* linha ){


    if(!validaDuracao(duration)){
        outputErros(Erros,linha);
        return 0;
    } 

    toLowerCase(plataform);
    if(!((strcmp(plataform,"\"mobile\"") == 0)  || (strcmp(plataform,"\"desktop\"") == 0) )){                 
        outputErros(Erros,linha);

        return 0;
    } 


    return 1;

}