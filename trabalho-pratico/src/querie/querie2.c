#include "controler/musicsController.h"
#include "controler/artistsController.h"
#include "querie/querie1.h"
#include "querie/querie2.h"


#include <stdio.h>
#include <stdlib.h>
#include <glib.h>


// void insert_or_sum(GHashTable table, charkey, float valor_novo) {
//     // Tentar buscar o tuplo existente
//     Tuplo tuplo_existente = g_hash_table_lookup(table, key);

//     if (tuplo_existente != NULL) {
//         // Se o tuplo já existir, somar o valor ao valor existente
//         tuplo_existente->valor += valor_novo;
//         // A tabela vai manter o tuplo existente, pois a referência é a mesma
//     } else {
//         // Se não existir, criar um novo tuplo e inserir na hash table
//         Tuplonovo_tuplo = malloc(sizeof(Tuplo));
//         novo_tuplo->nome = strdup(key);  // Copiar a string da chave
//         novo_tuplo->valor = valor_novo;

//         // Inserir o novo tuplo na hash table (substitui se já existir)
//         g_hash_table_replace(table, novo_tuplo->nome, novo_tuplo);
//     }
// }

// Output
// name 1;type 1;discography duration 1;country 1

struct querie2{
  char *artist_id; //array
  char *artist_type; //string
  int discography; //int em segundos
  char *artist_country; //???????? //string
};

void free_querie2 (Output2* q2){
  if(q2){
    free(q2->artist_id);
    free(q2->artist_type);
    free(q2->artist_country);

    free(q2);
  }
}


//a ideia seria ir criando as coisas e pondo na hash table e ao emsmo tempo ir criando um array com os tempos, os tempos seriam a key da hash table
// entao eu fazia uma funlao que procurasse o maior elemento do array, e dava à key a hash tbale para procurar o artista ()
//NAO ESQUECER RESOLUÇAO DE CONFITOS COM OS EMPATES!!!!! (pensar depois)

//maybe mudar a estrutura da musica para a duration passar a segundos????


int duration_to_seconds(const char *duration_str) {
    int hours, minutes, seconds;

    sscanf(duration_str, "%d:%d:%d", &hours, &minutes, &seconds);

    return hours * 3600 + minutes * 60 + seconds;
}


//Funçao que pega apenas no primeiro artista caso o artista nao seja individual
char* extrair_artista(char* artistId_completo){

  char* artistId_unico[9];
  int j;

  for (int i = 0; artistId_completo[i] != '\0'; i++) {
        if (isalnum(artistId_completo[i])) {
            artistId_unico[j++] = artistId_completo[i];
        } else if (j > 0 && !isalnum(artistId_completo[i])) {
        artistId_unico[j] = '\0';           
        break;
        }
    }

}

ArtistsData* get_struct_from_hashtable(GHashTable *hash_table, char* artist_id) {
    // Usando g_hash_table_lookup para procurar a estrutura pela chave
   ArtistsData *data = (ArtistsData*) g_hash_table_lookup(hash_table, artist_id);
    
    return data; // Retorna o ponteiro para a estrutura, ou NULL se não encontrada
}


// Função que será chamada para cada elemento da tabela de hash original
void insert_or_sum(gpointer key, gpointer value, gpointer user_data) {
// A nova tabela hash que está sendo preenchida, passada como 'user_data'
    GHashTable* new_hashtable_query2 = (GHashTable*)user_data;

    // O value que é um pointer para a struct original
    MusicData* original = (MusicData*)value;

    char *artist_id = get_music_artist_id(original);
    int duration_seconds = get_music_duration_seconds(original); 
    
    
    // Verificar se o artista já existe na nova hash table
    int *existing_duration = (int *)g_hash_table_lookup(new_hashtable_query2, artist_id);
    
    if (existing_duration) {
        // Se já existir, somar a duração atual à existente
        *existing_duration += duration_seconds;
    } else {
        // Caso contrário, adicionar o artista com a nova duração
        int *new_duration = malloc(sizeof(int));
        *new_duration = duration_seconds;
        g_hash_table_insert(new_hashtable_query2, artist_id, new_duration);
    }
}




void finalizar_hashtable_nova(GHashTable* original, GHashTable* new_hashtable_query2) {
      // Criar a nova hash table (onde as chaves são music_artist_id e os valores são durações acumuladas)
    GHashTable *new_hash_table = g_hash_table_new_full(g_str_hash, g_str_equal, free, (GDestroyNotify)free_querie2);

    // Percorrer a hash table original e transferir os campos desejados somando as durações
    g_hash_table_foreach(original, insert_or_sum, new_hash_table);

}

// struct querie2{
//   char *artist_id; //array 
//   char *artist_type; //string
//   int discography; //int em segundos
//   char *artist_country; //???????? //string
// };




