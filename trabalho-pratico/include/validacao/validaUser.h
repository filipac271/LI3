#ifndef VALIDAUSER_H
#define VALIDAUSER_H


#include <glib.h>

int validaUser(char* email, char* date, char* type,GHashTable* musicsTable,char** likedSongs,int numSongs);



#endif