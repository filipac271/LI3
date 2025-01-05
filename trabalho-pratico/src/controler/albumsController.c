#include "utilidades.h"
#include "Output.h"
#include "Input.h"
#include "Entitys/albums.h"
#include "controler/albumsController.h"
#include "controler/artistsController.h"

#include <glib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

struct albumsData{
    GHashTable* albumsTable;
};

// Função para inicializar a hash table
GHashTable* init_albums_table() {
    
    // A key da Hash Table é o ID  dos albuns
    GHashTable* albuns_table = g_hash_table_new_full(g_int_hash, g_int_equal, free, (GDestroyNotify)freeAlbum);

    // Verificar se a hash table foi criada corretamente
    if (albuns_table == NULL) {
        printf("Erro: Hash table dos albuns não foi criada.\n");
        exit(1);
    } else {
        printf("Hash table dos albuns criada com sucesso.\n");
    }

    return albuns_table;

}

// Função para inserir um album na hash table usando o id como chave
void insert_albums_into_table(GHashTable* albuns_table,Album* newAlbum ,int id) {
    int* key = malloc(sizeof(int));  // Aloca memória para a chave
    *key = id;
    g_hash_table_insert(albuns_table, key, newAlbum);
}

AlbumsData* albumsFeed(char* diretoria, ArtistsData* artistController) {

    AlbumsData* ALData = malloc(sizeof(AlbumsData)); 
    if(ALData == NULL){
        fprintf(stderr,"Alocação de memória do AlbumsController não foi bem sucedido");
        exit(1);
    }  
 
    ALData->albumsTable = init_albums_table();
    //Inicia o Parser e abre o ficheiro "albums.csv" do dataset
    Parser* parserE= newParser(diretoria,"albums.csv");
    // Ler a primeira linha do ficheiro  
    char* linha= pegaLinha(parserE);
    free(linha);

    while (1) {  
        parserE= parser(parserE);
    
        char** tokens = getTokens(parserE);

        if (tokens==NULL) {

             // Fecha o ficheiro guardado no Parser e liberta a memória alocada neste
              freeParser(parserE); break;
        }
    
        Album* newAlbum = createAlbum(tokens);
        // Insere os dados na hash table
        insert_albums_into_table(ALData->albumsTable, newAlbum , transformaIds(tokens[0]));
        atualizaAlbuns(tokens[2],artistController);    

        free(getLineError(parserE));
        free(getLine(parserE));
    
    }     
    return ALData;
}

// Função para procurar um album pelo id (chave da hash table)
Album* lookup_album(AlbumsData* controller, int id) {

    return g_hash_table_lookup(controller->albumsTable, &id);

}
char* get_Album_Name(AlbumsData* albumController, int albumId)
{
    Album* album=lookup_album( albumController, albumId);
    return getAlbumName(album);
}

// Função para libertar a memória alocada pela Hash Table contida em albums Data 
void destroyTableAlbum(AlbumsData* AlbumData){

    g_hash_table_destroy(AlbumData->albumsTable);
    printf("Destrui albumsData\n");

}


//Função para imprimir um album
void print_album_entry (gpointer key, gpointer value, gpointer user_data) {

    if (key == NULL || value == NULL) {
        printf( "Chave ou valor nulo encontrado.\n");
        sleep(2);
        return;
    }

    // Suprime o aviso de variáveis não usadas
    (void)user_data;

    //char* id = (char*)key;
    Album* album = (Album*)value;

    printAlbum(album);

}

// Função para imprimir toda a hash table
void print_all_albums(AlbumsData* data) {

    printf("----- Hash Table de albums -----\n");
    sleep(3);
    g_hash_table_foreach(data->albumsTable, print_album_entry, NULL);
    sleep(3);
    printf("----- Fim da Hash Table -----\n");

}



int isAlbumValid(AlbumsData* controlador,int id){
    Album* album = lookup_album(controlador,id);
    if(album == NULL) return 1;
    return 0;
}

