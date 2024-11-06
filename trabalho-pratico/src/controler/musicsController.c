#include "controler/musicsController.h"
#include "controler/artistsController.h"
#include "controler/mainController.h"
#include "utilidades.h"
#include "validacao/validaMusic.h"
#include "main/feeder.h"
#include "Entitys/musics.h"
#include "IOManager.h"


#include <glib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include <unistd.h>




struct musicData {
  GHashTable* musicsTable;
 // GHashTable* discographyIndo
};




MusicData* musicsFeed(char* diretoria, ArtistsData* artistsData){

 MusicData* MData = malloc(sizeof(MusicData));  // Corrigido: alocando corretamente o tamanho de `ArtistsData`
    //FILE* ficheiro = abrirFILE(diretoria,"musics.csv");

    
    char *filename = malloc(sizeof(char) * 256);
    sprintf(filename, "resultados/musics_errors.csv");
    FILE *errosFileMusics = fopen(filename, "w");
    free(filename);
    
    // char* line = NULL;  // Inicializado como NULL para getline alocar memória
    // size_t len = 0;
    // char* tokens[8];
    
    MData->musicsTable = iniciar_hash_musica();
    //DINFO
//    MData->discographyIndo = iniciar_hash_info();
    

    Parser* parserE= newParser(diretoria,"musics.csv");

    // Ignorar a primeira linha
    char * line= pegaLinha(parserE);
    fprintf(errosFileMusics,"%s",line);
    free(line);
    while (1) {

        // Pega a próxima linha
    //     if (pegaLinha(ficheiro, &len, &line) == NULL){
    //       break; 
    //     } 
    //        // Remove a nova linha no final, se existir
    // if (line[0] != '\0' && line[strlen(line) - 1] == '\n') {
    //     line[strlen(line) - 1] = '\0';
    // }
      //printf("%d\n", num_artists);


       
        parserE= parser(parserE); 


  
      char** tokens= getTokens(parserE);
     if (tokens==NULL) 
     {
          freeParser(parserE); break;
     }
        // Atualizar o lineOutput em cada iteração
        // char lineOutput[2048];
        // strncpy(lineOutput, line, 2048);  // Copia a linha para o buffer local
        // lineOutput[2048 - 1] = '\0';  // Garante a terminação da string
        

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

        int discography = duration_to_seconds(music_duration);

            //printf("DISCOGRAPHY: %d \n",discography);



        int isValid = validaMusic(music_duration,music_artist_id,artistsData,num_artistId,tokens[2]);
      
        if(isValid){
            Music* nova_musica = new_music(music_id, music_title, music_artist_id, music_duration, music_genre, music_year, music_lyrics, num_artistId);

            if(num_artistId > 1){
             // printf("ENTROU! \n");
              int i = 0;
              //printf("VALOR DO i: %d\n", i);

              while(i < num_artistId){
                
                inserir_discography_into_artist(artistsData,discography, music_artist_id[i]);
                i++;

              }
            } else{
                inserir_discography_into_artist(artistsData,discography, music_artist_id[0]);
              }

            // Inserir os dados na hash table
        inserir_musica_na_htable(MData->musicsTable,nova_musica,music_id);
        
        //printf("Número de artistas após: %d\n", num_artistId);
        }else{
            //fprintf(errosFileMusics,"%s\n",lineOutput);
        }


        free(music_artist_id);

        // Libera as strings alocadas com remove_quotes
        freeCleanerMusics(music_id,music_title,music_artists,music_duration,music_genre,music_year,music_lyrics);
        free(getLine(parserE));
    }
   
   // print_all_Dinfos(MData);
    

 
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

Music* lookup_musica(MusicData* controller, char* music_id){

  return g_hash_table_lookup(controller->musicsTable, music_id);
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

/*
GHashTable* getMusicsTable(MusicData* data){
  return data->musicsTable;
}




//COISAS DE DINFO E CENAS DO .H PARA SABER QUE JA TIREI DALI

.h
//void destroyDinfoTable(MusicData* data);
//GHashTable* iniciar_hash_info();
void inserir_dinfo_into_htable(GHashTable* dinfo, int new_discography, char* artist_id, GHashTable* Artist_Original);
void print_dinfo_entry (gpointer key, gpointer value, gpointer user_data);
void print_all_Dinfos(MusicData* musica);
GHashTable* getDinfoTable(MusicData* data);





.c
// void destroyDinfoTable(MusicData* data){
//   g_hash_table_destroy(data->discographyIndo);
//   printf("Tabela Dinfo destruida\n");
// }


// GHashTable* iniciar_hash_info(){
//   GHashTable* hash_dinfo = g_hash_table_new_full(g_str_hash, g_str_equal, free, (GDestroyNotify)free_dinfo);
//   if(hash_dinfo == NULL){
//     printf("Erro: Hash table DIinfo não foi criada.\n");
//     exit(1);
//   } else {
//     printf("Hash table Dinfo criada com sucesso.\n");
//   }
//   return(hash_dinfo);

// }


void inserir_dinfo_into_htable(GHashTable* dinfo, int new_discography, char* artist_id, GHashTable* Artist_Original){
  //getArtistsTable(artistsData)
  //printf("ARTISTS ID NA INSERIR: %s\n", artist_id);

  //printf("AQUI!\n");
  //printf("ARTISTS ID NA INSERIR: %s\n", artist_id);
  Info_M *existing_dinfo = g_hash_table_lookup(dinfo,artist_id);
  //printf("DISCOGRAFIA EXISTENTE: %d\n",new_discography);

  if(existing_dinfo != NULL){
   // printf("EXISTEEEEEEEEEEEEEEE\n");

    //printf("VELHA discografia: %d\n", get_dinfo_discography(existing_dinfo));
    set_dinfo_new_discography(existing_dinfo,new_discography);
    //printf("NOVA discografia: %d\n", get_dinfo_discography(existing_dinfo));
   // printf("CHEGOU AQUI!!!!!!!\n");
  } else{
    Artist *original_country = g_hash_table_lookup(Artist_Original, artist_id);
   // printf("AQUI AQUI ONDE NAO EXISTE!\n");
    //printf("DISCOGRAFIA ATUAL: %d\n",new_discography);



    Info_M *new_info = new_dinfo(artist_id, new_discography,(getArtistCountry(original_country)));
      g_hash_table_insert(dinfo, strdup(artist_id), new_info);

   // printf("CRIOU UMA DINFO NOVA!\n");
  }
}




void print_dinfo_entry (gpointer key, gpointer value, gpointer user_data) {
    char* id = (char*)key;
    Info_M* dinfo = (Info_M*)value;

    print_dinfo(dinfo);
}

void print_all_Dinfos(MusicData* musica) {
    printf("----- Hash Table de Discography -----\n");
    sleep(3);
    g_hash_table_foreach(musica->discographyIndo, print_dinfo_entry, NULL);
    sleep(3);
    printf("----- Fim da Hash Table -----\n");
}


GHashTable* getDinfoTable(MusicData* data){
  return data->discographyIndo;
}


*/

