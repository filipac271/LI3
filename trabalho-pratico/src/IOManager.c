#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "IOManager.h"
#include "querie/querie3.h"

struct parser{
    FILE* file;
   char* linha;
    char** tokens;
};

struct output
{
    FILE* file;
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
//   FILE* file= abrirFILE(diretoria,subdiretoria); // guardar file no estado
//   fseek(file, parserE->lastPosition, SEEK_SET);


    char* lineCopy;

   if( getline(&parserE->linha,&len  ,parserE->file)==-1 ) 
   {
  
     parserE->tokens[0]=NULL;
    return parserE;
   }
  
     lineCopy=strdup(parserE->linha);/// Para nao ser dividida a linha do parser
 
    if (lineCopy[0] != '\0' && lineCopy[strlen(lineCopy) - 1] == '\n') {
        lineCopy[strlen(lineCopy) - 1] = '\0';
    }

    int i = 0;
  
    // Divide a linha em tokens usando strsep
    char* token = strsep(&lineCopy, ";");
    while (token != NULL && i < 10) {
         // Armazenar o token no array
        parserE->tokens[i++]=token;
     
        token = strsep(&lineCopy, ";");
    }
    
  //free(lineCopy); // Dá double free
  
  
   return parserE;
}

Parser* newParser(char * diretoria,char* subdiretoria)
{
    FILE* file= abrirFILE(diretoria,subdiretoria);
   Parser* parserE=malloc(sizeof(struct parser));
   parserE->file=file;
   parserE->tokens=malloc(10* sizeof(char *));

  
   return parserE;
}

void freeParser(Parser* parserE)
{
     fclose(parserE->file); 
       free(parserE->tokens);
       free(parserE->linha);
    free(parserE);
}

char* pegaLinha(Parser* parserE) {
    FILE* ficheiro= parserE->file;
    size_t len =0;
    char* line; 
    getline(&line,&len, ficheiro);
 

    return line;
}

char** getTokens(Parser * parserE)
{
  if (parserE->tokens[0]==NULL) return NULL;
    return parserE->tokens;
}

char* getLinha( Parser* parserE)
{
    return strdup (parserE->linha);
}




Output* iniciaOutput (char* filename)
{
    FILE * output_file=fopen(filename, "w");
    Output* output3= malloc(sizeof(Output*));
    output3->file=output_file;
    return output3;
}

void freeOutput(Output* output)
{
    fclose(output->file);
    free(output);
}

void outputNULL(Output* output3)
{
    fprintf(output3->file,"\n");
}

void outputErros(Output* erros,char* linha)
{
    fprintf(erros->file,"%s",linha);
}

void output1(Output* output1, char* userEmail, char* userNome, char* userApelido,int idade, char* userCountry)
{
    fprintf(output1->file,"%s;%s;%s;%d;%s\n",userEmail,userNome,userApelido, idade,userCountry ); 
}

void output2(Output* output2, char* nome, char* tipo, char* time,char* pais)
{
     fprintf(output2->file,"%s;%s;%s;%s\n",nome,tipo, time, pais);
}


void output3(Output* output3, char* genero, int num)
{

   
        fprintf(output3->file,"%s;%d\n",genero,num);

    
}



