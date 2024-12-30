#include "controler/musicsController.h"
#include "controler/artistsController.h"
#include "controler/albumsController.h"
#include "utilidades.h"
#include "validacao/validaMusic.h"
#include "Entitys/musics.h"
#include "Input.h"
#include "sys/resource.h"


#include <glib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>




struct musicData {
  GHashTable* musicsTable;

};



//Iniciar Hash Table
GHashTable* iniciar_hash_musica(){

// A key da Hash Table é o ID  das músicas
  GHashTable* hash_musica = g_hash_table_new_full(g_int_hash, g_int_equal, free, (GDestroyNotify)free_musica);

 // Verificar se a hash table foi criada corretamente
  if(hash_musica == NULL){
   
    printf("Erro: Hash table musica não foi criada.\n");
    exit(1);

  } else {

    printf("Hash table musica criada com sucesso.\n");
  }

  return(hash_musica);

}


//Inserir música na Hash Table
void inserir_musica_na_htable(GHashTable* musica, Music* nova_musica, int music_id) {
    int* key = malloc(sizeof(int));  // Aloca memória para a chave

    *key = music_id;
    g_hash_table_insert(musica, key, nova_musica);
}






MusicData* musicsFeed(char* diretoria, ArtistsData* artistsData, AlbumsData* albumData){

    MusicData* MData = malloc(sizeof(MusicData));  

    if(MData == NULL){

        fprintf(stderr,"Alocação de memória do MusicsController não foi bem sucedido");
        exit(1);
    }  
    
    //Abre o ficheiro  "musics_errors.csv" e aloca memória para o respetivo pointer 
    Output* Erros= iniciaOutput("resultados/musics_errors.csv");
  
    MData->musicsTable = iniciar_hash_musica();

    //Inicia o Parser e abre o ficheiro "musics.csv" do dataset
    Parser* parserE= newParser(diretoria,"musics.csv");

    // Ler a primeira linha do ficheiro 
    char * line= pegaLinha(parserE);

    //Enviar a linha para o ficheiro musics_erros.csv, esta não será inserida hashTable
    outputErros(Erros,line);
    free(line);

    while (1) {

        parserE= parser(parserE); 

        char** tokens= getTokens(parserE);

        if (tokens==NULL) 
        {
          // Fecha o ficheiro guardado no Parser e liberta a memória alocada neste
          freeParser(parserE); 
          break;
        }

        // Linha do input para validação, esta será enviada para o output de erros caso não seja válida
        char* linhaE=getLineError(parserE);
        
        int isValid = validaMusic(tokens[4],tokens[2],artistsData, Erros,linhaE, albumData,tokens[3]);

        // Se a linha for válida é criado a música e é inserida na Hash Table das músicas, é também atualizada a discografia do seu artista
        if(isValid){ 
          Music* nova_musica = new_music(tokens);

          // Soma o tempo da música à discografia de todos os seus autores
          inserir_discography_into_artist(artistsData,tokens[4],tokens[2]);

          // Inserir os dados na hash table
          inserir_musica_na_htable(MData->musicsTable,nova_musica,transformaIds(tokens[0]));
        }

        free(linhaE);
        free(getLine(parserE));

   }
   
    // Liberta a memória alocada pelo Output Erros e fecha o ficheiro dos erros
    freeOutput(Erros);
  
    return MData;

}


void destroyMusicTable(MusicData* data){

  g_hash_table_destroy(data->musicsTable);
  printf("Tabela das musicas destruida\n");

}





// Função para procurar uma música pelo id (chave da hash table)
Music* lookup_musica(MusicData* controller, int music_id){
 // printf("CENA %d\n", music_id);

  return g_hash_table_lookup(controller->musicsTable, &music_id);
}


// Função  para imprime uma música
void print_music_entry (gpointer key, gpointer value, gpointer user_data) {

    if (key == NULL || value == NULL) {
        printf( "Chave ou valor nulo encontrado.\n");
        sleep(2);
        return;
    }

    // Suprime o aviso de variáveis não usadas
    (void)user_data;

    //char* id = (char*)key;
    Music* music = (Music*)value;

    print_musicas(music);
}


// Função para imprimir toda a hash table das Músicas
void print_all_musics(MusicData* musica) {

    printf("----- Hash Table de Musicas -----\n");
    sleep(3);
    g_hash_table_foreach(musica->musicsTable, print_music_entry, NULL);
    sleep(3);
    printf("----- Fim da Hash Table -----\n");

}





void atualizaStreams (char* idMusica, MusicData* musicController, ArtistsData* artistcontroller){

  int music_id = transformaIds(idMusica);
  
  Music* musicadoartista = lookup_musica(musicController, music_id);
  
  int numartistas = get_numArtistsId(musicadoartista);

  int* arrayartistas = getArtistIDfromMuiscID(musicadoartista);
    
  put_stream_into_Artist(numartistas,arrayartistas,artistcontroller);

  
  free(arrayartistas);
  
}

int get_musicAlbum(MusicData* musicController , int musicId)
{
     Music* music=lookup_musica(musicController, musicId);
    int album= get_music_album(music);
     return album;
}

int get_numArtists(MusicData* musicController,int musicId)
{
  Music* music=lookup_musica(musicController, musicId);
  int numartistas= get_numArtistsId(music);
  return numartistas; 
}

 int* getArtistIdMusic(MusicData* musicController,int musicId)
 {
     Music* music=lookup_musica(musicController, musicId);
    int* artistas= getArtistIDfromMuiscID(music);
   return artistas;
 } 

 char* get_musicGenre(MusicData* musicController, int musicId)
 {
     Music* music=lookup_musica(musicController, musicId);
     char* genero=get_music_genre(music);
     return genero;
 }