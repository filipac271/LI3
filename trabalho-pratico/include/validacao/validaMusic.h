#ifndef VALIDAMUSICS_H
#define VALIDAMUSICS_H

#include<glib.h>
#include "controler/artistsController.h"
#include "IOManager.h"

int validaMusic(char* duracaoAspas, char* music_artists,ArtistsData* artistsController, Output* Erros, char* linha) ;

#endif