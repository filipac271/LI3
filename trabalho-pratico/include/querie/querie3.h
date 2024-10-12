#ifndef QUERIE3_H
#define QUERIE3_H
#include <glib.h>
#include "parser/userParser.h"

typedef struct generoMusica Genero;

void querie3(int num,GHashTable* music, int min , int max, Age* usersByAge);

#endif