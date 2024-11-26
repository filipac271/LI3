#ifndef IOMANAGER
#define IOMANAGER
#include <stdio.h>
#include <stdlib.h>

typedef struct parser Parser;


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




int contar_linhas( char *nome_ficheiro);

#endif