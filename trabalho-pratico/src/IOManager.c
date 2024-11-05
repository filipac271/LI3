#include <stdio.h>
#include <stdlib.h>
#include <string.h>


FILE* abrirFILE(char* diretoria, char* subdiretoria){

        FILE* ficheiro = NULL;
        // O snprintf junta os argumentos para criar uma diretoria que armazena em filePath
        char filePath[1024];
        if(strcmp(subdiretoria,"") != 0){
        
            snprintf(filePath, sizeof(filePath), "%s/%s", diretoria, subdiretoria);

        }else{
            snprintf(filePath, sizeof(filePath), "%s", diretoria);
        }

        
        // Abre o ficheiro no modo de leitura
        ficheiro = fopen(filePath, "r");
        if (ficheiro == NULL) {
            printf("Erro ao abrir o ficheiro %s\n", filePath);
        } else {
            printf("Ficheiro %s aberto com sucesso\n", filePath);
        }

    return ficheiro;
}


FILE* abrirFILE_ERROS(char* diretoria){

        FILE* ficheiro = NULL;
        // O snprintf junta os argumentos para criar uma diretoria que armazena em filePath
        char filePath[1024];
       snprintf(filePath, sizeof(filePath), "%s", diretoria);

        
        // Abre o ficheiro no modo de leitura
        ficheiro = fopen(filePath, "w");
        if (ficheiro == NULL) {
            printf("Erro ao abrir o ficheiro %s\n", filePath);
        } else {
            printf("Ficheiro %s aberto com sucesso\n", filePath);
        }

    return ficheiro;
}


void fecharFILE (FILE* ficheiro){
    fclose(ficheiro);
}