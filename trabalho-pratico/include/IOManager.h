#ifndef IOMANAGER
#define IOMANAGER
#include <stdio.h>
#include <stdlib.h>

typedef struct parser Parser;

FILE* abrirFILE(char* diretoria, char* subdiretoria);
void fecharFILE (FILE* ficheiro);
FILE* abrirFILE_ERROS(char* diretoria);
Parser* parser(Parser* parserE);
char* pegaLinha(char* diretoria, char* subdiretoria);
Parser* newParser(char* diretoria,char* subdiretoria);
void freeParser(Parser* parserE);
char** getTokens(Parser * parserE);
long getLastPosition(Parser *parserE);
#endif