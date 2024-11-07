#include "Entitys/artists.h"
#include "controler/artistsController.h"
#include "controler/mainController.h"
#include "validacao/validaArtista.h"
#include "utilidades.h"
#include "IOManager.h"

#include <glib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

struct artistsData{
    GHashTable* artistsTable;
};

ArtistsData* artistFeed(char* diretoria) {

    ArtistsData* AData = malloc(sizeof(ArtistsData));  // Corrigido: alocando corretamente o tamanho de `ArtistsData`
  
      char *filename = malloc(sizeof(char) * 256);
    sprintf(filename, "resultados/artists_errors.csv");
    Output * Erros= iniciaOutput(filename);
    free(filename);

    
    AData->artistsTable = init_artists_table();
     Parser* parserE= newParser(diretoria,"artists.csv");
    // Ignorar a primeira linha

    char* linha= pegaLinha(parserE);
    
   outputErros(Erros,linha);
    

    
    while (1) {
        
        
        parserE= parser(parserE);
     if (getTokens(parserE)==NULL) 
     {
          freeParser(parserE); break;
     }
    
        char** tokens = getTokens(parserE);
      
        // // Atualizar o lineOutput em cada iteração
        // char lineOutput[2048];
        // strncpy(lineOutput, get, 2048);  // Copia a linha para o buffer local
        // lineOutput[2048 - 1] = '\0';  // Garante a terminação da string

                                                        // Aqui os tokens devem corresponder à ordem dos dados no arquivo
                                                        char* id = remove_quotes(tokens[0]);
                                                        char* name = remove_quotes(tokens[1]);
                                                        char* description = remove_quotes(tokens[2]);
                                                        char* ganhos = remove_quotes(tokens[3]);
                                                        float clean_ganhos = atof(ganhos);
                                                        char* grupo = tokens[4];
                                                        char* country = remove_quotes(tokens[5]);
                                                        char* type = remove_quotes(tokens[6]);
        
        char* linhaE=getLinha(parserE);
       
        int isValid = validaArtista(grupo, type,linhaE, Erros);
        
        if (isValid) {
            int numMembros = 1;
            if (strcmp(grupo, "\"[]\"") == 0) {
                numMembros = 0;
            } else {
                // Conta o número de membros do grupo
                for (int i = 2; grupo[i] != '\0'; i++) {
                    if (grupo[i] == ',') numMembros++;
                }
            }
         
            
            char** grupos_id = divideGroup(grupo, numMembros);    

            Artist* newArtist = create_artist(id, name, description, clean_ganhos, grupos_id, country, type, numMembros);
            
            // Insere os dados na hash table
            insert_artist_into_table(AData->artistsTable, newArtist, id);

    
            free(grupos_id);

        }
       
        // Libera as strings alocadas com remove_quotes
        freeCleanerArtist(id, name, description, ganhos, country, type);
   
    }
     printf("FIM DE CICLO\n");
    // Libera a memória alocada por getline
    free(linha);
    freeOutput(Erros);
   
   
    return AData;
}



void inserir_discography_into_artist (ArtistsData* controller, int discography, char* artist_id){
    Artist * artista_atual = g_hash_table_lookup(controller->artistsTable, artist_id);

    setArtistDiscography(artista_atual, discography);
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

void destroyTableArtist(ArtistsData* ArtistData){
    g_hash_table_destroy(ArtistData->artistsTable);
    printf("Destrui artistaData\n");
}
// Função para inserir um artista na hash table
void insert_artist_into_table(GHashTable* artists_table, Artist* new_artist,char* id) {

    // Criar um novo artista
    //Artist* new_artist = create_artist(id, name, description, ganho, grupo, country, type,numMembros);
    
    // Inserir na hash table usando o id como chave
    g_hash_table_insert(artists_table, strdup(id), new_artist);
    //printf("Artista inserido:%s\n",new_artist->id);
    //print_artist(new_artist);


}

// Função para procurar um artista pelo ID
Artist* lookup_artist(ArtistsData* controller, char* id) {
    return g_hash_table_lookup(controller->artistsTable, id);
}





void print_artist_entry (gpointer key, gpointer value, gpointer user_data) {
    if (key == NULL || value == NULL) {
        printf( "Chave ou valor nulo encontrado.\n");
        sleep(2);
        return;
    }

    char* id = (char*)key;
    Artist* artist = (Artist*)value;

    print_artist(artist);
}

// Função para imprimir toda a hash table
void print_all_artists(ArtistsData* data) {
    printf("----- Hash Table de Artistas -----\n");
    sleep(3);
    g_hash_table_foreach(data->artistsTable, print_artist_entry, NULL);
    sleep(3);
    printf("----- Fim da Hash Table -----\n");
}
/*
GHashTable* getArtistsTable (ArtistsData* data){
    return data->artistsTable;
}*/


void fill_filtered_artists(ArtistsData* controller, GArray *array, char *country) {
    GHashTableIter iter;
    gpointer key, value;

    g_hash_table_iter_init(&iter, controller->artistsTable);
    while (g_hash_table_iter_next(&iter, &key, &value)) {
        Artist* artist_to_filter = value;
        char* pais = getArtistCountry(artist_to_filter);
        if (country == NULL || strcmp(country, "") == 0 || strcmp(pais, country) == 0) {
            g_array_append_val(array, artist_to_filter);
        }
        free(pais);
    }
}