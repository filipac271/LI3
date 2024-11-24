#ifndef ARTISTS_H
#define ARTISTS_H

typedef struct artists Artist;

int getArtistId(Artist* artista);
char* getArtistName (Artist* artista);
//char* getArtistDescriçao (Artist* artista);
float getArtistGanho(Artist* artista);
//char** getArtistGrupo (Artist* artista);
char* getArtistCountry (Artist* artista);
char* getArtistType (Artist* artista);
int getArtistNumMembros (Artist* artista);
int getArtistDiscography (Artist* artista);
void setArtistDiscography (Artist* artista, int discography);

Artist* create_artist(char** tokens);
void print_artist(Artist* artist);
void free_artist(Artist* artist);

#endif