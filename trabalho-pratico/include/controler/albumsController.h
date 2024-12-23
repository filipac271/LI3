#ifndef ALBUNSCONTROLLER_H
#define ALBUNSCONTROLLER_H
#include <glib.h>
#include <stdlib.h>
#include <stdio.h>
#include "Entitys/albums.h"
#include "controler/artistsController.h"

typedef struct albumsData AlbumsData;


AlbumsData* albumsFeed(char* diretoria, ArtistsData* artistController);


void destroyTableAlbum(AlbumsData* AlbumData);

Album* lookup_album(AlbumsData* controller, int id);

void print_all_albums(AlbumsData* data);

#endif