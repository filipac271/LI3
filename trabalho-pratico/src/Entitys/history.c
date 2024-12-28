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
  GHashTable* artistahistory; //mudar para garray
  GArray* artistahistory_garray;
};




void freeUmArtista (UmArtista* artista){
  if(artista == NULL){
    return;
  } 
  free(artista);
}


// Função para libertar o GArray e seus dados
void free_garray_with_data(GArray* array) {
    if (array != NULL) {
        // Itera sobre o GArray e liberta cada elemento
        guint i;
        for (i = 0; i < array->len; i++) {
            UmArtista* artista = g_array_index(array, UmArtista*, i);
            freeUmArtista(artista);  // Liberta os dados (cada UmArtista)
        }
        g_array_free(array, FALSE);  
    }
}

void freeDomingo(Domingo* domingo) {
    free(domingo->data);  

        g_array_free(domingo->artistahistory_garray, TRUE);

    free(domingo);
}


Domingo* newDomingo(char* data){
   // Aloca memória para a estrutura
    Domingo* novo_domingo = malloc(sizeof(Domingo));
    if (!novo_domingo) {
        fprintf(stderr, "Erro ao alocar memória para Domingo\n");
        return NULL;
    }

    novo_domingo->data = strdup(data); // Duplica a string passada como parâmetro

    // Cria a hash table para armazenar o histórico dos artistas   (GDestroyNotify)freeUmArtista
    novo_domingo->artistahistory = g_hash_table_new_full(g_int_hash, g_int_equal, NULL, NULL);

    novo_domingo->artistahistory_garray = g_array_new(FALSE, FALSE, sizeof(UmArtista));

    return novo_domingo;
}


UmArtista* new_umArtista (int artist_id, int segundos){
    UmArtista* n_umart = malloc(sizeof(UmArtista)); 

    if (n_umart == NULL) {
        fprintf(stderr, "Memory allocation failed for novo UMArtista\n"); //this is line 123
        exit(1);
    }

    // Artista ainda não existe na tabela, cria um novo registro
    n_umart->artist_id = artist_id;
    n_umart->totalsemanalsegundos = segundos;

    return n_umart;  
}

//Função para inserir um novo artista na Hash Table
void inserir_umartista_na_semana(GHashTable* artisthistory, UmArtista* novo_artista, int artist_id){
    
    int* key = malloc(sizeof(int));  
    *key = artist_id;

    g_hash_table_insert(artisthistory, key, novo_artista);
   // free(key); //isto nao é solucao para nada apenas traz erros
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

    if(numartistas > 0){
    for (int i = 0; i < numartistas; i++) {
        int artist_id = arrayartistas[i];

        UmArtista* artist_data = lookup_artista_historico(artistahistory, artist_id);

        if (!artist_data) {
            //Se o artista nao existir cria-lo e acrescenta à hash table interna
            UmArtista* novo_artista = new_umArtista(artist_id, segundos);
            inserir_umartista_na_semana(artistahistory, novo_artista, artist_id);
        } else {
            artist_data->totalsemanalsegundos += segundos; //this is line 178
        }
    } 
    } else {
        printf("SOMETHING IS VERY WRONG\n");
    }
    free(arrayartistas);
    free(segundosparaadicionar);
}


void passa_Domingo_para_garray(Domingo* domingo) {
    if (domingo == NULL || domingo->artistahistory == NULL || domingo->artistahistory_garray == NULL) {
        return;
    }

    // Limpa o GArray antes de começar
    g_array_set_size(domingo->artistahistory_garray, 0); 

    GHashTableIter iter;
    gpointer key, value;
    //pega no domingo e vai começar a iterar por ele
    g_hash_table_iter_init(&iter, domingo->artistahistory);

    while (g_hash_table_iter_next(&iter, &key, &value)) {

        UmArtista* artist_to_filter = value;

        if(artist_to_filter == NULL){
            free(key); // Liberta a chave se o artista for ignorado
            continue;
        }

        if (artist_to_filter->totalsemanalsegundos == 0) { // se o tempo for 0 o artista é ignorado porque nao vale a pena ele ocupar espaço
            free(key); // Liberta a chave se o artista for ignorado
            continue;
        }
        g_array_append_val(domingo->artistahistory_garray, artist_to_filter);
       // freeUmArtista(artist_to_filter); nao é solução
        free(key); //liberta a chave para ele ir para o proximo
    }
    g_hash_table_destroy(domingo->artistahistory);
    domingo->artistahistory = NULL;

    // Ordena o GArray
    g_array_sort(domingo->artistahistory_garray, (GCompareFunc)compare_seconds);

    // Remove elementos excedentes, mantendo apenas os 10 primeiros
    guint length = domingo->artistahistory_garray->len;
    if (length > 10) {    
    g_array_set_size(domingo->artistahistory_garray, 10);
    }
   // g_hash_table_destroy(domingo->artistahistory);
    //domingo->artistahistory = NULL;


}


gint compare_seconds(gconstpointer a, gconstpointer b) {
    
    UmArtista *artist_a = *(UmArtista **)a;
    UmArtista *artist_b = *(UmArtista **)b;

    int segundos_a = get_seconds_from_garray(artist_a);
    int segundos_b = get_seconds_from_garray(artist_b);
    //printf("NAO SEI\n");

    // Compara pela duração em segundos (ordem decrescente)
    int r = segundos_b - segundos_a;

    // Se os segundos forem iguais, compara pelo artist_id para ficar com o de menor id 
    if (r == 0) {
        r = artist_a->artist_id - artist_b->artist_id;
    }

    return r;
}

// void tentativa_free_hashtable (Domingo*domingo){
//     GHashTableIter iter;
//     gpointer key, value;
//     //pega no domingo e vai começar a iterar por ele
//     g_hash_table_iter_init(&iter, domingo->artistahistory);

//     while (g_hash_table_iter_next(&iter, &key, &value)) {
//         UmArtista* artist_to_filter = value;

//         freeUmArtista(value);
//        // free(key); //liberta a chave para ele ir para o proximo
//     }

// }



//GETTERS E SETTEERS

GHashTable* get_artisthistorido_dedomingo (Domingo* domingo){
    return domingo->artistahistory;
}


UmArtista* lookup_artista_historico(GHashTable* Artista, int artist_id){
    return g_hash_table_lookup(Artista, &artist_id);

}

GHashTable* getArtistHistory(Domingo* domingo){
  return(domingo->artistahistory);
}

GArray* get_garray_from_domingo (Domingo* domingo){
  return (domingo->artistahistory_garray);
}


int get_garray_len (Domingo* domingo){
  return(domingo->artistahistory_garray->len);
}



int get_artist_id_from_garray (UmArtista* artista){
    return artista->artist_id;
}


int get_seconds_from_garray (UmArtista* artista){
    return artista->totalsemanalsegundos;
}





//FUNCOES PRINTS 
void print_artisthistory (UmArtista* artista) {
    if (artista) {
        printf("ARTIST_ID: %d\n", artista->artist_id);
        printf("TOTAL_SEGUNDOS: %d\n", artista->totalsemanalsegundos);
    } else {
        fprintf(stderr, "Erro: ESTE UMARTISTA NAO EXISTE\n");
    }
}


// Função para imprimir o GArray
void print_garray(GArray* array) {
    if (array == NULL) {
        printf("O GArray está vazio ou não foi inicializado.\n");
        return;
    }

    printf("O GArray contém %d elementos:\n", array->len);

    // Iterar sobre todos os elementos do GArray
    for (guint i = 0; i < array->len; i++) {
        UmArtista* artista = g_array_index(array, UmArtista*, i);
        print_artisthistory(artista);
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


void print_semana_completa(gpointer key, gpointer value, gpointer user_data) {
    (void)key; // Se não for usado
    (void)user_data; // Ignora user_data, se não for usado

    Domingo *domingo = (Domingo *)value;

    if (domingo == NULL) {
        fprintf(stderr, "Erro: Domingo é NULL.\n");
        return;
    }

    if (get_artisthistorido_dedomingo(domingo) == NULL) {
        fprintf(stderr, "Erro: Hash Table artistahistory é NULL.\n");
        return;
    }

    printf("----- Hash Table DOMINGO da semana %s -----\n", domingo->data);
    g_hash_table_foreach(get_artisthistorido_dedomingo(domingo), print_artisthistory_entry, NULL);
    printf("----- Fim da Hash Table DOMINGO da semana %s -----\n", domingo->data);
}
