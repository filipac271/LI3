#ifndef MUSICPARSER_H
#define MUSICPARSER_H

#include <stdio.h>  
#include <glib.h>

char** divideArtists( char* music_artist_id);


GHashTable* parser_musica(FILE *file);


#endif