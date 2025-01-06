#ifndef QUERIE1_H
#define QUERIE1_H
#include <glib.h>
#include "controler/usersController.h"
#include "controler/artistsController.h"

/**
 * @brief Executa a primeira query e gera um arquivo de saída com informações sobre o usuário ou artista.
 *
 * Esta função realiza os seguintes passos:
 * - Recebe uma linha com os dados da query e determina se a consulta é para um usuário ou artista.
 * - Se for um usuário, busca informações sobre o usuário e gera a saída correspondente.
 * - Se for um artista, busca informações sobre o artista e gera a saída correspondente.
 * - A saída é salva em um arquivo gerado dinamicamente com o nome "commandN_output.txt", onde N é o número da query.
 * - Caso o ID fornecido seja inválido, a função retorna sem gerar nenhuma saída.
 *
 * @param userController Controlador que contém os dados dos usuários.
 * @param line Linha de entrada contendo os parâmetros da query.
 * @param i Índice da query, usado para nomear o arquivo de saída.
 * @param artistController Controlador que contém os dados dos artistas.
 *
 */
void query1(UsersData *userController, char *line, int i, ArtistsData *artistController);

#endif