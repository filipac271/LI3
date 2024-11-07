#include "../../include/controler/usersController.h"
#include "../../include/controler/musicsController.h"
#include "controler/usersController.h"
#include "utilidades.h"
#include "Entitys/musics.h"
#include "Entitys/artists.h"
#include "querie/querie2.h"
#include "IOManager.h"

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
//para tirar os warnigns é mudar o 9 para 16 mas ocupa mais memoria
    char *time_string = malloc(16); // hh:mm:ss + \0 = 9 caracteres
    if (time_string == NULL) {
        return NULL; // Verifica se a alocação foi bem-sucedida
    }

    // Calcula horas, minutos e segundos
    int hours = total_seconds / 3600;
    int minutes = (total_seconds % 3600) / 60;
    int seconds = total_seconds % 60;

    // Formata a string no formato hh:mm:ss
//mudar aqui tambem para 16 caso se queira tirar os warning
    snprintf(time_string, 16, "%02d:%02d:%02d", hours, minutes, seconds);

    return time_string;
}

//REVER ESTA FUNCAO
// Função de comparação para ordenar pela discografia em ordem decrescente
gint compare_discography(gconstpointer a, gconstpointer b) {

    Artist *artist_a = *(Artist **)a;
    Artist *artist_b = *(Artist **)b;

    int disc_a = getArtistDiscography(artist_a);
    int disc_b = getArtistDiscography(artist_b);

    int r = disc_b - disc_a;



    // Compara pela discografia (ordem decrescente)
    return (r);
}

// Função para filtrar a hash table e ordenar o array pela discografia
GArray* filter_and_sort_hash_table_by_discography(ArtistsData* controller, char *country) {
    // Cria o array no módulo de processamento
    GArray *filtered_array = g_array_new(FALSE, FALSE, sizeof(struct Artist*));

    // Preenche o array no módulo de hash table
    fill_filtered_artists(controller, filtered_array, country);

    // Ordena o array após preenchê-lo
    g_array_sort(filtered_array, (GCompareFunc)compare_discography);

    return filtered_array;
}







void querie2(ArtistsData* ArtistController, int n, int i, char* country){
  //printf("COUNTRY DO INICIO DA FUNCAO QUERIE2: %s\n", country);
  

  GArray* q2 = filter_and_sort_hash_table_by_discography(ArtistController, country);

  guint length = get_garray_length(q2);

char *filename = malloc(sizeof(char) * 256);
  sprintf(filename, "resultados/command%d_output.txt",i+1);
  Output* output= iniciaOutput(filename);
  

  // name 1;type 1;discography duration 1;country 1
    int j = 0;
    if(n == 0){
      outputNULL(output);
    }else{
    while(j < n && j < (int)length){
    
     Artist *artist_atual = g_array_index(q2,Artist*, j);


   // char* id_atual = getArtistId(artist_atual);

    int discography = getArtistDiscography(artist_atual);
// Artist *original = g_hash_table_lookup(Artist_Original, id_atual);
    char* time = seconds_to_hhmmss(discography);


      // name 1;type 1;discography duration 1;country 1
      char* nome = getArtistName(artist_atual);
      char* tipo = getArtistType(artist_atual);
      char* pais = getArtistCountry(artist_atual);
      output2(output,nome,tipo,time,pais);
      free(nome);
      free(tipo);      
      free(pais);
      free(time);
      j++;
  }
    }


    g_array_free(q2, TRUE);

free(filename);
freeOutput(output);


}
