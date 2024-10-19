
#include <glib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "controler/mainController.h"
#include "controler/artistsController.h"
#include "controler/musicsController.h"
#include "controler/usersController.h"


struct mainController
{
    ArtistsData* artistsController;
    MusicData* musicsController;
    UsersData* usersController;
};


MainController* mainFeed(FILE** dataset){
    MainController* mainData = malloc(sizeof(MainController));


    mainData->artistsController =  artistFeed(dataset[0]);
    mainData->musicsController = musicsFeed(dataset[1],mainData->artistsController);
    mainData->usersController = usersFeed(dataset[2],mainData->musicsController);




    return mainData;
}


void print_all_Data(MainController* data){
    //print_all_artists(data->artistsController);
    //print_all_musics(data->musicsController);
    //print_all_users(data->usersController);
}


void destroyData(MainController* data){
    destroyTableArtist(data->artistsController);
    destroyMusicTable(data->musicsController);
    destroyUsersData(data->usersController);
    free(data->usersController);
    free(data->musicsController);
    free(data->artistsController);
    free(data);
}

UsersData* getUserController(MainController* data){
    return data->usersController;
}

MusicData* getMusicController (MainController* data){
    return data->musicsController;

}