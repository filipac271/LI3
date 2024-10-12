#ifndef USERPARSER_H
#define USERPARSER_H

#include <stdio.h>  
#include <glib.h>

typedef struct ageUsers Age;


Age* addLikedSongs( Age* songsByAge, int idade,char** newSongs,int newSongCount) ;
char** likedSongs(char* songs, int numberS);
GHashTable* userParser(FILE *file, Age* songsByAge);



#endif