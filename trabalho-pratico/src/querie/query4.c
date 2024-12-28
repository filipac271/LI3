#include "controler/artistsController.h"
#include "controler/historyController.h"
#include "controler/musicsController.h"
#include "utilidades.h"
#include "Entitys/artists.h"
#include "Entitys/history.h"
#include "Entitys/musics.h"
#include "Output.h"
#include "querie/query4.h"


#include <stdio.h>
#include <stdlib.h>
#include <glib.h>
#include <unistd.h>


int id_maiores_ocorrencias(GHashTable* domingo, int* maior_n_ocorrencias) {
    //Criamos a hash table auxiliar
    GHashTable* hash_auxiliar = g_hash_table_new_full(g_int_hash, g_int_equal, free, free);

    GHashTableIter iter;
    gpointer key, value;

    int max_ocorrencias = -1;
    int mais_freq_artist = -1;

    //Começamos a ver A hashtable externa
    g_hash_table_iter_init(&iter, domingo);

    while (g_hash_table_iter_next(&iter, &key, &value)) {
        //hash table externa
        Domingo* semana_atual = (Domingo*)value;
        //GArray interno
        GArray* top_semanal = get_garray_from_domingo(semana_atual);

        for (int i = 0; i < (int)top_semanal->len; i++) {
            //Vamos iterar o GArray interno
            UmArtista* artista_atual = g_array_index(top_semanal, UmArtista*, i);
            
            int id_atual = get_artist_id_from_garray(artista_atual);

            // Aloca memória para a chave para evitar usar algo local 
            int* id_atual_ptr = g_new(int, 1);
            *id_atual_ptr = id_atual;

            // Verifica se a chave já existe na hash table
            int* ocorrencia_atual_ptr = g_hash_table_lookup(hash_auxiliar, id_atual_ptr);

            if (!ocorrencia_atual_ptr) {
                // Não existe na tabela; inicializa com 1
                int* nova_ocorrencia = g_new(int, 1);
                *nova_ocorrencia = 1;
                g_hash_table_insert(hash_auxiliar, id_atual_ptr, nova_ocorrencia);
               // g_free(nova_ocorrencia);
            } else {
                // Já existe; incrementa
                (*ocorrencia_atual_ptr)++;
                g_free(id_atual_ptr); // Libera a chave alocada para evitar duplicação
            }

            // Atualiza o artista mais frequente
            int ocorrencia_atual = ocorrencia_atual_ptr ? *ocorrencia_atual_ptr : 1;



            if (ocorrencia_atual > max_ocorrencias || 
                (ocorrencia_atual == max_ocorrencias && id_atual < mais_freq_artist)) {
                max_ocorrencias = ocorrencia_atual;
                mais_freq_artist = id_atual;
                *maior_n_ocorrencias = max_ocorrencias;
            }
        }
    }

    g_hash_table_destroy(hash_auxiliar);
    return mais_freq_artist;
}




//Assume-se que as datas recebidas por esta funcao já sao os domingos 
int artista_mais_frequente_com_data (GHashTable* semanas, char* data_inicio, char* data_fim, int *ocorrencia_final){
    int artista_mais_frequente = -1;
    int max_ocorrencias = 0;

    GHashTable* contador_artistas = g_hash_table_new_full(g_int_hash, g_int_equal, free, free);
    // Iterar sobre as semanas no intervalo
    GHashTableIter iter;
    gpointer key, value;
    g_hash_table_iter_init(&iter, semanas);

if (data_inicio != NULL && data_fim != NULL && strcmp(data_inicio, "") != 0 && strcmp(data_fim, "") != 0) {
    while (g_hash_table_iter_next(&iter, &key, &value)) {

        char data_atual[11]; 
        calcularDomingoAnterior((char*)key, data_atual);
        // Verificar se está no intervalo
        if ( strcmp(data_atual, data_inicio) >=0 && strcmp(data_atual, data_fim) <= 0) {
        //hash table externa
        Domingo* semana_atual = (Domingo*)value;
        //GArray interno
        GArray* top_semanal = get_garray_from_domingo(semana_atual);

            // Processar o GArray (top 10 artistas)
            for (int i = 0; i < (int)top_semanal->len; i++) {

                UmArtista* artista_atual = g_array_index(top_semanal, UmArtista*, i);

                int id_atual = get_artist_id_from_garray(artista_atual);

                // Aloca memória para a chave para evitar usar algo local 
                int* id_atual_ptr = g_new(int, 1); 
                *id_atual_ptr = id_atual;

                // Verifica se a chave já existe na hash table
                int* ocorrencia_atual_ptr = g_hash_table_lookup(contador_artistas, id_atual_ptr);

                if (!ocorrencia_atual_ptr) {
                    // Não existe na tabela; inicializa com 1
                    int* nova_ocorrencia = g_new(int, 1); 
                    *nova_ocorrencia = 1;
                    g_hash_table_insert(contador_artistas, id_atual_ptr, nova_ocorrencia);

                } else {
                    // Já existe; incrementa
                    (*ocorrencia_atual_ptr)++;
                    g_free(id_atual_ptr); // Liberta a chave para nao correr o risco de haver algum tipo de duplicaçao
                }

                int ocorrencia_atual = ocorrencia_atual_ptr ? *ocorrencia_atual_ptr : 1;
                
                if (ocorrencia_atual > max_ocorrencias 
                || (ocorrencia_atual == max_ocorrencias && id_atual < artista_mais_frequente)){
                    max_ocorrencias = ocorrencia_atual;
                    artista_mais_frequente = id_atual;
                    *ocorrencia_final =  max_ocorrencias;

                }
            }
        }
    }
}
    //DEBUG
    // if (artista_mais_frequente != -1) {
    //     printf("O artista mais frequente no top 10 foi o ID %d, com %d ocorrências.\n", artista_mais_frequente, max_ocorrencias);
    // } else {
    //     printf("Nenhum artista encontrado no intervalo especificado.\n");
    // }

    g_hash_table_destroy(contador_artistas);
    return artista_mais_frequente;
}



void query4 (HistoryData* HistoryController, ArtistsData* ArtistController, char* line, int i){

    char data_inicio[11] = ""; 
    char data_fim[11] = "";

    int query4_result = sscanf(line + 2, "%s %s", data_inicio, data_fim);  // Lê o intervalo de idades (min e max) a partir da linha de entrada
    int artist_id = 0;
    int ocorrencias = 0;


    if(query4_result < 2){
        artist_id = id_maiores_ocorrencias((get_Domingo_from_HD(HistoryController)),&ocorrencias);

        } else {
        char* domingo_inicio = malloc(11 * sizeof(char));
        calcularDomingoAnterior(data_inicio, domingo_inicio);

        char* domingo_final = malloc(11 * sizeof(char));
        calcularDomingoAnterior(data_fim, domingo_final);

        artist_id = artista_mais_frequente_com_data((get_Domingo_from_HD(HistoryController)), domingo_inicio, domingo_final, &ocorrencias);

        free(domingo_inicio);
        free(domingo_final);
        }

    char* filename = malloc(sizeof(char) * 256);
    sprintf(filename, "resultados/command%d_output.txt", i + 1);
    Output* output = iniciaOutput(filename);

    Artist* artista_atual = lookup_artist(ArtistController, artist_id);
    char id_em_char[10]; // Tamanho suficiente para "A0000000" + '\0'
    destransforma_IDs(artist_id, id_em_char);

    char* tipo = getArtistType(artista_atual);

    output4(output, id_em_char, tipo, (ocorrencias), line[1]);

    free(tipo);
    free(filename);
    freeOutput(output);
}
