#ifndef ALBUMS_H
#define ALBUMS_H

typedef struct albums Album;

Album* createAlbum(char** tokens);

void freeAlbum (Album* album);

void printAlbum (Album* album);
#endif