#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include "mainParser.h"

#define NUM_FILES 3

void lerFicheiros(char* pastaPrincipal, char* subpasta, char* fileNames[], int numFiles, char* queriesFile) {
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
        snprintf(filePath, sizeof(filePath), "%s/%s/%s", pastaPrincipal, subpasta, fileNames[i]);

        // Abre o ficheiro no modo de leitura
        ficheiros[i] = fopen(filePath, "r");

        if (ficheiros[i] == NULL) {
            printf("Erro ao abrir o ficheiro %s\n", filePath);
        } else {
            printf("Ficheiro %s aberto com sucesso\n", filePath);
        }
    }


    parser(ficheiros);
    

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
    char* subpastaSemErros = "sem_erros";    // Define a subpasta a ser usada 
    char* subpastaComErros = "com_erros";    // Define a subpasta a ser usada 
    char* queriesFile = argv[2];

    // Lista de nomes de ficheiros na subpasta
    char* fileNames[NUM_FILES] = {"artists.csv", "musics.csv", "users.csv"};

    // Chama a função para ler os ficheiros
    lerFicheiros(pastaPrincipal, subpastaSemErros, fileNames, NUM_FILES,queriesFile);

    return 0;
}
