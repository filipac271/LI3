#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include"Entitys/history.h"

#include "Output.h"
#include "Input.h"

struct output
{
    FILE* file;
};

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
void output1(Output* output1, void* arg1, void* arg2, void* arg3,void* arg4, void* arg5, char c,int isArtist)
{

     if (isArtist) {
        if (c == 'S') {
            fprintf(output1->file, "%s=%s=%s=%d=%.2f\n", (char*)arg1,(char*) arg2, (char*)arg3, *((int*) arg4),*((double*) arg5));
        } else {
            fprintf(output1->file, "%s;%s;%s;%d;%.2f\n", (char*)arg1,(char*) arg2, (char*)arg3, *((int*) arg4),*((double*) arg5));
        }
    } else {
        // Output para usuário
        if (c == 'S') {
            fprintf(output1->file, "%s=%s=%s=%d=%s\n", (char*)arg1,(char*) arg2, (char*)arg3, *((int*) arg4),(char*) arg5);
        } else {
            fprintf(output1->file, "%s;%s;%s;%d;%s\n",(char*) arg1,(char*) arg2,(char*) arg3, *((int*) arg4),(char*) arg5);
        }
    }
   
}

//Função de output da Querie 2
void output2(Output* output2, char* nome, char* tipo, char* time,char* pais, char c)
{
    if( c == 'S')
    {
        fprintf(output2->file,"%s=%s=%s=%s\n",nome,tipo, time, pais);
    }
    else
    {
        fprintf(output2->file,"%s;%s;%s;%s\n",nome,tipo, time, pais);
    }
    
}

//Função de output da Querie 3
void output3(Output* output3, char* genero, int num, char c)
{
    if ( c == 'S')
    {
        fprintf(output3->file,"%s=%d\n",genero,num); 
    }
    else
    {
        fprintf(output3->file,"%s;%d\n",genero,num);  
    }
    
}



//Função de output da Querie 5
void output5(Output* output5, char** usernames,int numrecomendacoes)
{
        for (int i = 0; i < numrecomendacoes; i++)
        {
            fprintf(output5->file,"%s\n",usernames[i]); 
        }
}

//Função de output da Query 4
//name;type;count_top_10
void output4(Output* output4, char* name, char* type, int num, char c){
    if ( c == 'S')
    {
        fprintf(output4->file,"%s=%s=%d\n",name, type, num); 
    }
    else
    {
        fprintf(output4->file,"%s;%s;%d\n",name, type, num);  
    }
}



void output6(char c, Output* output6, char* tempoAudicao,int nMusicas,char* artistId,char* data,char* genero,char* album, char* hora,int N)
{
      if ( c == 'S')
    {
        if(N==0)
        {
            fprintf(output6->file,"%s=%d=%s=%s=%s=%s=%s\n",tempoAudicao,nMusicas,artistId,data,genero,album,hora); 
        }
        else if( N==1)
        {
            fprintf(output6->file,"%s=%d=%s\n",artistId, nMusicas,tempoAudicao); 
        }
        
    }
    else
    {
          if(N==0)
        {
            fprintf(output6->file,"%s;%d;%s;%s;%s;%s;%s\n",tempoAudicao,nMusicas,artistId,data,genero,album,hora); 
        }
        else if( N==1)
        {
            fprintf(output6->file,"%s;%d;%s\n",artistId, nMusicas,tempoAudicao); 
        }
          
    }
    
}

