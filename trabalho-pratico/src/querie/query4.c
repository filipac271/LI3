#include "controler/artistsController.h"
#include "controler/historyController.h"
#include "controler/musicsController.h"
#include "utilidades.h"
#include "Entitys/artists.h"
#include "Entitys/history.h"
#include "Entitys/musics.h"
#include "Output.h"

#include <stdio.h>
#include <stdlib.h>
#include <glib.h>
#include <unistd.h>

/* Query 4 ideias
adicionar um parametro de usado ao  historico -Feito
transformar os dias em domingos com a funcao que faz isso //fazer isso na funcao de query mesmo
percorrer a primeira hashtable e colocar ou num array auziliar ou numa hashtable auxiliar, mas provavelmente array
ir percorrendo todas as hashtables até estar tudo com o parametro usado
Ordenar o array

PENSAR TALVEZ EM ALGO DIFERENTE PARA QUANDO NAO hOUVER DATA

struct artistahistory{
  int artist_id;
  int totalsemanalsegundos; //passar a duration de hh:mm:ss (funcao defenida nas utilities) 
  int usado; // 1-usado; 0-por usar
};

struct domingo{
  char* data ;
  GHashTable* artistahistory;
};
*/

// Estrutura para acumular dados de artistas
struct artista_total {
    int artist_id;
    int total_segundos;
};

// Função para comparar os artistas pelo total de segundos ouvidos
int compare_artistas(const void* a, const void* b) {
    struct artista_total* art_a = (struct artista_total*)a;
    struct artista_total* art_b = (struct artista_total*)b;
    return art_b->total_segundos - art_a->total_segundos; // Decrescente
}


GHashTable* put_artists_into_auxHT(GHashTable* domingos, const char* inicio, const char* fim) {
    GHashTableIter iter;
    gpointer key, value;
    GHashTable* artistas_acumulados = g_hash_table_new_full(g_int_hash, g_int_equal, free, free);

    // Iterar pelos domingos no intervalo de tempo
    g_hash_table_iter_init(&iter, domingos);
    while (g_hash_table_iter_next(&iter, &key, &value)) {
        Domingo* dom = (Domingo*)value;

        // Verificar se o domingo está dentro do intervalo
        char* data_domingo_atual = get_history_data(dom);
        if (strcmp(data_domingo_atual, inicio) >= 0 && strcmp(data_domingo_atual, fim) <= 0) {
            GHashTableIter artist_iter;
            gpointer artist_key, artist_value;

            // Iterar pelos artistas do domingo atual
            GHashTable* artistahistorico_atual = get_artisthistorido_dedomingo(dom);
            g_hash_table_iter_init(&artist_iter, artistahistorico_atual);
            while (g_hash_table_iter_next(&artist_iter, &artist_key, &artist_value)) {
                UmArtista* artista = (UmArtista*)artist_value;
                if (get_usado_from_artist(artista) == 0) {

                  //coiso do garray
                    int id = get_id_from_Umartista(artista);

                    // Acumular os segundos
                    int* total = g_hash_table_lookup(artistas_acumulados, GINT_TO_POINTER(id));
                    if (total == NULL) {
                        total = malloc(sizeof(int)); //este total pode dar problemas
                        *total = 0;
                        g_hash_table_insert(artistas_acumulados, GINT_TO_POINTER(id), total);
                    }
                    *total += get_total_de_segundos_from_Umartista(artista);
                    set_usado_to_used(artista); // Marcar como usado
                }
            }
        }
//ver se isto funciona aqui
        free(data_domingo_atual);
    }  
    return artistas_acumulados;
}

GArray* transform_and_ord (GHashTable* artistas_acumulados){
  GHashTableIter iter;
  gpointer key, value;
  GArray* artistas_totais = g_array_new(FALSE, FALSE, sizeof(struct artista_total)); //rever isto
    g_hash_table_iter_init(&iter, artistas_acumulados);
    while (g_hash_table_iter_next(&iter, &key, &value)) {
        struct artista_total artista;
        artista.artist_id = *(int*)key;
        artista.total_segundos = *(int*)value;
        g_array_append_val(artistas_totais, artista);
    }

    g_array_sort(artistas_totais, compare_artistas);

  return artistas_totais;
}



//name;type;count_top_10
//4S 2022/12/09 2024/05/02

void query4 (HistoryData* HistoryController, char* line, int i){
  char* data_inicio;
  char* data_fim;

  int query4_result = sscanf(line + 2, "%d %d", &data_inicio, &data_fim);  // Lê o intervalo de idades (min e max) a partir da linha de entrada

  if(query4_result == 0){

  } 
  char* domingo_inicio = calcular_domingo_anterior(data_inicio);
  char* domingo_final = calcular_domingo_anterior(data_fim);

  GHashTable* aux =put_artists_into_auxHT(HistoryController, domingo_inicio, domingo_final);

  GArray* q4 = transform_and_ord(aux);
  guint length = get_garray_length(q4);

    char* filename = malloc(sizeof(char) * 256);
    sprintf(filename, "resultados/command%d_output.txt", i + 1);
    Output* output = iniciaOutput(filename);

  int j = 0;
  while(j < 10 && j < (int)length){
    
  }
}








