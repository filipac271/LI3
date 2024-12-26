#include "Entitys/musics.h" 
#include "utilidades.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "Entitys/history.h"
#include "Entitys/artists.h"
#include "controler/historyController.h"

/* Ideia principal do historico (para ficar aqui registado)

Para a query 4 teremos uma hashtable em que a key é a data de domigno(inicio da semana) 
nessa semana cada espacinho é uma strcut com artista e tempo total desse artista na semana
IMPORTANTE se for uma banda é preciso ver os seis constituintes e adicionar a esses artistas 
e não à banda em si.

Comando
4 [begin_date end_date]
Output
name;type;count_top_10


//FALAR COM A CAROL DEPOIS
Para a query 6 teremos uma hashtable em que a key é o userid e dentro teremos uma struct com 
o artista o total de temppo desse ano
pensar em algo para o #musica.???
genero????

struct ano{
  char* user_id;
  Ghashtable
}


Comando
6 <user_id> <year> [N]
Output
listening time;#musics;artist;day;genre;favorite_album;hour
[artista_preferido_1;#musicas;listening_time]
[artista_preferido_2;#musicas;listening_time]
[…]

HISTORICO
- id – identificador único do registo;
– user_id – identificador único do utilizador a que o registo se refere;
– music_id – identificador único da música a que o registo se refere;
– timestamp – data e hora em que a música foi ouvida pelo utilizador;
– duration – tempo de duração da audição da música. E.g., um utilizador pode ter ouvido
apenas 30 segundos de uma música;
– platform – plataforma em que a música foi reproduzida. I.e., computador ou disposi-
tivo móvel.

*/

struct artistahistory{
  int artist_id;
  int totalsemanalsegundos; //passar a duration de hh:mm:ss (funcao defenida nas utilities) 
};

struct domingo{
  char* data ;
  GHashTable* artistahistory;
};




void freeUmArtista (UmArtista* artista){
  if(artista == NULL){
    return;
  } 
  free(artista);
}


void freeDomingo(Domingo* domingo) {
    free(domingo->data);  
        
        g_hash_table_destroy(domingo->artistahistory); 

    free(domingo);
}












void destroy_history(Domingo* domingo) {
  
        free(domingo->data);  
        
        g_hash_table_destroy(domingo->artistahistory); 
    
}






Domingo* newDomingo(char* data){
   // Aloca memória para a estrutura
    Domingo* novo_domingo = malloc(sizeof(Domingo));
    if (!novo_domingo) {
        fprintf(stderr, "Erro ao alocar memória para Domingo\n");
        return NULL;
    }

    //Ver se é realmente preciso um strdup
    novo_domingo->data = strdup(data); // Duplica a string passada como parâmetro
  //GHashTable* Domingo =g_hash_table_new_full(g_int_hash, g_int_equal, free, (GDestroyNotify)freeUser);

    // Cria a hash table para armazenar o histórico dos artistas
    novo_domingo->artistahistory = g_hash_table_new_full(g_int_hash, g_int_equal, free, (GDestroyNotify)freeUmArtista);

    return novo_domingo;
}

/* Tokens:
TOken[0] = history_id
token[1] = user_id
token[2] = music_id
token[3] = timestramp
token[4] = duration hh:mm:ss
token[5] = platafomra
*/

UmArtista* new_umArtista (int artist_id, int segundos){
  UmArtista* n_umart = malloc(sizeof(UmArtista));
  
  if (n_umart == NULL) {
        fprintf(stderr, "Memory allocation failed for novo UMArtista\n");
        exit(1);
    }

          // Artista ainda não existe na tabela, crie um novo registro
  n_umart->artist_id = artist_id;
  n_umart->totalsemanalsegundos = segundos; // Inicialize o valor

  return n_umart;  
}


void inserir_umartista_na_semana(GHashTable* artisthistory, UmArtista* novo_artista, int artist_id){
   // printf("INSERIR ARTISTA NA SEMANA!");
    
    
    int* key = malloc(sizeof(int));  // Aloca memória para a chave
    *key = artist_id;

    g_hash_table_insert(artisthistory, key, novo_artista);

}

GHashTable* get_artisthistorido_dedomingo (Domingo* domingo){
  return domingo->artistahistory;
}


UmArtista* lookup_artista_historico(GHashTable* Artista, int artist_id){
  return g_hash_table_lookup(Artista, &artist_id);

}


// Função para adicionar um artista ao Domingo
void new_or_add(Domingo* domingo, char** tokens, MusicData* musicController) {
  //transforma o char music_id em int para conseguir encontrar a estrutura Music 
    int music_id = transformaIds(tokens[2]);

    Music* musicadoartista = lookup_musica(musicController, music_id);

    int numartistas = get_numArtistsId(musicadoartista);

    //array de artistas que constituem essa musica
    int* arrayartistas = getArtistIDfromMuiscID(musicadoartista,numartistas);
    

    GHashTable* artistahistory = domingo->artistahistory;
    if (!artistahistory) {
        fprintf(stderr, "Erro: artistahistory é NULL.\n");
        return;
    }

    char* segundosparaadicionar = remove_quotes(tokens[4]);
  

    int segundos = duration_to_seconds(segundosparaadicionar);

    //É PRECISO ALTERAR PARA QUANDO O NUMARTISTA É 0 ISTO É QUANDO NAO É UM GRUPO
    if(numartistas > 0){
    for (int i = 0; i < numartistas; i++) {
        int artist_id = arrayartistas[i];

        UmArtista* artist_data = lookup_artista_historico(artistahistory, artist_id);

        if (!artist_data) {

            UmArtista* novo_artista = new_umArtista(artist_id, segundos);
            inserir_umartista_na_semana(artistahistory, novo_artista, artist_id);
        } else {

            artist_data->totalsemanalsegundos += segundos;
        }
    }

    }
    free(arrayartistas);
    free(segundosparaadicionar);
}




GHashTable* getArtistHistory(Domingo* domingo){
  return(domingo->artistahistory);
}








//FUNCOES PRINTS QUE NAO FUNCIONAM
void print_artisthistory (UmArtista* artista) {
    if (artista) {
        printf("ARTIST_ID: %d\n", artista->artist_id);
        printf("TOTAL_SEGUNDOS: %d\n", artista->totalsemanalsegundos);
    } else {
        fprintf(stderr, "Erro: ESTE UMARTISTA NAO EXISTE\n");
    }
}


void printf_domingo (Domingo* domingo) {
    if (domingo) {
        if (domingo->data) {
            printf("DATA: %s\n", domingo->data);
        } else {
            fprintf(stderr, "Erro: DATA do Domingo é NULL\n");
        }
    } else {
        fprintf(stderr, "Erro: ESTA DOMINGO NAO EXISTE\n");
    }
}


void print_artisthistory_entry(gpointer key, gpointer value, gpointer user_data) {
    if (key == NULL || value == NULL) {
        fprintf(stderr, "Erro: Chave ou valor nulo encontrado.\n");
        return;
    }

    (void)user_data; // Ignora user_data, se não for usado

    printf("Processando artista com chave: %p\n", key); // Log da chave
    UmArtista* artista = (UmArtista*)value;

    print_artisthistory(artista);
}


void print_semana_completa(Domingo* domingo) {
    if (domingo == NULL) {
        fprintf(stderr, "Erro: Domingo é NULL.\n");
        return;
    }

    if (get_artisthistorido_dedomingo(domingo)== NULL) {
        fprintf(stderr, "Erro: Hash Table artistahistory é NULL.\n");
        return;
    }


    printf("----- Hash Table DOMINGO da semana %s -----\n", domingo->data);

    g_hash_table_foreach(get_artisthistorido_dedomingo(domingo), print_artisthistory_entry, NULL);

    printf("----- Fim da Hash Table DOMINGO da semana %s -----\n", domingo->data);
}
