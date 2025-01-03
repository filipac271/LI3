#ifndef MAINCONTROLLER_H
#define MAINCONTROLLER_H
#include <stdio.h>
#include "controler/usersController.h"
#include "controler/artistsController.h"
#include "controler/musicsController.h"
#include "controler/albumsController.h"
#include "controler/historyController.h"

/**
 * @typedef mainController
 * @brief Estrutura principal que centraliza os controladores de dados do sistema.
 * 
 * Esta estrutura contém controladores para gerenciar artistas, músicas,
 * usuários, álbuns e histórico de atividades.
 */
typedef struct mainController MainController;

/**
 * @brief Inicializa o MainController com dados provenientes da diretoria fornecida.
 * 
 * @param diretoria Caminho para a diretoria contendo os arquivos de dados.
 * @return Ponteiro para a estrutura MainController inicializada ou NULL em caso de diretoria inválida.
 */
MainController* mainFeed(char* diretoria);

/**
 * @brief Liberta a memória alocada pelo MainController e todos os seus subcomponentes.
 * 
 * @param data Ponteiro para a estrutura MainController a ser destruída.
 */
void destroyData(MainController* data);

/**
 * @brief Imprime todas as informações armazenadas no MainController.
 * 
 * @param data Ponteiro para a estrutura MainController.
 */
void print_all_Data(MainController* data);

/**
 * @brief Obtém o controlador de usuários.
 * 
 * @param data Ponteiro para o MainController.
 * @return Ponteiro para a estrutura UsersData.
 */
UsersData* getUserController(MainController* data);

/**
 * @brief Obtém o controlador de músicas.
 * 
 * @param data Ponteiro para o MainController.
 * @return Ponteiro para a estrutura MusicData.
 */
MusicData* getMusicController (MainController* data);

/**
 * @brief Obtém o controlador de artistas.
 * 
 * @param data Ponteiro para o MainController.
 * @return Ponteiro para a estrutura ArtistsData.
 */
ArtistsData* getartistController (MainController* data);

/**
 * @brief Obtém o controlador de álbuns.
 * 
 * @param data Ponteiro para o MainController.
 * @return Ponteiro para a estrutura AlbumsData.
 */
AlbumsData* getalbumController (MainController* data);

/**
 * @brief Obtém o controlador de histórico.
 * 
 * @param data Ponteiro para o MainController.
 * @return Ponteiro para a estrutura HistoryData.
 */
HistoryData* gethistoryController (MainController* data);

#endif