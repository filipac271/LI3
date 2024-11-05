#include "main/feeder.h"
#include "parser/parsermusica.h"
#include "parser/userParser.h"
#include "controler/artistsController.h"
#include "controler/usersController.h"
#include "controler/musicsController.h"
#include "controler/mainController.h"
#include "querie/querieManager.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <glib.h>


#define NUM_FILES 3


void lerFicheiros(char* pastaPrincipal, char* fileNames[], int numFiles, char* queriesFile) {

    // Aloca memória para armazenar os ponteiros para os ficheiros
    FILE** ficheiros = malloc(numFiles * sizeof(FILE*));
    FILE* queriesInput;


    if (ficheiros == NULL) {
        printf("Erro de alocação de memória\n");
        return;
    }
    queriesInput = fopen(queriesFile,"r");


    for (int i = 0; i < numFiles; ++i) {
        // Constrói o caminho completo: pastaPrincipal/subpasta/nomeFicheiro
        // O snprintf junta os argumentos para criar uma diretoria que armazena em filePath
        char filePath[1024];
        snprintf(filePath, sizeof(filePath), "%s/%s", pastaPrincipal, fileNames[i]);

        
        // Abre o ficheiro no modo de leitura
        ficheiros[i] = fopen(filePath, "r");

        if (ficheiros[i] == NULL) {
            printf("Erro ao abrir o ficheiro %s\n", filePath);
        } else {
            printf("Ficheiro %s aberto com sucesso\n", filePath);
        }
    }

    

    MainController* data = feeder(ficheiros);
    print_all_Data(data);



    queries(data,queriesInput);
    
    destroyData(data);


    // Fechar os ficheiros depois de os usar (exemplo)
    for (int i = 0; i < numFiles; ++i) {
        if (ficheiros[i] != NULL) {
            fclose(ficheiros[i]);
        }
    }
    fclose(queriesInput);



    // Liberta a memória alocada
    free(ficheiros);
}

int principal(char** argv) {

    char* pastaPrincipal = argv[1];  // Recebe a pasta principal como argumento
    
    char* queriesFile = argv[2];


    // Lista de nomes de ficheiros na subpasta
    char* fileNames[NUM_FILES] = {"artists.csv", "musics.csv", "users.csv"};

    // Chama a função para ler os ficheiros
    lerFicheiros(pastaPrincipal, fileNames, NUM_FILES,queriesFile);

    return 0;
}