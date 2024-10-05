#ifndef ARTISTSCONTROLLER_H
#define ARTISTSCONTROLLER_H
#include <glib.h>

typedef struct artists ArtistsData;

void insert_artist_into_table(GHashTable* artists_table,char* id, char* name, char* description, float ganho, char** grupo, char* country, char* type);


GHashTable* init_artists_table();


ArtistsData* lookup_artist(GHashTable* artists_table, char* id);

void print_artist_entry (gpointer key, gpointer value, gpointer user_data);
void print_all_artists(GHashTable* artists_table);
void print_artist(ArtistsData* artist);
#endif