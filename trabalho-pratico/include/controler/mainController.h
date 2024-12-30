#ifndef MAINCONTROLLER_H
#define MAINCONTROLLER_H
#include <stdio.h>
#include "controler/usersController.h"
#include "controler/artistsController.h"
#include "controler/musicsController.h"
#include "controler/historyController.h"
#include "controler/albumsController.h"


typedef struct mainController MainController;


MainController* mainFeed(char* diretoria);

void destroyData(MainController* data);
void print_all_Data(MainController* data);
UsersData* getUserController(MainController* data);
MusicData* getMusicController (MainController* data);
ArtistsData* getartistController (MainController* data);
HistoryData* gethistoryController (MainController* data);
AlbumsData* getalbumController (MainController* data);
#endif