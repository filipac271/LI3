#ifndef QUERY5_H
#define QUERY5_H
#include "controler/usersController.h"

/**
 * @brief Libera a memória alocada para as matrizes e arrays usados na query 5.
 * 
 * Esta função libera a memória associada às matrizes e arrays usados na query 5:
 * - A matriz de elementos (`elementosMatriz`), que armazena dados de recomendações.
 * - O array de IDs de usuários (`idsUsers`).
 * - O array de nomes de gêneros musicais (`nomesGeneros`).
 * 
 * As matrizes e arrays são liberados de forma adequada para evitar vazamentos de memória.
 * 
 * @param elementosMatriz Matriz de elementos contendo os dados de recomendações.
 * @param idsUsers Array contendo os IDs dos usuários.
 * @param nomesGeneros Array contendo os nomes dos gêneros musicais.
 * @param userControllador Controlador de usuários, usado para obter o número de linhas e colunas das matrizes.
 * 
 */
void freeQ5Matrizes(int** elementosMatriz, char** idsUsers, char** nomesGeneros, UsersData* userControllador);

/**
 * @brief Realiza a query 5 e gera recomendações de usuários com base nas preferências de um usuário.
 * 
 * Esta função processa a linha de entrada extraindo o ID do usuário e o número de recomendações
 * a serem geradas. Com base nos dados do controlador de usuários e nas matrizes de recomendações, a função gera um arquivo
 * de saída contendo os IDs dos usuários recomendados.
 * 
 * @param line Linha de entrada contendo o comando e parâmetros (ID do usuário e número de recomendações).
 * @param i Número da query, usado para gerar o nome do arquivo de saída.
 * @param userControllador Controlador contendo os dados dos usuários.
 * @param elementosMatriz Matriz de elementos que armazena os dados de recomendações.
 * @param idsUsers Array de IDs de usuários.
 * @param nomesGeneros Array de nomes de gêneros musicais.
 */
void query5(char* line, int i, UsersData* userControllador, int** elementosMatriz, char** idsUsers, char** nomesGeneros);


#endif