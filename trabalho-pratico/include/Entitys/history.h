#ifndef HISTORY_H
#define HISTORY_H
#include <stdio.h>
#include "controler/usersController.h"
#include "controler/artistsController.h"
#include "controler/musicsController.h"


typedef struct artistahistory UmArtista;

typedef struct domingo Domingo;


typedef struct genero Generos;
typedef struct album Albuns;
typedef struct artista Artistas;
typedef struct dia Dia;

typedef struct ano Ano;
typedef struct userHistory History;

int IdArtista(History* userHistory, int ano, int i);

int TempoArtista(History* userHistory, int ano, int i);

int nMusicasArtista(History* userHistory, int ano, int i);

int* NartistasMaisOuvidos(History* userHistory,int pAno, int N);

char* ArtistaMaisOuvido(History* userHistory,int anoP);

char* HoraMaisAudicoes(History* userHistory,int anoP);

int AlbumFavorito(History* userHistory,int anoP, AlbumsData* albumController);

char* GeneroMaisOuvido(History* userHistory, int anoP);

char* DataMaisMusicas(History* userHistory,int anoP);

int procuraAno(History* history, int ano);

History* adicionaUserHistory(History* userHistory, MusicData* musicData,int musicId,int ano,int mes,int dia,int hora,int duration);

History* inicializaUserHistory(int userId,MusicData* musicData,int musicId,int ano,int mes, int dia,int hora,int duration);

History * lookup_UserHistory(GHashTable* history,int userId);


void freeArtistas( Artistas* artista);

void freeUserHistory(History* history);

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


#endif