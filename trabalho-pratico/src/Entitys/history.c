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

struct artisthistory_garray{
  int artist_id;
  int totalsemanalsegundos; //passar a duration de hh:mm:ss (funcao defenida nas utilities) 
};


struct domingo{
  char* data ;
  GHashTable* artistahistory; //mudar para garray
  GArray* artistahistory_garray;
};




void freeUmArtista (UmArtista* artista){
  if(artista == NULL){
    return;
  } 
  free(artista);
}

// Função para liberar a memória de cada UmArtista
void free_um_artista(ArrayArtistas* artista) {
    if (artista != NULL) {
        free(artista);  // Liberar a memória do UmArtista
    }
}

// Função para liberar o GArray e seus dados
void free_garray_with_data(GArray* array) {
    if (array != NULL) {
        // Itera sobre o GArray e libera cada elemento
        guint i;
        for (i = 0; i < array->len; i++) {
            ArrayArtistas* artista = g_array_index(array, ArrayArtistas*, i);
            free_um_artista(artista);  // Liberar os dados (cada UmArtista)
        }

        // Agora, libera o GArray em si
        g_array_free(array, FALSE);  // Não precisa liberar os dados novamente, pois já fizemos isso
    }
}



void freeDomingo(Domingo* domingo) {
    free(domingo->data);  
        
        //g_hash_table_destroy(domingo->artistahistory); 
        g_array_free(domingo->artistahistory_garray, TRUE);
        //free_garray_with_data(domingo->artistahistory_garray);


    free(domingo);
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
    novo_domingo->artistahistory = g_hash_table_new_full(g_int_hash, g_int_equal, NULL, NULL);

    novo_domingo->artistahistory_garray = g_array_new(FALSE, FALSE, sizeof(ArrayArtistas));

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
  UmArtista* n_umart = malloc(sizeof(UmArtista)); //this is line 151
  
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
    //free(key);
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
    int* arrayartistas = getArtistIDfromMuiscID(musicadoartista);
    

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

int compare_artistas(const void* a, const void* b) {
    ArrayArtistas* art_a = (ArrayArtistas*)a;
    ArrayArtistas* art_b = (ArrayArtistas*)b;
    return art_b->totalsemanalsegundos - art_a->totalsemanalsegundos; // Decrescente
}


void passa_Domingo_para_garray(Domingo* domingo) {
    if (domingo == NULL || domingo->artistahistory == NULL || domingo->artistahistory_garray == NULL) {
        return; // Valida os parâmetros de entrada
    }

    GHashTableIter iter;
    gpointer key, value;
    // Limpa o GArray antes de preenchê-lo novamente, se necessário
    g_array_set_size(domingo->artistahistory_garray, 0);

    // Itera sobre a GHashTable e transfere os dados para o GArray
    g_hash_table_iter_init(&iter, domingo->artistahistory);
           // printf("ESTOU AQUI\n");

    while (g_hash_table_iter_next(&iter, &key, &value)) {
        ArrayArtistas* artist_to_filter = (ArrayArtistas*)value;
       // printf("ESTOU AQUI\n");
        //print_artisthistorygarray(artist_to_filter);
        g_array_append_val(domingo->artistahistory_garray, artist_to_filter);

        
        // Ver se isto funciona 
        free(key);  // só deus sabe porque é que sito funciona
        freeUmArtista((UmArtista*)value);
    }

    // Destrói a estrutura interna da GHashTable
    g_hash_table_destroy(domingo->artistahistory);
    domingo->artistahistory = NULL; // Marca como NULL para evitar acessos futuros

    // Ordena o GArray usando a função de comparação
    g_array_sort(domingo->artistahistory_garray, compare_artistas);

    // Trunca o GArray para manter apenas os 10 primeiros elementos
    guint length = domingo->artistahistory_garray->len;
    if (length > 10) {
        g_array_remove_range(domingo->artistahistory_garray, 10, length - 10);
    }
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

void print_artisthistorygarray (ArrayArtistas* artista) {
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