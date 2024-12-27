#ifndef ARTISTSCONTROLLER_H
#define ARTISTSCONTROLLER_H
#include <glib.h>
#include <stdlib.h>
#include <stdio.h>
#include "Entitys/artists.h"

typedef struct artistsData ArtistsData;

void inserir_discography_into_artist (ArtistsData* controller, char* music_durationAspas, char* music_artists);

ArtistsData* artistFeed(char* diretoria);

Artist* lookup_artist(ArtistsData* controller, int id);

void print_artist_entry (gpointer key, gpointer value, gpointer user_data);

void print_all_artists(ArtistsData* data);

void destroyTableArtist(ArtistsData* ArtistData);

void fill_filtered_artists(ArtistsData* controller, GArray *array, char *country);

void put_stream_into_Artist (int numartistas, int* arrayArtistas, ArtistsData* controller);

void atualizaAlbuns (char* arrayAlbuns, ArtistsData* controller);


char* getArtistNameControl(ArtistsData* controlador, int id);

char* getArtistCountryControl(ArtistsData* controlador, int id);

char* getArtistTypeControl(ArtistsData* controlador, int id);


int getArtistAlbunsIndividuaisControl(ArtistsData* controlador, int id);


double getArtistProfitsControl(ArtistsData* controlador, int id);

int getArtistDiscographyControl(ArtistsData* controlador, int id);

int isArtistValid (ArtistsData* controlador , int id);


#endif