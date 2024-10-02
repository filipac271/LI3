#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "mainParser.h"
#include <glib.h>
#include "musicsController.h"


struct music{
  char *music_id;
  char *music_title;
  char *music_artist_id;
  char *music_duration;
  char *music_genre;
  char *music_year;
  char *music_lyrics;
};

//alocar memoria??

//passar as coisas para a struct

MusicData* new_music(char* music_id, char* music_title, char* music_artist_id, char* music_duration, char* music_genre, char* music_year, char* music_lyrics){
  MusicData* n_music = malloc(sizeof(struct music));
    if (n_music == NULL) {
        fprintf(stderr, "Memory allocation failed for new music\n");
        exit(1);
    }

  n_music->music_id = strdup(music_id);
  n_music->music_title = strdup(music_title);
  n_music->music_artist_id = strdup(music_artist_id);
  n_music->music_duration = strdup(music_duration);
  n_music->music_genre = strdup(music_genre);
  n_music->music_year = strdup(music_year);
  n_music->music_lyrics = strdup(music_lyrics);

  if (!n_music->music_id || !n_music->music_title || !n_music->music_artist_id || !n_music->music_duration || !n_music->music_genre || !n_music->music_lyrics) {
        fprintf(stderr, "Memory allocation failed for one or more fields in new_music\n");
        free_musica(n_music);
        exit(1);
    }

  return n_music;

}

void free_musica(MusicData* musica) {
    if (musica) {

        free(musica->music_id);
        free(musica->music_title);
        free(musica->music_artist_id);
        free(musica->music_duration);
        free(musica->music_genre);
        free(musica->music_year);
        free(musica->music_lyrics);

        free(musica);
    }
}

//acabar esta amanha
void print_musicas(MusicData * musica){
  if(musica){
    printf("ID_MUSIC: %s\n", musica->music_id);
    printf("MUSIC_TITLE: %s\n", musica->music_title);
    printf("MUSIC_ARTIST: %s\n", musica->music_artist_id);
    printf("MUSIC_DURATION: %s\n", musica->music_duration);
    printf("MUSIC_GENRE: %s\n", musica->music_genre);
    printf("MUSIC_YEAR: %s\n", musica->music_year);
    printf("MUSIC_LYRICS: %s\n", musica->music_lyrics);
  }
}


GHashTable* iniciar_hash_musica(){
  GHashTable* hash_musica = g_hash_table_new_full(g_str_hash, g_str_equal, free, (GDestroyNotify)free_musica);

  if(hash_musica == NULL){
    printf("Erro: Hash table musica não foi criada.\n");
    exit(1);
  } else {
    printf("Hash table musica criada com sucesso.\n");
  }
  return(hash_musica);
}
//
void inserir_musica_na_htable(GHashTable* musica, char* music_id, char* music_title, char* music_artist_id, char* music_duration, char* music_genre, char* music_year, char* music_lyrics){
  MusicData* nova_musica = new_music(music_id, music_title, music_artist_id, music_duration, music_genre, music_year, music_lyrics);

  g_hash_table_insert(musica, strdup(music_id), nova_musica);
  //ver se depois é preciso adicionar prints
    

}

MusicData* lookup_musica(GHashTable* musica, char* music_id){
  return g_hash_table_lookup(musica, music_id);
}


// Função callback para imprimir a hash table
void print_music_entry (gpointer key, gpointer value, gpointer user_data) {
    char* id = (char*)key;
    MusicData* music = (MusicData*)value;

    print_musicas(music);
}

// Função para imprimir toda a hash table
void print_musics(GHashTable* musica) {
    printf("----- Hash Table de Artistas -----\n");
    sleep(3);
    g_hash_table_foreach(musica, print_music_entry, NULL);
    printf("----- Fim da Hash Table -----\n");
}