#include "controler/artistsController.h"
#include "controler/historyController.h"
#include "controler/musicsController.h"
#include "utilidades.h"
#include "Entities/artists.h"
#include "Entities/history.h"
#include "Entities/musics.h"
#include "Output.h"
#include "query/query4.h"


#include <stdio.h>
#include <stdlib.h>
#include <glib.h>
#include <unistd.h>


void query4 (HistoryData* HistoryController, ArtistsData* ArtistController, char* line, int i){

    char data_inicio[11] = ""; 
    char data_fim[11] = "";

    int query4_result = sscanf(line + 2, "%s %s", data_inicio, data_fim);  // Lê o intervalo de idades (min e max) a partir da linha de entrada
    int artist_id = 0;
    int ocorrencias = 0;

    if(query4_result < 2){
        artist_id = id_maiores_ocorrencias(HistoryController ,&ocorrencias);

        } else {
        char* domingo_inicio = malloc(11 * sizeof(char));
        calcularDomingoAnterior(data_inicio, domingo_inicio);

        char* domingo_final = malloc(11 * sizeof(char));
        calcularDomingoAnterior(data_fim, domingo_final);

        artist_id = artista_mais_frequente_com_data(HistoryController, domingo_inicio, domingo_final, &ocorrencias);

        free(domingo_inicio);
        free(domingo_final);
        }

    char* filename = malloc(sizeof(char) * 256);
    sprintf(filename, "resultados/command%d_output.txt", i + 1);
    Output* output = iniciaOutput(filename);

    int artistvalido = isArtistValid(ArtistController, artist_id);
    if(artistvalido == 1){
        outputNULL(output);
    } else{
    char id_em_char[10]; // Tamanho suficiente para "A0000000" + '\0'
    destransforma_IDs(artist_id, id_em_char);

    char* tipo = getArtistTypeControl(ArtistController, artist_id);

    output4(output, id_em_char, tipo, (ocorrencias), line[1]);

    free(tipo);

    }
    
    free(filename);
    freeOutput(output);
}
