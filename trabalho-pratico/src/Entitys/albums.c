#include "Entitys/albums.h"
#include "utilidades.h"

#include "stdlib.h"
#include "stdio.h"

struct albums
{
    int id;
    char* title;
    int* artistsIds;
    int year;
    //char* producers;
    int numArtists;
};



Album* createAlbum(char** tokens){

    Album* newAlbum = malloc(sizeof(Album));

    newAlbum->id = transformaIds(tokens[0]);
    newAlbum->title = remove_quotes(tokens[1]);

    int numArtists = calculate_num_members(tokens[2]);
    int* artistsList = divideArray(tokens[2],numArtists);

    newAlbum->artistsIds = malloc(numArtists * sizeof(int));
    for (int i = 0; i < numArtists; i++)
    {
        newAlbum->artistsIds[i] = artistsList[i];
    }

    char* clearYear = remove_quotes(tokens[3]);
    int intYear = atoi(clearYear);
    newAlbum->year = intYear;
    
    newAlbum->numArtists = numArtists;

    free(clearYear);
    freeArray(artistsList);

    return newAlbum;
}

char* getAlbumName(Album* album)
{
    return strdup(album->title); //////Falta Copia
}

void freeAlbum (Album* album){
    free(album->title);
    free(album->artistsIds);
    free(album);
}


void printAlbum (Album* album){

    printf("Id do album:%d\n",album->id);
    printf("Album title:%s\n",album->title);
    printf("Artistas :\n");

    for(int i=0; i<album->numArtists;i++)
    {
    printf("%d\t ",album->artistsIds[i]);
    }
    printf("\n");
    printf("Ano do lançamento do album:%d\n",album->year);

    printf("\n"); 
    
}