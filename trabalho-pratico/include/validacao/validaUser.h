#ifndef VALIDAUSER_H
#define VALIDAUSER_H


#include"controler/musicsController.h"
#include "Output.h"

/**
 * @brief Função para validar as informações de um usuário.
 * 
 * Esta função valida o e-mail, a data, o tipo de usuário, as músicas curtidas e outras informações associadas a um usuário. 
 * A validação é feita de acordo com as seguintes condições:
 * 1. A lista de músicas curtidas deve estar corretamente formatada com `[ ]`.
 * 2. O tipo de usuário deve ser "premium" ou "normal".
 * 3. A data deve ser válida (através da função `validaData`).
 * 4. O e-mail deve ser válido (através da função `validaEmail`).
 * 5. As músicas curtidas (listadas em `songs`) devem existir no controlador de músicas, sendo cada ID de música válido.
 * Se qualquer uma dessas condições falhar, um erro será registrado.
 * 
 * @param email E-mail do usuário.
 * @param date Data associada ao usuário.
 * @param type Tipo do usuário ("premium" ou "normal").
 * @param musicsController Ponteiro para o controlador de músicas.
 * @param songs Lista de músicas curtidas pelo usuário, formatada entre `[]`.
 * @param numSongs Número de músicas na lista de músicas curtidas.
 * @param Erros Ponteiro para a estrutura de erros, onde as mensagens de erro serão armazenadas.
 * @param linha Linha de entrada contendo os dados do usuário.
 * @return Retorna 1 se todas as validações forem bem-sucedidas, 0 caso contrário.
 */
int validaUser(char* email, char* date, char* type, MusicData* musicsController, char* songs, int numSongs, Output* Erros, char* linha);


#endif