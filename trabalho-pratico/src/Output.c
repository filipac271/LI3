#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

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
void output1(Output* output1, char* userEmail, char* userNome, char* userApelido,int idade, char* userCountry, char c)
{
    if (c == 'S') 
    {
        fprintf(output1->file,"%s=%s=%s=%d=%s\n",userEmail,userNome,userApelido, idade,userCountry ); 
    }
    else
    {
        fprintf(output1->file,"%s;%s;%s;%d;%s\n",userEmail,userNome,userApelido, idade,userCountry ); 
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