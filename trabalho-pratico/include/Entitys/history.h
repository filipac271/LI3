#ifndef HISTORY_H
#define HISTORY_H
#include <stdio.h>
#include "controler/usersController.h"
#include "controler/artistsController.h"
#include "controler/musicsController.h"


typedef struct artistahistory UmArtista;

typedef struct domingo Domingo;


void freeUmArtista (UmArtista* artista);

void free_garray_with_data(GArray* array);

void freeDomingo(Domingo* domingo);


Domingo* newDomingo(char* data);

UmArtista* new_umArtista (int artist_id, int segundos);

void inserir_umartista_na_semana(GHashTable* artisthistory, UmArtista* novo_artista, int artist_id);

void new_or_add(Domingo* domingo, char** tokens, MusicData* musicController);

void passa_Domingo_para_garray(Domingo* domingo);

gint compare_seconds(gconstpointer a, gconstpointer b);







GHashTable* get_artisthistorido_dedomingo (Domingo* domingo);

UmArtista* lookup_artista_historico(GHashTable* Artista, int artist_id);

GHashTable* getArtistHistory(Domingo* domingo);

GArray* get_garray_from_domingo (Domingo* domingo);

int get_garray_len (Domingo* domingo);

int get_artist_id_from_garray (UmArtista* artista);

int get_seconds_from_garray (UmArtista* artista);




void print_artisthistory (UmArtista* artista);

void print_garray(GArray* array);

void printf_domingo (Domingo* domingo);

void print_artisthistory_entry(gpointer key, gpointer value, gpointer user_data);

void print_semana_completa(gpointer key, gpointer value, gpointer user_data);



#endif