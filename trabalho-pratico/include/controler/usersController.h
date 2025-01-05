#ifndef USERSCONTROLLER_H
#define USERSCONTROLLER_H

#include "Entitys/users.h"
#include "controler/musicsController.h"


/**
 * @typedef
 * @brief Estrutura que representa os dados dos usuários.
 */
typedef struct usersData UsersData;


/**
 * @brief Alimenta o controlador de usuários (UsersData) a partir de um diretório de dados.
 * 
 * @param diretoria Caminho para o diretório contendo o ficheiro com os dados dos usuários.
 * @param musicData Ponteiro para a estrutura MusicData associada.
 * @return Ponteiro para a estrutura UsersData inicializada.
 */
UsersData* usersFeed(char* diretoria, MusicData* musicData);

/**
 * @brief Procura um usuário na hash table pelo username.
 * 
 * @param controlador Ponteiro para a estrutura UsersData.
 * @param username ID do usuário a ser buscado.
 * @return Ponteiro para a estrutura User encontrada ou NULL caso não exista.
 */
User* fetchUser(UsersData* controlador, int username);


/**
 * @brief Imprime toda a hash table de usuários.
 * 
 * @param data Ponteiro para a estrutura UsersData.
 */
void print_all_users(UsersData* data);

/**
 * @brief Destrói a estrutura UsersData, liberando toda a memória alocada.
 * 
 * @param data Ponteiro para a estrutura UsersData a ser destruída.
 */
void destroyUsersData(UsersData* data);

/**
 * @brief Obtém o gênero de música no array usersByAge de uma idade específica na posição i.
 * 
 * @param userController Ponteiro para a estrutura UsersData.
 * @param idade Idade do usuário.
 * @param i Posição no array.
 * @return Cópia do gênero encontrado.
 */
char* getUBAGenero(UsersData * userController, int idade, int i);

/**
 * @brief Obtém o número de músicas no array usersByAge de uma idade específica na posição j.
 * 
 * @param userController Ponteiro para a estrutura UsersData.
 * @param idade Idade do usuário.
 * @param j Posição no array.
 * @return Número de músicas.
 */
int getUBANSongs(UsersData* userController, int idade, int j);

/**
 * @brief Obtém o número de gêneros no array usersByAge de uma idade específica.
 * 
 * @param userController Ponteiro para a estrutura UsersData.
 * @param idade Idade do usuário.
 * @return Número de gêneros.
 */
int getUBANGeneros(UsersData * userController, int idade);

/**
 * @brief Atualiza as preferências de um usuário com base em um gênero de música.
 * 
 * @param generoMusica Nome do gênero musical.
 * @param username ID do usuário.
 * @param userController Ponteiro para a estrutura UsersData.
 */
void atualizaPrefsUser(char* generoMusica, char* username, UsersData* userController);

/**
 * @brief Obtém os elementos da matriz de preferências (Q5) de usuários.
 * 
 * @param userController Ponteiro para a estrutura UsersData.
 * @return Ponteiro para a matriz de preferências.
 */
int** getElementosMatrizQ5(UsersData* userController);

/**
 * @brief Obtém as linhas da matriz de preferências (Q5) de usuários.
 * 
 * @param userController Ponteiro para a estrutura UsersData.
 * @return Ponteiro para o array de IDs dos usuários.
 */
char** getLinhasMatrizQ5(UsersData* userController);

/**
 * @brief Obtém as colunas da matriz de preferências (Q5) de usuários.
 * 
 * @param userController Ponteiro para a estrutura UsersData.
 * @return Ponteiro para o array de nomes dos gêneros.
 */
char** getColunasMatrizQ5(UsersData* userController);

/**
 * @brief Obtém o número de linhas na matriz de preferências (Q5).
 * 
 * @param userController Ponteiro para a estrutura UsersData.
 * @return Número de linhas.
 */
int getNumLinhas(UsersData* userController);

/**
 * @brief Obtém o número de colunas na matriz de preferências (Q5).
 * 
 * @param userController Ponteiro para a estrutura UsersData.
 * @return Número de colunas.
 */
int getNumColunas(UsersData* userController);

/**
 * @brief Obtém a posição de chegada de um usuário baseado no username.
 * 
 * @param userController Ponteiro para a estrutura UsersData.
 * @param username ID do usuário.
 * @return Posição de chegada ou -1 se o usuário não for encontrado.
 */
int getPosicaoUser(UsersData* userController, char* username);

/**
 * @brief Obtém a data de nascimento de um usuário.
 * 
 * @param controlador Ponteiro para a estrutura UsersData.
 * @param username ID do usuário.
 * @return Ponteiro para a data de nascimento do usuário.
 */
char* getUserBirthDateControl(UsersData* controlador, int username);

/**
 * @brief Obtém o e-mail de um usuário.
 * 
 * @param controlador Ponteiro para a estrutura UsersData.
 * @param username ID do usuário.
 * @return Ponteiro para o e-mail do usuário.
 */
char* getUserEmailControl(UsersData* controlador, int username);

/**
 * @brief Obtém o nome de um usuário.
 * 
 * @param controlador Ponteiro para a estrutura UsersData.
 * @param username ID do usuário.
 * @return Ponteiro para o nome do usuário.
 */
char* getUserNomeControl(UsersData* controlador, int username);

/**
 * @brief Obtém o apelido de um usuário.
 * 
 * @param controlador Ponteiro para a estrutura UsersData.
 * @param username ID do usuário.
 * @return Ponteiro para o apelido do usuário.
 */
char* getUserApelidoControl(UsersData* controlador, int username);

/**
 * @brief Obtém o país de um usuário.
 * 
 * @param controlador Ponteiro para a estrutura UsersData.
 * @param username ID do usuário.
 * @return Ponteiro para o país do usuário.
 */
char* getUserCountryControl(UsersData* controlador, int username);

/**
 * @brief Obtém o tipo de subscrição de um usuário.
 * 
 * @param controlador Ponteiro para a estrutura UsersData.
 * @param username ID do usuário.
 * @return Ponteiro para o tipo de subscrição do usuário.
 */
char* getUserSubscryptionTypeControl(UsersData* controlador, int username);

/**
 * @brief Verifica se um usuário é válido.
 * 
 * @param controlador Ponteiro para a estrutura UsersData.
 * @param userName ID do usuário.
 * @return 1 se válido, 0 caso contrário.
 */
int isUserValid(UsersData* controlador, int userName);

#endif
