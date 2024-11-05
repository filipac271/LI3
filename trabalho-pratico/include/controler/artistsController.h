#ifndef ARTISTSCONTROLLER_H
#define ARTISTSCONTROLLER_H
#include <glib.h>
#include <stdlib.h>
#include <stdio.h>
#include "Entitys/artists.h"

typedef struct artistsData ArtistsData;

void insert_artist_into_table(GHashTable* artists_table,Artist* newArtist, char* id);
void inserir_discography_into_artist (ArtistsData* controller, int discography, char* artist_id);

ArtistsData* artistFeed(char* diretoria);


GHashTable* init_artists_table();

Artist* create_artist(char* id, const char* name, char* description, float ganho, char** grupo, char* country, char* type,int numMembros);

Artist* lookup_artist(ArtistsData* controller, char* id);

void print_artist_entry (gpointer key, gpointer value, gpointer user_data);
void print_all_artists(ArtistsData* data);
void destroyTableArtist(ArtistsData* ArtistData);



void fill_filtered_artists(ArtistsData* controller, GArray *array, char *country);

#endif