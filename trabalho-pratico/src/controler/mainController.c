
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
#include "Input.h"

#include "controler/albumsController.h"

#include "controler/historyController.h"
#include "Entities/history.h"




struct mainController
{
    ArtistsData* artistsController;
    MusicData* musicsController;
    UsersData* usersController;
    AlbumsData* albumsController;
    HistoryData* historyController;

};


MainController* mainFeed(char* diretoria){

    int diretoriaValida = checkDiretoria(diretoria);
    if(!diretoriaValida){
        return NULL;
    }
    MainController* mainData = malloc(sizeof(MainController));

    mainData->artistsController =  artistFeed(diretoria);

    mainData->albumsController = albumsFeed(diretoria,mainData->artistsController);

    mainData->musicsController = musicsFeed(diretoria,mainData->artistsController,mainData->albumsController);

    mainData->usersController = usersFeed(diretoria,mainData->musicsController);

    mainData ->historyController = historyFeed(diretoria, mainData->musicsController, mainData->artistsController,mainData->usersController);



    return mainData;
}


void print_all_Data(MainController* data){
    //Pequena utilização da variavel para tirar o warning de data not being used
    (void)data;

    // print_all_albums(data->albumsController);
    //print_all_artists(data->artistsController);
    //print_all_musics(data->musicsController);
    //print_all_users(data->usersController);
   // print_all_history(data->historyController);

}

void destroyData(MainController* data){
    destroyTableArtist(data->artistsController);
    destroyTableAlbum(data->albumsController);
    destroyMusicData(data->musicsController);
    destroyUsersData(data->usersController);
    destroyHistoryData(data->historyController);
    free(data->usersController);
    free(data->musicsController);
    free(data->albumsController);
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


AlbumsData* getalbumController (MainController* data){
    return data->albumsController;
}

HistoryData* gethistoryController (MainController* data){
    return data->historyController;
}
