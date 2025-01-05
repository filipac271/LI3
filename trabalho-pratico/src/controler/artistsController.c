#include "Entitys/artists.h"
#include "Entitys/musics.h"
#include "controler/artistsController.h"
#include "validacao/validaArtista.h"
#include "utilidades.h"
#include "Input.h"
#include "query/query2.h"

#include <glib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

struct artistsData{
    GHashTable* artistsTable;
};

// Função para inicializar a hash table
GHashTable* init_artists_table() {
    // A key da Hash Table é o ID  dos artistas
    GHashTable* artists_table = g_hash_table_new_full(g_int_hash, g_int_equal, free, (GDestroyNotify)free_artist);
    // Verificar se a hash table foi criada corretamente
    if (artists_table == NULL) {
        printf("Erro: Hash table dos artistas não foi criada.\n");
        exit(1);
    } else {
        printf("Hash table dos artistas criada com sucesso.\n");
    }
    return artists_table;
}

// Função para inserir um artista na hash table usando o id como chave
void insert_artist_into_table(GHashTable* artists_table, Artist* new_artist,int id) {
    int* key = malloc(sizeof(int));  // Aloca memória para a chave
    *key = id;
    g_hash_table_insert(artists_table, key,new_artist);
}


ArtistsData* artistFeed(char* diretoria) {

    ArtistsData* AData = malloc(sizeof(ArtistsData)); 
    if(AData == NULL){
        fprintf(stderr,"Alocação de memória do ArtistsController não foi bem sucedido");
        exit(1);
    }  
     //Abre o ficheiro  "artists_errors.csv" e aloca memória para o respetivo pointer 
    Output * Erros= iniciaOutput("resultados/artists_errors.csv");
    AData->artistsTable = init_artists_table();
    //Inicia o Parser e abre o ficheiro "artists.csv" do dataset
    Parser* parserE= newParser(diretoria,"artists.csv");
    // Ler a primeira linha do ficheiro  
    char* linha= pegaLinha(parserE);
    //Enviar a linha para o ficheiro "artist_erros.csv", esta não será inserida na hashTable
    outputErros(Erros,linha);
    free(linha);

    while (1) {
 
        parserE= parser(parserE);
        char** tokens = getTokens(parserE);

        if (tokens==NULL) {

             // Fecha o ficheiro guardado no Parser e liberta a memória alocada neste
              freeParser(parserE); break;
         }

        // Linha do input para validação, esta será enviada para o output de erros caso não seja válida
        char* linhaE=getLineError(parserE);
        int isValid = validaArtista(tokens[4],tokens[6],linhaE, Erros);
        
        //Se a linha for válida é criado o artista e é inserido na Hash Table dos artistas
        if (isValid) {
            Artist* newArtist = create_artist(tokens);
            // Insere os dados na hash table
            insert_artist_into_table(AData->artistsTable, newArtist, transformaIds(tokens[0]));
        }

        free(linhaE);
        free(getLine(parserE));
    }
    // Liberta a memória alocada pelo Output Erros e fecha o ficheiro dos erros
    freeOutput(Erros);
    return AData;
}


// Soma o tempo da música à discografia de todos os seus autores
void inserir_discography_into_artist (ArtistsData* controller, char* music_durationAspas, char* music_artists) {

        char *music_duration = remove_quotes(music_durationAspas);
        int num_artistId = calculate_num_members(music_artists);
        int* music_artist_id = divideArray(music_artists,num_artistId);

        if(num_artistId > 1){

            int i = 0;
            
            while(i < num_artistId){
                    
                    int discography = duration_to_seconds(music_duration);
                    Artist * artista_atual = lookup_artist(controller, music_artist_id[i]);
                    setArtistDiscography(artista_atual, discography);
                    i++;
            }

        } 
        else
        { 
            int discography = duration_to_seconds(music_duration);          
            Artist * artista_atual = lookup_artist(controller, music_artist_id[0]);
            setArtistDiscography(artista_atual, discography); 
        }
        free(music_duration);
        freeArray(music_artist_id);
}

void put_stream_into_Artist (int numartistas, int* arrayArtistas, ArtistsData* controller){

  for (int i = 0; i < numartistas; i++) {

    int artist_id = arrayArtistas[i]; 
    Artist * artista_atual = g_hash_table_lookup(controller->artistsTable,&artist_id );
    char* tipo = getArtistType(artista_atual);

    if(strcmp (tipo,"individual") == 0){
        double ganho = getArtistGanho(artista_atual);
       setStreams(artista_atual,1*ganho); 

    }
    else if (strcmp (tipo,"group") == 0){
        double ganho = getArtistGanho(artista_atual);
        setStreams(artista_atual,1*ganho);
        int* grupoList = getArtistGrupo(artista_atual);
        int num_artists = getArtistNumMembros(artista_atual);

        for(int i = 0; i<num_artists; i++ ){
            Artist* artistaGrupo = g_hash_table_lookup(controller->artistsTable,&grupoList[i] );
            setStreams(artistaGrupo,(1*ganho)/num_artists);
        }
        free(grupoList);
    }

    free(tipo);
  }
}

void atualizaAlbuns (char* arrayAlbuns, ArtistsData* controller){

int numartistas = calculate_num_members(arrayAlbuns);
int* arrayArtistas = divideArray(arrayAlbuns,numartistas);

for (int i = 0; i < numartistas; i++) {
    int artist_id = arrayArtistas[i]; 
    Artist * artista_atual = g_hash_table_lookup(controller->artistsTable,&artist_id );

    if(artista_atual != NULL) setAlbuns(artista_atual);

}

free(arrayArtistas);

}

// Função para libertar a memória alocada pela Hash Table contida em Artist Data 
void destroyTableArtist(ArtistsData* ArtistData){

    g_hash_table_destroy(ArtistData->artistsTable);
    printf("Destrui artistaData\n");
}

// Função para procurar um artista pelo id (chave da hash table)
Artist* lookup_artist(ArtistsData* controller, int id) {

    return g_hash_table_lookup(controller->artistsTable, &id);
}

//Função para imprimir um artista
void print_artist_entry (gpointer key, gpointer value, gpointer user_data) {

    if (key == NULL || value == NULL) {
        printf( "Chave ou valor nulo encontrado.\n");
        sleep(2);
        return;
    }

    // Suprime o aviso de variáveis não usadas
    (void)user_data;

    //char* id = (char*)key;
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

//Função que enche o GArray com os artistas de um determinado país
void fill_filtered_artists(ArtistsData* controller, GArray *array, char *country) {

    GHashTableIter iter;
    gpointer key, value;
    g_hash_table_iter_init(&iter, controller->artistsTable);

    while (g_hash_table_iter_next(&iter, &key, &value)) {
    
        Artist* artist_to_filter = value;
        char* pais = getArtistCountry(artist_to_filter);
        if (country == NULL || strcmp(country, "") == 0 || strcmp(pais, country) == 0) {

            Discography* n_discography = create_discography(getArtistId(artist_to_filter), getArtistDiscography(artist_to_filter));
            g_array_append_val(array, n_discography);

        }
        free(pais);
    }
}

int isArtistValid (ArtistsData* controlador , int id){
    Artist* artista = lookup_artist(controlador,id);
    if(artista == NULL) return 1;
    return 0;
}

//Getters

char* getArtistNameControl(ArtistsData* controlador, int id){
    Artist* artista = lookup_artist(controlador,id);
    return getArtistName(artista);
}

char* getArtistCountryControl(ArtistsData* controlador, int id){
    Artist* artista = lookup_artist(controlador,id);
    return getArtistCountry(artista);
}

char* getArtistTypeControl(ArtistsData* controlador, int id){
    Artist* artista = lookup_artist(controlador,id);
    return getArtistType(artista);
}

int getArtistAlbunsIndividuaisControl(ArtistsData* controlador, int id){
    Artist* artista = lookup_artist(controlador,id);
    return getArtistAlbunsIndividuais(artista);
}

double getArtistProfitsControl(ArtistsData* controlador, int id){
    Artist* artista = lookup_artist(controlador,id);
    return getArtistProfits(artista);
}

int getArtistDiscographyControl(ArtistsData* controlador, int id){
    Artist* artista = lookup_artist(controlador,id);
    return getArtistDiscography(artista);
}

int getArtistNumMembrosControl(ArtistsData* controlador, int id) {
    Artist* artista = lookup_artist(controlador, id);
    return getArtistNumMembros(artista);
}

int* getArtistGrupoControl(ArtistsData* controlador, int id) {
    Artist* artista = lookup_artist(controlador, id);
    return getArtistGrupo(artista);
}

double getArtistGanhoControl(ArtistsData* controlador, int id) {
    Artist* artista = lookup_artist(controlador, id);
    return getArtistGanho(artista);
}

int getArtistIdControl(ArtistsData* controlador, int id) {
    Artist* artista = lookup_artist(controlador, id);
    return getArtistId(artista);
}