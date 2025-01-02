#ifndef QUERIE2_H
#define QUERIE2_H
#include <glib.h>
#include "controler/artistsController.h"
#include "utilidades.h"

typedef struct discografia Discography;

Discography* create_discography(int artist_id, int segundos);


void querie2(ArtistsData* ArtistController, char* line, int i);

#endif

