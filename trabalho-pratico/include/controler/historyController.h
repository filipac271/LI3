#ifndef HISTORYCONTROLLER_H
#define HISTORYCONTROLLER_H
#include <stdio.h>
#include "controler/usersController.h"
#include "controler/artistsController.h"
#include "controler/musicsController.h"
#include "controler/historyController.h"
#include "Entitys/history.h"


typedef struct historyData HistoryData;

GHashTable* createHistoryTable();

Domingo* lookup_domingo(GHashTable* domingo, char* data);

void newDomingo_orNot(HistoryData* controller, char** tokens, MusicData* musicController);

History* lookup_UserHistory(HistoryData* historyController,int userId);

HistoryData* historyFeed(char* diretoria, MusicData* musicData, ArtistsData* artistData);

int getNumArtistas(HistoryData* historyController,int userId,int posicaoAno);

int getIdArtista(HistoryData* historyController, int user_id, int ano, int i);

int getTempoArtista(HistoryData* historyController, int user_id, int ano, int i);

int getnMusicasArtista(HistoryData* historyController, int user_id, int ano, int i);

int getPosicaoAno(HistoryData* historyController,int user_id, int ano);

int* getNartistasMaisOuvidos(HistoryData* historyController,int user_id,int posicaoAno, int N);

char* getArtistaMaisOuvido(HistoryData* historyController,int user_id,int posicaoAno);

char* getDia(HistoryData*  historyController,int user_id,int ano);

char* getGeneroMaisOuvido(HistoryData* historyController,int user_id,int ano);

int getAlbumFavorito(HistoryData* historyController,int user_id,int ano,AlbumsData* albumController);

char* getHora(HistoryData* historyController,int user_id,int ano);

void destroyHistoryData(HistoryData* data);


void print_all_history (HistoryData* history);

#endif