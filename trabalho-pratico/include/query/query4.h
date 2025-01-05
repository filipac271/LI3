#ifndef QUERY4_H
#define QUERY4_H
#include <glib.h>
#include "controler/artistsController.h"
#include "utilidades.h"

/**
 * @brief Executa a Query 4.
 *
 * Esta função realiza a operação associada à Query 4, utilizando os dados
 * do histórico de execução e dos artistas para processar uma linha específica.
 *
 * @param HistoryController Pointer para a estrutura HistoryData que contem os dados do historico que serão trabalhados.
 * @param ArtistController Pointer para a estrutura ArtistData que contem alguns dados necessarios para responder à query.
 * @param line String contendo a linha de entrada a ser processada.
 * @param i Índice atual que pode ser usado como referência no processamento.
 */
void query4 (HistoryData* HistoryController, ArtistsData* ArtistController, char* line, int i);


#endif