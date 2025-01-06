#ifndef ALBUNSCONTROLLER_H
#define ALBUNSCONTROLLER_H
#include <glib.h>
#include <stdlib.h>
#include <stdio.h>
#include "Entities/albums.h"
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
 * @brief Obtém o nome do album.
 * 
 * @param albumController Ponteiro para a estrutura AlbumsData que contém a tabela hash.
 * @param albumId Id do album cujo nome é procurado.
 * @return nome do album em string.
 */
char* get_Album_Name(AlbumsData* albumController, int albumId);

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
 * @brief Imprime todos os álbuns na tabela hash.
 * 
 * Esta função percorre a tabela hash contida em AlbumsData e imprime todos os albums.
 * 
 * @param data Ponteiro para a estrutura AlbumsData contendo a tabela hash.
 */
void print_all_albums(AlbumsData* data);


/**
 * @brief Verifica se um álbum com o ID fornecido é válido.
 * 
 * @param controlador Ponteiro para o controlador de álbuns.
 * @param id ID do álbum a ser verificado.
 * @return 1 se o álbum não existir (inválido), 0 se o álbum existir (válido).
 */
int isAlbumValid(AlbumsData* controlador,int id);

#endif