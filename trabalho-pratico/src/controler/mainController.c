
#include <glib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/resource.h>


#include "controler/mainController.h"
#include "controler/artistsController.h"
#include "controler/musicsController.h"
#include "controler/usersController.h"
#include "controler/historyController.h"
#include "Entitys/history.h"



struct mainController
{
    ArtistsData* artistsController;
    MusicData* musicsController;
    UsersData* usersController;
    HistoryData* historyController;
};


MainController* mainFeed(char* diretoria){
    MainController* mainData = malloc(sizeof(MainController));


    mainData->artistsController =  artistFeed(diretoria);


    mainData->musicsController = musicsFeed(diretoria,mainData->artistsController);


    mainData->usersController = usersFeed(diretoria,mainData->musicsController);

    mainData ->historyController = historyFeed(diretoria, mainData->musicsController);


    return mainData;
}


void print_all_Data(MainController* data){
    //Pequena utilização da variavel para tirar o warning de data not being used
    (void)data;
    //print_all_artists(data->artistsController);
    //print_all_musics(data->musicsController);
    //print_all_users(data->usersController);
   // print_all_history(data->historyController);
}


void destroyData(MainController* data){
    destroyTableArtist(data->artistsController);
    destroyMusicTable(data->musicsController);
    destroyUsersData(data->usersController);
    destroyHistoryData(data->historyController);
    free(data->usersController);
    free(data->musicsController);
    free(data->artistsController);
    free(data->historyController);
    free(data);
}

UsersData* getUserController(MainController* data){
    return data->usersController;
}

MusicData* getMusicController (MainController* data){
    return data->musicsController;

}

ArtistsData* getartistController (MainController* data){
    return data->artistsController;
}

HistoryData* gethistoryController (MainController* data){
    return data->historyController;
}