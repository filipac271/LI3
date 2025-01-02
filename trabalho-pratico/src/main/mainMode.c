#include "controler/mainController.h"
#include "querie/querieManager.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <glib.h>





int principal(char* pastaPrincipal , char* queriesFile) {

    //O mainFeed devolverá o controllador geral que contem os outros controladores das outras 3 entidades que já contêm o dataset parseado
    MainController* data = mainFeed(pastaPrincipal);

    if(data == NULL)return 1;

    //Função simples que printa todas as HashTables principais
    print_all_Data(data);

    queries(data,queriesFile);
    
    //Função que liberta a memória do mainController e dos outros controladores
    destroyData(data);


    return 0;
}