#ifndef IOMANAGER
#define IOMANAGER
#include <stdio.h>
#include <stdlib.h>
#include "querie/querie3.h"
typedef struct parser Parser;
typedef struct output Output;

FILE* abrirFILE(char* diretoria, char* subdiretoria);
void fecharFILE (FILE* ficheiro);
FILE* abrirFILE_ERROS(char* diretoria);
Parser* parser(Parser* parserE);
char* pegaLinha(Parser* parserE);
Parser* newParser(char* diretoria,char* subdiretoria);
void freeParser(Parser* parserE);
char** getTokens(Parser * parserE);
char* getLineError( Parser* parserE);
char* getLine (Parser* parserE);


Output* iniciaOutput (char* filename);
void freeOutput(Output* output);
void outputNULL(Output* output3);
void outputErros(Output* erros,char* linha);

void output1(Output* output1, char* userEmail, char* userNome, char* userApelido,int idade, char* userCountry);
void output2(Output* output2, char* nome, char* tipo, char* time,char* pais);
void output3(Output* output3, char* genero, int num);

#endif