#ifndef IOMANAGER
#define IOMANAGER
#include <stdio.h>
#include <stdlib.h>
FILE* abrirFILE(char* diretoria, char* subdiretoria);
void fecharFILE (FILE* ficheiro);
FILE* abrirFILE_ERROS(char* diretoria);
#endif