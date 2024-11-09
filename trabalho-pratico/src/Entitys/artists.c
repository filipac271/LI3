#include "Entitys/artists.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct artists
{
    char* id; //A0000xxx
    char* name;
    char* descriçao;
    float ganho_por_stream;
    char** grupo;
    char* country;
    char* type;
    int numMembrosGrupo;
    int total_discography;
};


// Função para criar um novo artista
Artist* create_artist(char* id, const char* name, char* description, float ganho, char** grupo, char* country, char* type,int numMembros) {
    Artist* new_artist = malloc(sizeof(Artist));
    if(new_artist == NULL){
        fprintf(stderr, "Memory allocation failed for new artist\n");
        exit(1);
    }
    new_artist->id = strdup(id);
    new_artist->name = strdup(name);
    new_artist->descriçao = strdup(description);
    new_artist->ganho_por_stream = ganho;
    new_artist->grupo = malloc(numMembros * sizeof(char*)); 


    for (int i = 0; i < numMembros; i++) {
         new_artist->grupo[i] = strdup(grupo[i]);  // Duplica cada string

    }


    new_artist->country = strdup(country);
    new_artist->type = strdup(type);
    new_artist->numMembrosGrupo=numMembros;
    new_artist->total_discography = 0;


    return new_artist;
}

// Função para liberar memória dos artistas
void free_artist(Artist* artist) {
    if (artist) {
        free(artist->id);
        free(artist->name);
        free(artist->descriçao);
        free(artist->country);

        int i;
        for ( i = 0; i < artist->numMembrosGrupo; i++)
        {
         free(artist->grupo[i]);
        }

        free(artist->grupo);
        free(artist->type);
        free(artist);
    }
}

//Função para printar todas as informações de um artista
void print_artist(Artist* artist) {
    if (artist) {
        printf("ID: %s\n", artist->id);
        printf("Name: %s\n", artist->name);
        printf("Description: %s\n", artist->descriçao);
        printf("Ganho por Stream: %.2f\n", artist->ganho_por_stream);
        printf("Grupo:\n");
        
        if (artist->numMembrosGrupo > 0) {
            for (int i = 0; i < artist->numMembrosGrupo; i++) {
                printf("%s\n", artist->grupo[i]);  // Acessa o membro específico do grupo
            }
        } else {
            printf("SOLO SINGER");
        }

        printf("\n");
        printf("Country: %s\n", artist->country);
        printf("Type: %s\n", artist->type);
        printf("Numero de Membros: %d\n", artist->numMembrosGrupo);
        printf("Total DURATION: %d", artist->total_discography);
        printf("\n");
    } else {
        printf("N tenho nada para printar\n");
    }
}


char* getArtistId(Artist* artista){
    return strdup(artista->id);
}

char* getArtistName(Artist* artista){
    return strdup(artista->name);
}

char* getArtistDescriçao(Artist* artista){
    return strdup(artista->descriçao);
}

float getArtistGanho(Artist* artista){
    return artista->ganho_por_stream;
}

char** getArtistGrupo(Artist* artista){
    return artista->grupo;
}

char* getArtistCountry(Artist* artista){
    return  strdup(artista->country);
}

char* getArtistType(Artist* artista){
    return strdup(artista->type);
}

int getArtistNumMembros(Artist* artista){
    return artista->numMembrosGrupo;
}


//Adicionado ao .h
int getArtistDiscography(Artist* artista){
    return artista->total_discography;
}

void setArtistDiscography(Artist* artista, int discography){
    artista->total_discography += discography;
}