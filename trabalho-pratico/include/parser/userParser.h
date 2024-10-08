#ifndef USERPARSER_H
#define USERPARSER_H

#include <stdio.h>  
#include <glib.h>

char** likedSongs(char* songs, int numberS);
GHashTable* userParser(FILE *file);


#endif