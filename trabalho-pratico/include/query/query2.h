#ifndef QUERIE2_H
#define QUERIE2_H
#include <glib.h>
#include "controler/artistsController.h"
#include "utilidades.h"

/**
 * @brief Estrutura que representa a discografia de um artista.
 */
typedef struct discografia Discography;

/**
 * @brief Cria uma nova estrutura de discografia para um artista.
 * 
 * @param artist_id ID do artista associado à discografia.
 * @param segundos Tempo total, em segundos, associado à discografia.
 * @return Ponteiro para a nova estrutura Discography criada.
 */
Discography* create_discography(int artist_id, int segundos);

/**
 * @brief Processa a Query 2 com base nos dados dos artistas.
 * 
 * @param ArtistController Ponteiro para a estrutura ArtistsData que controla os dados dos artistas.
 * @param line Linha de entrada contendo as informações necessárias para a Query 2.
 * @param i Índice atual que pode ser usado como referência no processamento.
 * 
 * Esta função executa a lógica associada à Query 2, que geralmente envolve manipular ou analisar 
 * os dados dos artistas com base na entrada fornecida.
 */
void query2(ArtistsData* ArtistController, char* line, int i);

#endif

