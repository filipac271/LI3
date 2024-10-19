#include "controler/musicsController.h"
#include "controler/artistsController.h"
#include "controler/mainController.h"
#include "utilidades.h"
#include "validacao/validaMusic.h"
#include "main/feeder.h"
#include "Entitys/musics.h"

#include <glib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include <unistd.h>




struct musicData {
  GHashTable* musicsTable;
};




MusicData* musicsFeed(FILE* ficheiro,ArtistsData* artistsData){

 MusicData* MData = malloc(sizeof(MusicData));  // Corrigido: alocando corretamente o tamanho de `ArtistsData`
    
    char *filename = malloc(sizeof(char) * 256);
    sprintf(filename, "resultados/musics_errors.csv");
    FILE *errosFileMusics = fopen(filename, "w");
    free(filename);
    
    char* line = NULL;  // Inicializado como NULL para getline alocar memória
    size_t len = 0;
    char* tokens[8];
    
    MData->musicsTable = iniciar_hash_musica();
    
    // Ignorar a primeira linha
    getline(&line, &len, ficheiro);
    fprintf(errosFileMusics,"%s",line);
    
    while (1) {

        // Pega a próxima linha
        if (pegaLinha(ficheiro, &len, &line) == NULL){
           break; 
        } 
           // Remove a nova linha no final, se existir
    if (line[0] != '\0' && line[strlen(line) - 1] == '\n') {
        line[strlen(line) - 1] = '\0';
    }
      //printf("%d\n", num_artists);

        
        // Atualizar o lineOutput em cada iteração
        char lineOutput[2048];
        strncpy(lineOutput, line, 2048);  // Copia a linha para o buffer local
        lineOutput[2048 - 1] = '\0';  // Garante a terminação da string
        
        parser(line, tokens);

        // Aqui os tokens devem corresponder à ordem dos dados no arquivo
        char *music_id = remove_quotes(tokens[0]);
        char *music_title = remove_quotes(tokens[1]);
        char *music_artists = remove_quotes(tokens[2]);
        char *music_duration = remove_quotes(tokens[3]);
        char *music_genre = remove_quotes(tokens[4]);
        char *music_year = remove_quotes(tokens[5]);
        char *music_lyrics = remove_quotes(tokens[6]);

        int num_artistId = contar_elementos(music_artists);

        char** music_artist_id = divideArtists(music_artists);


        int isValid = validaMusic(music_duration,music_artist_id,getArtistsTable(artistsData),num_artistId);
        
        if(isValid){
            Music* nova_musica = new_music(music_id, music_title, music_artist_id, music_duration, music_genre, music_year, music_lyrics, num_artistId);

            // Inserir os dados na hash table
        inserir_musica_na_htable(MData->musicsTable,nova_musica,music_id);
        
        //printf("Número de artistas após: %d\n", num_artistId);
        }else{
            fprintf(errosFileMusics,"%s\n",lineOutput);
        }


        free(music_artist_id);

        // Libera as strings alocadas com remove_quotes
        freeCleanerMusics(music_id,music_title,music_artists,music_duration,music_genre,music_year,music_lyrics);
    }
    
    // Libera a memória alocada por getline
    free(line);
    
    fclose(errosFileMusics);
    return MData;
}


void destroyMusicTable(MusicData* data){
  g_hash_table_destroy(data->musicsTable);
  printf("Tabela das musicas destruida\n");
}









GHashTable* iniciar_hash_musica(){
  GHashTable* hash_musica = g_hash_table_new_full(g_str_hash, g_str_equal, free, (GDestroyNotify)free_musica);

  if(hash_musica == NULL){
    printf("Erro: Hash table musica não foi criada.\n");
    exit(1);
  } else {
    printf("Hash table musica criada com sucesso.\n");
  }
  return(hash_musica);
}


//
void inserir_musica_na_htable(GHashTable* musica, Music* nova_musica,char* music_id){

  g_hash_table_insert(musica, strdup(music_id), nova_musica);
  //ver se depois é preciso adicionar prints
    

}

//Nao mexer a partir daqui!

Music* lookup_musica(GHashTable* musica, char* music_id){
  return g_hash_table_lookup(musica, music_id);
}


// Função callback para imprimir a hash table
void print_music_entry (gpointer key, gpointer value, gpointer user_data) {
    char* id = (char*)key;
    Music* music = (Music*)value;

    print_musicas(music);
}

// Função para imprimir toda a hash table
void print_all_musics(MusicData* musica) {
    printf("----- Hash Table de Musicas -----\n");
    sleep(3);
    g_hash_table_foreach(musica->musicsTable, print_music_entry, NULL);
    sleep(3);
    printf("----- Fim da Hash Table -----\n");
}


GHashTable* getMusicsTable(MusicData* data){
  return data->musicsTable;
}






