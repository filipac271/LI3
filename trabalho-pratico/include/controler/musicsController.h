#ifndef MUSICSCONTROLLER_H
#define MUSICSCONTROLLER_H
#include <glib.h>
#include <stdio.h>
#include "Entitys/musics.h"
#include "controler/artistsController.h"
#include "controler/albumsController.h"

typedef struct musicData MusicData;

MusicData* musicsFeed(char* diretoria, ArtistsData* artistsData, AlbumsData* albumData);

Music* lookup_musica(MusicData* controller, int music_id);

void print_music_entry (gpointer key, gpointer value, gpointer user_data);

void print_all_musics(MusicData* musica);

void destroyMusicTable(MusicData* data);

void atualizaStreams (char* idMusica, MusicData* musicController, ArtistsData* artistcontroller);


#endif