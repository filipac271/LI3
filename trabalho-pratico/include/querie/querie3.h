#ifndef QUERIE3_H
#define QUERIE3_H
#include <glib.h>
#include "controler/usersController.h"
#include "utilidades.h"

/**
 * @typedef
 * @brief Estrutura para armazenar informações sobre os géneros musicais e o número de músicas associadas.
 */
typedef struct querie3 Genero;


/**
 * @brief Realiza a consulta de géneros musicais para um intervalo de idades e grava os resultados em um arquivo.
 * 
 * Esta função processa uma linha de entrada contendo um intervalo de idades e, para cada idade dentro desse intervalo,
 * consulta os géneros musicais e a quantidade de músicas associada a cada género. Os géneros são então ordenados e
 * gravados em um arquivo de saída. Se o intervalo de idades não contiver géneros válidos, o arquivo de saída será
 * gerado com informações vazias.
 * 
 * @param num Número da consulta, usado para gerar o nome do arquivo de saída.
 * @param line Linha de entrada contendo o intervalo de idades.
 * @param userController Controlador contendo os dados dos usuários.
 * 
 */
void querie3(int num, char* line, UsersData* userController);

#endif