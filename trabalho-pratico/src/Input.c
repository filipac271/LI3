#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "Input.h"

#define MaxTokensSize 8

struct parser{
    FILE* file;

    char* line;

    char* lineError;

    char** tokens;
};

int checkDiretoria (char* diretoria){
    FILE* ficheiro = NULL;

    ficheiro = fopen(diretoria, "r");
    if (ficheiro == NULL) {
        fclose(ficheiro);
        return 0;
    } 

    fclose(ficheiro);
    return 1;
}


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
    //Dá free de linha e return caso n haja mais linhas no ficheiro
    free(line);
    parserE->tokens[0]=NULL;
    return parserE;
   }


    // Remove a nova linha no final, se existir
    if (line[strlen(line) - 1] == '\n') {
            line[strlen(line) - 1] = '\0';
    }


    parserE->lineError = strdup(line);
    parserE->line = line;


    char* lineCopy = line;
   
    int i = 0;
  
    // Divide a linha em tokens usando strsep
    char* token = strsep(&lineCopy, ";");
    while (token != NULL && i < 10) {
         // Armazenar o token no array
        parserE->tokens[i++]=token;
        token = strsep(&lineCopy, ";");
    }

   //Retorna a estrutura do parser
   return parserE;
}

//Função que cria e aloca memoria para a estrutura e os campos do Parser
Parser* newParser(char * diretoria,char* subdiretoria)
{
   FILE* file= abrirFILE(diretoria,subdiretoria);
   Parser* parserE=malloc(sizeof(struct parser));
   parserE->file=file;
   parserE->tokens=malloc(MaxTokensSize * sizeof(char *));
   parserE->line = NULL;
   parserE->lineError = NULL;

  
   return parserE;
}

//Função que dá free da memoria para a estrutura e os campos do Parser
void freeParser(Parser* parserE)
{
    fecharFILE(parserE->file); 
    free(parserE->tokens);
    free(parserE);
}

char* pegaLinha(Parser* parserE) {

    size_t len=0;
    char* line = NULL; 
    if(getline(&line,&len,parserE->file) == -1) {
        //Dá free de linha e return de NULL caso n haja mais linhas no ficheiro
        free(line);
        return NULL;
    }

    // Remove a nova linha no final, se existir
    if (line[strlen(line) - 1] == '\n') {
            line[strlen(line) - 1] = '\0';
    }

    return line;
}



char** getTokens(Parser * parserE)
{
  if (parserE->tokens[0]==NULL) return NULL;

    return parserE->tokens;
}

char* getLine( Parser* parserE)
{
    return parserE->line;
}

char* getLineError( Parser* parserE)
{
    return parserE->lineError;
}







int contar_linhas( char *nome_ficheiro) {
    FILE *file = fopen(nome_ficheiro, "r");
    if (file == NULL) {
        perror("Erro ao abrir o ficheiro");
        return -1;  // Retorna -1 em caso de erro
    }

    int linhas = 0;
    char ch;
    while ((ch = fgetc(file)) != EOF) {
        if (ch == '\n') {
            linhas++;
        }
    }

    fclose(file);
    return linhas;
}