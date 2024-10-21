#include "../../include/controler/usersController.h"
#include "../../include/controler/musicsController.h"
#include "controler/usersController.h"
#include "utilidades.h"
#include "Entitys/musics.h"
#include "Entitys/artists.h"
#include "querie/querie2.h"


#include <stdio.h>
#include <stdlib.h>
#include <glib.h>

guint get_garray_length(GArray *array) {
    if (array == NULL) {
        return 0; // Retorna 0 se o GArray for NULL
    }
    return array->len; // Retorna o tamanho do GArray
}

char* seconds_to_hhmmss(int total_seconds) {
    // Aloca memória para a string de saída
    char *time_string = malloc(9); // hh:mm:ss + \0 = 9 caracteres
    if (time_string == NULL) {
        return NULL; // Verifica se a alocação foi bem-sucedida
    }

    // Calcula horas, minutos e segundos
    int hours = total_seconds / 3600;
    int minutes = (total_seconds % 3600) / 60;
    int seconds = total_seconds % 60;

    // Formata a string no formato hh:mm:ss
    snprintf(time_string, 9, "%02d:%02d:%02d", hours, minutes, seconds);

    return time_string;
}





//funcao auxiliar apenass para confirmar que esta tudo okay
void print_info_array(GArray *array) {
    // Itera sobre o array de artistas
    for (guint i = 0; i < array->len; i++) {
        // Obtém o ponteiro para cada estrutura Info_M no array
        struct Info_M *artist = g_array_index(array, struct Info_M *, i);
        
        // Usa os getters para acessar e imprimir cada campo
        printf("Artist ID: %s\n", get_dinfo_id(artist));
        printf("Discography: %d\n", get_dinfo_discography(artist));
        printf("Artist Country: %s\n", get_dinfo_country(artist));
        printf("---------------------------\n");
    }
}


// Função de comparação para ordenar pela discografia em ordem decrescente
gint compare_discography(gconstpointer a, gconstpointer b) {
    const struct Info_M *artist_a = *(const struct query2 **)a;
    const struct Info_M *artist_b = *(const struct query2 **)b;

    int disc_a = get_dinfo_discography(artist_a);
    int disc_b = get_dinfo_discography(artist_b);


    // Compara pela discografia (ordem decrescente)
    return (disc_b - disc_a);
}

// Função para filtrar a hash table e ordenar o array pela discografia
GArray* filter_and_sort_hash_table_by_discography(GHashTable *D_Info_original, char *country) {
    GArray *filtered_array = g_array_new(FALSE, FALSE, sizeof(struct Info_M*));
    
    // Itera sobre a hash table e aplica o filtro apenas se 'country' não for NULL
    GHashTableIter iter;
    gpointer key, value;

    g_hash_table_iter_init(&iter, D_Info_original);
    while (g_hash_table_iter_next(&iter, &key, &value)) {
        struct Info_M* dinfo_to_filter = (struct Info_M*) value;

        // Se 'country' não for NULL, aplica a filtragem pelo país
        if (country == NULL || strcmp(country, "") == 0 || strcmp(get_dinfo_country(dinfo_to_filter), country) == 0) {
            // Se country for NULL, ou se o país do artista corresponder ao fornecido, adiciona ao array
            g_array_append_val(filtered_array, dinfo_to_filter);
        }
    }

    // Ordena o array pela discografia em ordem decrescente
    g_array_sort(filtered_array, (GCompareFunc)compare_discography);

    return filtered_array;
}



void querie2(GHashTable* dinfo_Original, GHashTable* Artist_Original, int n, int i, char* country){
  //printf("COUNTRY DO INICIO DA FUNCAO QUERIE2: %s\n", country);
  

  GArray* q2 = filter_and_sort_hash_table_by_discography(dinfo_Original, country);
  if(country == " "){
    print_info_array(q2);
  }

  guint length = get_garray_length(q2);

 // printf("NAO SEI SE ISTO IMPRIME  %d\n", length);
  if(length == 0){
    print_info_array(q2);
  }

char *filename = malloc(sizeof(char) * 256);
  sprintf(filename, "resultados/command%d_output.txt",i+1);
  FILE *output_file = fopen(filename, "w");


  //printf("COUNTRY: %s\n",country);

    //printf("TENTATIVA DE DESCOBRIR ERRO DOS SEM COUNTRY: %d\n", n);
  // name 1;type 1;discography duration 1;country 1
    int j = 0;
    if(n == 0){
      fprintf(output_file,"\n");
    }else{
    while(j < n && j < length && country != ""){
     // printf("COntinuo sem ideias %d\n", n);
    
    struct Info_M *artist_atual = g_array_index(q2, struct Info_M *, j);

    //printf("CHEGOU AQUI \n");

    //printf("O ID DO ARTISTA ATUAL %s\n", get_dinfo_id(artist_atual));

   // printf("Nem ideia %d\n", j);
  
    char* id_atual = get_dinfo_id(artist_atual);

    //printf("O ID DO ARTISTA ATUAL2 %s\n", id_atual);

    //printf("PAROU AQUI ????\n");

    Artist *original = g_hash_table_lookup(Artist_Original, id_atual);
    char* time = seconds_to_hhmmss(get_dinfo_discography(artist_atual));


      // name 1;type 1;discography duration 1;country 1

      fprintf(output_file,"%s;%s;%s;%s\n",getArtistName(original), getArtistType(original), time, getArtistCountry(original));

      free(time);
      j++;
  }
    }


    g_array_free(q2, TRUE);

//certamente faltam dar mais frees
free(filename);
fclose(output_file);

}