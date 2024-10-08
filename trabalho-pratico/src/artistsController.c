#include <glib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "artistsController.h"

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
};

// Função para imprimir os dados de um artista
void print_artist(ArtistsData* artist) {
    if (artist) {
        printf("ID: %s\n", artist->id);
        printf("Name: %s\n", artist->name);
        printf("Description: %s\n", artist->descriçao);
        printf("Ganho por Stream: %.2f\n", artist->ganho_por_stream);
        printf("Grupo:\n");
        
        if(artist->numMembrosGrupo > 0){
          for (int i = 0; i < artist->numMembrosGrupo; i++) {

                printf("%s\n", artist->grupo[i]);
            
        }  
        }else printf("SOLO SINGER");
        
        
        printf("\n");
        
        printf("Country: %s\n", artist->country);
        printf("Type: %s\n", artist->type);
        printf("Numero de Membros: %d\n",artist->numMembrosGrupo);
        printf("\n");
    }
    else printf("N tenho nada para printar\n");
}

// Função para criar um novo artista
ArtistsData* create_artist(char* id, const char* name, char* description, float ganho, char** grupo, char* country, char* type,int numMembros) {
    ArtistsData* new_artist = malloc(sizeof(struct artists));
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


    return new_artist;
}

// Função para liberar memória dos artistas
void free_artist(ArtistsData* artist) {
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

// Função para inicializar a hash table
GHashTable* init_artists_table() {
    // Criar a hash table que mapeia strings (ID) para structs de artistas
    GHashTable* artists_table = g_hash_table_new_full(g_str_hash, g_str_equal, free, (GDestroyNotify)free_artist);

    // Verificar se a hash table foi criada corretamente
    if (artists_table == NULL) {
        printf("Erro: Hash table dos artistas não foi criada.\n");
        exit(1);
    } else {
        printf("Hash table dos artistas criada com sucesso.\n");
    }

    return artists_table;
}
// Função para inserir um artista na hash table
void insert_artist_into_table(GHashTable* artists_table, ArtistsData* new_artist,char* id) {

    // Criar um novo artista
    //ArtistsData* new_artist = create_artist(id, name, description, ganho, grupo, country, type,numMembros);
    
    // Inserir na hash table usando o id como chave
    g_hash_table_insert(artists_table, strdup(id), new_artist);
    //printf("Artista inserido:%s\n",new_artist->id);
    //print_artist(new_artist);


}

// Função para procurar um artista pelo ID
ArtistsData* lookup_artist(GHashTable* artists_table, char* id) {
    return g_hash_table_lookup(artists_table, id);
}



// Função callback para imprimir a hash table
void print_artist_entry (gpointer key, gpointer value, gpointer user_data) {
    char* id = (char*)key;
    ArtistsData* artist = (ArtistsData*)value;

    print_artist(artist);
}

// Função para imprimir toda a hash table
void print_all_artists(GHashTable* artists_table) {
    printf("----- Hash Table de Artistas -----\n");
    sleep(3);
    g_hash_table_foreach(artists_table, print_artist_entry, NULL);
    sleep(3);
    printf("----- Fim da Hash Table -----\n");
}
