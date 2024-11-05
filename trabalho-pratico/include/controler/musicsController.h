#ifndef MUSICSCONTROLLER_H
#define MUSICSCONTROLLER_H
#include <glib.h>
#include <stdio.h>
#include "Entitys/musics.h"
#include "controler/artistsController.h"

typedef struct musicData MusicData;



MusicData* musicsFeed(FILE* ficheiro,ArtistsData* artistsData);

GHashTable* iniciar_hash_musica();

void inserir_musica_na_htable(GHashTable* musica, Music* new_music,char* music_id);

Music* lookup_musica(GHashTable* musica, char* music_id);

void print_music_entry (gpointer key, gpointer value, gpointer user_data);

void print_all_musics(MusicData* musica);

void destroyMusicTable(MusicData* data);

GHashTable* getMusicsTable(MusicData* data);


GHashTable* iniciar_hash_info();

void inserir_dinfo_into_htable(GHashTable* dinfo, int new_discography, char* artist_id, GHashTable* Artist_Original);

void print_dinfo_entry (gpointer key, gpointer value, gpointer user_data);


void print_all_Dinfos(MusicData* musica);

void destroyDinfoTable(MusicData* data);


GHashTable* getDinfoTable(MusicData* data);

char * getMusica(MusicData* musicController,char* song);

#endif