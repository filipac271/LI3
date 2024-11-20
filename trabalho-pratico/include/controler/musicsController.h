#ifndef MUSICSCONTROLLER_H
#define MUSICSCONTROLLER_H
#include <glib.h>
#include <stdio.h>
#include "Entitys/musics.h"
#include "controler/artistsController.h"

typedef struct musicData MusicData;



MusicData* musicsFeed(char* diretoria,ArtistsData* artistsData);


void inserir_musica_na_htable(GHashTable* musica, Music* new_music,char* music_id);

Music* lookup_musica(MusicData* controller, char* music_id);

void print_music_entry (gpointer key, gpointer value, gpointer user_data);

void print_all_musics(MusicData* musica);

void destroyMusicTable(MusicData* data);


#endif