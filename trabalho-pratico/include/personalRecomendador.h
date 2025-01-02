#ifndef PERSONALRECOMENDADOR_H
#define PERSONALRECOMENDADOR_H

/**
 * @file personalRecomendador.h
 * @brief Biblioteca para recomendação de utilizadores com gostos musicais semelhantes.
 *
 * Este módulo fornece funcionalidades para calcular e retornar uma lista de utilizadores
 * com gostos semelhantes a um utilizador-alvo, com base em uma matriz de classificações.
 */

/**
 * @struct Recomendacao
 * @brief Estrutura que armazena a recomendação de um utilizador.
 *
 * @var Recomendacao::idUtilizador
 * ID do utilizador recomendado.
 *
 * @var Recomendacao::somaDiferencas
 * Soma das diferenças de gostos entre o utilizador-alvo e o utilizador recomendado.
 */
typedef struct recomendacao Recomendacao;

/**
 * @brief Recomenda utilizadores com gostos semelhantes ao utilizador-alvo.
 *
 * Esta função analisa uma matriz de classificações de músicas, comparando os gostos
 * de cada utilizador com os do utilizador-alvo. Ela retorna uma lista de utilizadores
 * recomendados, ordenada pela semelhança de gostos.
 *
 * @param idUtilizadorAlvo ID do utilizador para o qual as recomendações serão feitas.
 * @param matrizClassificacaoMusicas Matriz onde cada linha representa um utilizador
 *                                    e cada coluna um gênero musical, com o número
 *                                    de músicas ouvidas como valores.
 * @param idsUtilizadores Vetor de strings com os IDs dos utilizadores.
 * @param nomesGeneros Vetor de strings com os nomes dos gêneros musicais.
 * @param numUtilizadores Número total de utilizadores.
 * @param numGeneros Número total de gêneros musicais.
 * @param numRecomendacoes Número máximo de recomendações a retornar.
 * @return Um vetor de strings com os IDs dos utilizadores recomendados.
 *         Se o utilizador-alvo não for encontrado, retorna `NULL`.
 */
char **recomendaUtilizadoresP(
    char *idUtilizadorAlvo,
    int **matrizClassificacaoMusicas,
    char **idsUtilizadores,
    char **nomesGeneros,
    int numUtilizadores,
    int numGeneros,
    int numRecomendacoes
);

#endif 
