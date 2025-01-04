#ifndef VALIDAARTISTAS_H
#define VALIDAARTISTAS_H

#include "Output.h"


/**
 * @brief Função para validar a entrada de um artista (individual ou grupo).
 * 
 * Esta função verifica se o tipo do artista é válido (individual ou grupo) e também valida a formatação do campo "grupo".
 * - Se o tipo for "individual", o campo "grupo" deve ser vazio.
 * - Se o tipo for "group", o campo "grupo" deve ser uma lista válida (ex: ["artista1", "artista2"]).
 * 
 * @param grupo String representando os membros do grupo ou uma lista vazia.
 * @param type Tipo do artista, que pode ser "individual" ou "group".
 * @param linha Linha de entrada que contém as informações do artista.
 * @param erros Ponteiro para a estrutura de erros, onde as mensagens de erro serão armazenadas.
 * @return Retorna 1 se a validação for bem-sucedida, 0 caso contrário.
 */
int validaArtista(char* grupo, char* type, char* linha, Output* erros);

#endif