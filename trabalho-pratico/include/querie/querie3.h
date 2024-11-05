#ifndef QUERIE3_H
#define QUERIE3_H
#include <glib.h>
#include "controler/usersController.h"
#include "utilidades.h"
#include "controler/musicsController.h"

typedef struct generoMusica Genero;


void querie3(int num,MusicData* musicController, int min , int max, UsersData* userController);

#endif