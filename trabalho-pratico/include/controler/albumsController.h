#ifndef ALBUNSCONTROLLER_H
#define ALBUNSCONTROLLER_H
#include <glib.h>
#include <stdlib.h>
#include <stdio.h>
#include "Entitys/albums.h"
#include "controler/artistsController.h"

/**
 * @typedef 
 * @brief Estrutura do Controller do Albums 
 */
typedef struct albumsData AlbumsData;

/**
 * @brief Inicializa a estrutura de dados de albums a partir de um diretório.
 * 
 * @param diretoria String representando o caminho do diretório com os dados.
 * @param artistController Ponteiro para os dados dos artistas.
 * @return Ponteiro para a estrutura AlbumsData inicializada.
 */
AlbumsData* albumsFeed(char* diretoria, ArtistsData* artistController);


/**
 * @brief Liberta a memória alocada pela Hash Table contida em AlbumsData.
 * 
 * Esta função destrói a tabela hash contida na estrutura AlbumsData, liberando 
 * todos os recursos associados.
 * 
 * @param AlbumData Ponteiro para a estrutura AlbumsData contendo a tabela hash.
 */
void destroyTableAlbum(AlbumsData* AlbumData);


/**
 * @brief Procura um álbum na tabela hash usando o ID como chave.
 * 
 * Esta função busca um álbum na tabela hash contida em AlbumsData com base no 
 * ID fornecido.
 * 
 * @param controller Ponteiro para a estrutura AlbumsData contendo a tabela hash.
 * @param id ID do álbum a ser procurado.
 * @return Ponteiro para o álbum correspondente, ou NULL se o ID não for encontrado.
 */
Album* lookup_album(AlbumsData* controller, int id);

/**
 * @brief Imprime todos os álbuns na tabela hash.
 * 
 * Esta função percorre a tabela hash contida em AlbumsData e imprime todos os albums.
 * 
 * @param data Ponteiro para a estrutura AlbumsData contendo a tabela hash.
 */
void print_all_albums(AlbumsData* data);

#endif