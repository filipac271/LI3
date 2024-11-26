#ifndef VALIDAUSER_H
#define VALIDAUSER_H


#include <glib.h>
#include"controler/musicsController.h"
#include "Output.h"

int validaUser(char* email, char* date, char* type,MusicData* musicsController,char* songs,int numSongs, Output* Erros, char* linha);


#endif