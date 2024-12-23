#ifndef HISTORY_H
#define HISTORY_H
#include <stdio.h>
#include "controler/usersController.h"
#include "controler/artistsController.h"
#include "controler/musicsController.h"


typedef struct artistahistory UmArtista;

typedef struct domingo Domingo;

Domingo* newDomingo(char* data);

UmArtista* new_umArtista (int artist_id, int segundos);

void inserir_umartista_na_semana(GHashTable* artisthistory, UmArtista* novo_artista, int artist_id);

void new_or_add(Domingo* domingo, char**tokens, MusicData* musicController);

void freeDomingo(Domingo* domingo);

void freeUmArtista (UmArtista* artista);


void print_artisthistory (UmArtista* artista);

void printf_domingo (Domingo* domingo);

void print_artisthistory_entry(gpointer key, gpointer value, gpointer user_data);

GHashTable* getArtistHistory(Domingo* domingo);

UmArtista* lookup_artista_historico(GHashTable* Artista, int artist_id);

void destroy_history(Domingo* domingo);

GHashTable* get_artisthistorido_dedomingo (Domingo* domingo);

void print_semana_completa (Domingo* domingo);


char* get_history_data (Domingo* domingo);

int get_usado_from_artist (UmArtista* artista);

int get_id_from_Umartista (UmArtista* artista);

int get_total_de_segundos_from_Umartista (UmArtista* artista);

void set_usado_to_used (UmArtista* artista);


#endif