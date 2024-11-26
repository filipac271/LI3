#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "IOManager.h"

struct parser{
    FILE* file;

    char* line;

    char* lineError;

    char** tokens;
};

struct output
{
    FILE* file;
};

#define MaxTokensSize 8

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



//Função que cria e aloca memoria para a estrutura e os campos do Output
Output* iniciaOutput (char* filename)
{
    FILE * output_file=fopen(filename, "w");
    Output* output3= malloc(sizeof(Output*));
    output3->file=output_file;
    return output3;
}

//Função que dá free da memoria para a estrutura e os campos do Output
void freeOutput(Output* output)
{
    fecharFILE(output->file);
    free(output);
}

//Função de output de queries com informações inválidas
void outputNULL(Output* output3)
{
    fprintf(output3->file,"\n");
}

//Função de output das linhas do dataset inválidas
void outputErros(Output* erros,char* linha)
{
    fprintf(erros->file,"%s\n",linha);
}

//Função de output da Querie 1
void output1(Output* output1, char* userEmail, char* userNome, char* userApelido,int idade, char* userCountry)
{
    fprintf(output1->file,"%s;%s;%s;%d;%s\n",userEmail,userNome,userApelido, idade,userCountry ); 
}

//Função de output da Querie 2
void output2(Output* output2, char* nome, char* tipo, char* time,char* pais)
{
    fprintf(output2->file,"%s;%s;%s;%s\n",nome,tipo, time, pais);
}

//Função de output da Querie 3
void output3(Output* output3, char* genero, int num)
{
    fprintf(output3->file,"%s;%d\n",genero,num);  
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