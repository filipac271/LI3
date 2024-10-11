#ifndef MUSICS_H
#define MUSICS_H
#include <glib.h>

typedef struct music MusicData;

int contar_elementos(char *str);


MusicData* new_music(char* music_id, char* music_title, char** music_artist_id, char* music_duration, char* music_genre, char* music_year, char* music_lyrics, int num_artists);

void free_musica(MusicData* musica);

void print_musicas(MusicData * musica);

GHashTable* iniciar_hash_musica();

void inserir_musica_na_htable(GHashTable* musica, char* music_id, char* music_title, char** music_artist_id, char* music_duration, char* music_genre, char* music_year, char* music_lyrics, int num_artist_id);

MusicData* lookup_musica(GHashTable* musica, char* music_id);

void print_music_entry (gpointer key, gpointer value, gpointer user_data);

void print_all_musics(GHashTable* musica);

char* get_music_id (MusicData* music);

char* get_music_title (MusicData* music);

char* get_music_artist_id (MusicData* music);

char* get_music_duration (MusicData* music);

int duration_to_seconds(char* music_duration);

int get_music_duration_seconds (MusicData* musica);

char* get_music_genre (MusicData* music);

char* get_music_year (MusicData* music);

char* get_music_lyrics (MusicData* music);





#endif