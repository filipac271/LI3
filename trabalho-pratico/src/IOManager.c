#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "IOManager.h"

struct parser{
    FILE* file;
    char* line;
    char** tokens;
};


#define TOKEN_SIZE 8

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
           // printf("Ficheiro %s aberto com sucesso\n", filePath);
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
          //  printf("Ficheiro %s aberto com sucesso\n", filePath);
        }

    return ficheiro;
}


void fecharFILE (FILE* ficheiro){
    fclose(ficheiro);
}


Parser* parser(Parser* parserE) {
    size_t len=0;
    char* line = NULL;

   if( getline(&line,&len,parserE->file)==-1 ) 
   {
    free(line);
    parserE->tokens[0]=NULL;
    return parserE;
   }

  
    // Remove a nova linha no final, se existir
    if (line[strlen(line) - 1] == '\n') {
            line[strlen(line) - 1] = '\0';
    }

    char* lineCopy = line;
   
    int i = 0;
    // parserE->linha=lineCopy;
    // Divide a linha em tokens usando strsep
    char* token = strsep(&lineCopy, ";");
    while (token != NULL && i < 10) {
         // Armazenar o token no array
        parserE->tokens[i++]=token;
        token = strsep(&lineCopy, ";");
    }
   
   parserE->line = line;
    
  
   return parserE;
}

Parser* newParser(char * diretoria,char* subdiretoria)
{
    FILE* file= abrirFILE(diretoria,subdiretoria);
   Parser* parserE=malloc(sizeof(struct parser));
   parserE->file=file;
   parserE->tokens=malloc(10* sizeof(char *));
   parserE->line = NULL;

  
   return parserE;
}

void freeParser(Parser* parserE)
{
    fclose(parserE->file); 
    free(parserE->tokens);
    free(parserE);
}

char* pegaLinha(Parser* parserE) {
    size_t len=0;
    char* line = NULL; 
    getline(&line,&len,parserE->file);
    return line;
}



char** getTokens(Parser * parserE)
{
  if (parserE->tokens[0]==NULL) return NULL;

    return parserE->tokens;
}


char* getLine (Parser* parserE){
    return parserE->line;
}