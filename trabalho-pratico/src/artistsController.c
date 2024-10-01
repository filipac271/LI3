#include <glib.h>
#include "artistsController.h"


struct artists
{
    char* id;
    char* name;
    char* descriçao;
    float ganho_por_stream;
    char** grupo;
    char* country;
    char* type;    

};


// Função para criar um novo artista
ArtistsData* create_artist(int id, const char* name, const char* description, float ganho, char** grupo, const char* country, const char* type) {
    struct artists* new_artist = malloc(sizeof(struct artists));
    new_artist->id = strdup(id);
    new_artist->name = strdup(name);
    new_artist->descriçao = strdup(description);
    new_artist->ganho_por_stream = ganho;
    new_artist->grupo = grupo; // Aqui você deve cuidar da alocação
    new_artist->country = strdup(country);
    new_artist->type = strdup(type);
    return new_artist;
}


// Função para liberar memória dos artistas
void free_artist(ArtistsData* artist) {
    if (artist) {
        free(artist->name);
        free(artist->descriçao);
        free(artist->country);
        free(artist->type);
        free(artist);
    }
}