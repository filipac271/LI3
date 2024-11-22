#ifndef VALIDAUSER_H
#define VALIDAUSER_H


#include <glib.h>
#include"controler/musicsController.h"
#include "IOManager.h"

int validaUser(char* email, char* date, char* type,MusicData* musicsController,int* liked_songs_id,int SongCount, Output* Erros, char* linha);



#endif