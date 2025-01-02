#ifndef VALIDAMUSICS_H
#define VALIDAMUSICS_H
#include "controler/artistsController.h"
#include "controler/albumsController.h"
#include "Output.h"

int validaMusic(char* duracaoAspas, char* music_artists,ArtistsData* artistsController, Output* Erros, char* linha, AlbumsData* albumController,char* albumId);

#endif