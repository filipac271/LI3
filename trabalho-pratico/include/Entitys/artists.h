#ifndef ARTISTS_H
#define ARTISTS_H

typedef struct artists Artist;

char* getArtistId(Artist* artista);
char* getArtistName (Artist* artista);
char* getArtistDescriçao (Artist* artista);
float getArtistGanho(Artist* artista);
char** getArtistGrupo (Artist* artista);
char* getArtistCountry (Artist* artista);
char* getArtistType (Artist* artista);
int getArtistNumMembros (Artist* artista);

Artist* create_artist(char* id, const char* name, char* description, float ganho, char** grupo, char* country, char* type,int numMembros);
void print_artist(Artist* artist);
void free_artist(Artist* artist);

#endif