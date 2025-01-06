#ifndef QUERIE6_H
#define QUERIE6_H

#include "controler/historyController.h"
#include <glib.h>
#include "controler/albumsController.h"
#include <glib.h>
#include "controler/artistsController.h"


 /**
 * @brief Executa a Query 6.
 *
 *  Esta função realiza a operação associada à Query 6. Utilizando os dados do histórico do utilizador no ano pedido, 
 * recolhe as informações estatísticas necessárias:tempo de audição total, número de músicas ouvidas, artista favorito, 
 * dia em que reproduziu mais músicas, género e album favoritos e a hora do dia em que o user costuma ouvir mais músicas. 
 *  Se for pedido a função também devolve os N artistas mais ouvidos, as suas músicas que o utilizador ouviu
 * e o tempo total de audição.
 *
 * @param i Número do comando.
 * @param line String contendo a linha de entrada a ser processada.
 * @param historyController Pointer para a estrutura HistoryData que contem os dados do histórico que serão processados.
 * @param musicController Pointer para a estrutura MusicData que contem alguns dados necessários para responder à query.
 * @param albumController Pointer para a estrutura AlbumsData que contem alguns dados necessários para responder à query.
 */
void query6(int i, char * line, HistoryData* historyController,MusicData* musicController, AlbumsData* albumController);

#endif