#include "Entitys/artists.h"
#include "utilidades.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

struct artists
{
    int id; 
    char* name;
    //char* descriçao;
    float ganho_por_stream;
    int* grupo;
    char* country;
    char* type;
    int numMembrosGrupo;
    int total_discography;
};




// Função para criar um novo artista
Artist* create_artist(char** tokens) {
    Artist* new_artist = malloc(sizeof(Artist));
    if(new_artist == NULL){
        fprintf(stderr, "Memory allocation failed for new artist\n");
        exit(1);
    }

    //O remove quotes já manda uma cópia

    char* ganhos = remove_quotes(tokens[3]);
    float clean_ganhos = atof(ganhos);

    char* grupo = tokens[4];
    int numMembros = calculate_num_members(grupo); 
    int* grupos_id = divideGroup(grupo, numMembros);
    
    // char* idChar = remove_quotes(tokens[0]);
    new_artist->id = transformaIds(tokens[0]);
    //    free(idChar);    

    new_artist->name = remove_quotes(tokens[1]);
    //new_artist->descriçao = remove_quotes(tokens[2]);
    new_artist->ganho_por_stream = clean_ganhos;  
    new_artist->grupo = malloc(numMembros * sizeof(int)); 
    for (int i = 0; i < numMembros; i++)
    {
        new_artist->grupo[i] = grupos_id[i]; 
    }
    
    new_artist->country = remove_quotes(tokens[5]);
    new_artist->type = remove_quotes(tokens[6]);
    new_artist->numMembrosGrupo=numMembros;
    new_artist->total_discography = 0;
    free(ganhos);
    freeArray(grupos_id);

    return new_artist;
}

// Função para liberar memória dos artistas
void free_artist(Artist* artist) {
    if (artist) {
        free(artist->name);
        //free(artist->descriçao);
        free(artist->country);

        free(artist->grupo);
        free(artist->type);
        free(artist);
    }
}

//Função para printar todas as informações de um artista
void print_artist(Artist* artist) {
    if (artist) {
        printf("ID: %d\n", artist->id);
        printf("Name: %s\n", artist->name);
        //printf("Description: %s\n", artist->descriçao);
        printf("Ganho por Stream: %.2f\n", artist->ganho_por_stream);
        printf("Grupo:");
        
        if (artist->numMembrosGrupo > 0) {
            for (int i = 0; i < artist->numMembrosGrupo; i++) {
                printf("%d;", artist->grupo[i]);  // Acessa o membro específico do grupo
            }
                printf("\n");
        } else {
            printf("SOLO SINGER\n");
        }

        printf("Country: %s\n", artist->country);
        printf("Type: %s\n", artist->type);
        printf("Numero de Membros: %d\n", artist->numMembrosGrupo);
        printf("Total DURATION: %d\n", artist->total_discography);
        printf("\n");
    } else {
        printf("N tenho nada para printar\n");
    }
}


int getArtistId(Artist* artista){
    return artista->id;
}

char* getArtistName(Artist* artista){
    return strdup(artista->name);
}

// char* getArtistDescriçao(Artist* artista){
//     return strdup(artista->descriçao);
// }

float getArtistGanho(Artist* artista){
    return artista->ganho_por_stream;
}

// char** getArtistGrupo(Artist* artista){
//     return artista->grupo;
// }

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