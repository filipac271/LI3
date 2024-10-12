#ifndef MUSICS_H
#define MUSICS_H
#include <glib.h>

typedef struct music MusicData;

MusicData* new_music(char* id, char* music_title, char* music_artist_id, char* music_duration, char* music_genre, char* music_year, char* music_lyrics);

void free_musica(MusicData* musica);

void print_musicas(MusicData * musica);

GHashTable* iniciar_hash_musica();

void inserir_musica_na_htable(GHashTable* musica, char* music_id, char* music_title, char* music_artist_id, char* music_duration, char* music_genre, char* music_year, char* music_lyrics);

MusicData* lookup_musica(GHashTable* musica, char* music_id);

void print_music_entry (gpointer key, gpointer value, gpointer user_data);

void print_all_musics(GHashTable* musica);

char* get_music_genre (MusicData* music);

#endif