#ifndef VALIDAHISTORY_H
#define VALIDAHISTORY_H

#include "Output.h"

/**
 * @brief Função para validar as informações de um history.
 * 
 * Esta função valida o tipo de plataforma e a duração do history. A plataforma deve ser "mobile" ou "desktop".
 * A duração deve ser uma string válida representando o tempo. Se a validação falhar em algum desses critérios,
 * a função registra um erro.
 * 
 * @param plataform Plataforma do history, que pode ser "mobile" ou "desktop".
 * @param duration Duração do history, que deve ser validada pela função `validaDuracao`.
 * @param Erros Ponteiro para a estrutura de erros, onde as mensagens de erro serão armazenadas.
 * @param linha Linha de entrada que contém as informações do history.
 * @return Retorna 1 se a validação for bem-sucedida, 0 caso contrário.
 */
int validaHistory(char* plataform, char* duration, Output* Erros, char* linha);

#endif