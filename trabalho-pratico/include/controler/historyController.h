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


HistoryData* historyFeed(char* diretoria, MusicData* musicData, ArtistsData* artistData);

void destroyHistoryData(HistoryData* data);


void print_all_history (HistoryData* history);
GHashTable* get_Domingo_from_HD (HistoryData* data);

#endif