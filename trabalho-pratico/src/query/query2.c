#include "controler/artistsController.h"
#include "utilidades.h"
#include "Entitys/artists.h"
#include "Output.h"
#include "query/query2.h"

#include <stdio.h>
#include <stdlib.h>
#include <glib.h>
#include <unistd.h>

struct discografia{
    int artist_id;
    int segundos;
};


Discography* create_discography(int artist_id, int segundos){
    Discography* n_discography = malloc(sizeof(Discography));

    if (n_discography == NULL) {
        fprintf(stderr, "Memory allocation failed for novo Discography\n"); //this is line 123
        exit(1);
    }

    n_discography->artist_id = artist_id;
    n_discography->segundos = segundos;

    return n_discography;
}


void free_discografia (Discography* atual){
    if(atual == NULL){
    return;
    } 

    free(atual);
}



// Função de comparação para ordenar pela discografia em ordem decrescente
gint compare_discography(gconstpointer a, gconstpointer b) {

    Discography *artist_a = *(Discography **)a;
    Discography *artist_b = *(Discography **)b;

    int disc_a = (artist_a->segundos);
    int disc_b = (artist_b->segundos);

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




void query2(ArtistsData* ArtistController, char* line, int i) {
    int n;
    char country[256] = "";  // String para armazenar o país, inicializada como string vazia

    // Limpa a string `country` antes de processar cada linha
    strcpy(country, "");

    // Lê o número e a string entre aspas, se existir
    int query2_result = sscanf(line + 2, "%d \"%[^\"]\"", &n, country);
    if (query2_result == 1) {
        // Apenas o número foi lido, país não fornecido
        strcpy(country, "");  // Define `country` como string vazia
    }

    GArray* q2 = filter_and_sort_hash_table_by_discography(ArtistController, country);
    guint length = get_garray_length(q2);


    char* filename = malloc(sizeof(char) * 256);
    sprintf(filename, "resultados/command%d_output.txt", i + 1);
    Output* output = iniciaOutput(filename);


    // name 1;type 1;discography duration 1;country 1
    int j = 0;
    if (n == 0) {
        outputNULL(output);
    } else {
        while (j < n && j < (int)length) {
            Discography* artist_atual = g_array_index(q2, Discography*, j);

            int id = artist_atual->artist_id;

            int discography = (artist_atual->segundos);
            if(discography == 0)break;
            
            char* time = seconds_to_hhmmss(discography);

            char* nome = getArtistNameControl(ArtistController, id);
            char* tipo = getArtistTypeControl(ArtistController, id);
            char* pais = getArtistCountryControl(ArtistController, id);

            output2(output, nome, tipo, time, pais, line[1]);

            free(nome);
            free(tipo);
            free(pais);
            free(time);
            j++;
        }
    }

    for(guint i = 0; i < q2->len; i++){
        Discography* artist_atual = g_array_index(q2, Discography*, i);

        free_discografia(artist_atual);
    }

    g_array_free(q2, TRUE);
    free(filename);
    freeOutput(output);
}