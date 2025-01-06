/**
 * @file users.h
 * @brief Definições relacionadas à manipulação de utilizadores e agrupamento por idade.
 * 
 * Este ficheiro contém a definição das estruturas `User` e `Age`, além das funções associadas 
 * que permitem manipular os dados de utilizadores e as suas estatísticas por idade.
 */

#ifndef USERS_H
#define USERS_H

#include "controler/musicsController.h"


/**
 * @brief Estrutura que representa um utilizador.
 */
typedef struct users User;

/**
 * @brief Estrutura que agrupa utilizadores por idade.
 */
typedef struct usersByAge Age;

typedef struct query5 Query5;

/**
 * @brief Cria uma nova instância de `User` e coloca os tokens nos respetivos lugares.
 * 
 * @param tokens Array de strings que contém os parametros do utilizador.
 * @return Pointer para a nova estrutura `User`.
 */
User* newUser(char** tokens,int posicaoChegada);

/**
 * @brief Liberta a memória alocada para um utilizador.
 * 
 * @param user Pointer para a estrutura `User` a ser liberada.
 */
void freeUser(User* user);

/**
 * @brief Imprime(Printa) todos os parametros que constituem uma estrutura 'User'.
 * 
 * @param user Pointer para a estrutura `User`.
 */
void printUser(User* user);





//GETTERS E SETTERS USER
/**
 * @brief Getter do email do utilizador.
 * 
 * @param user Pointer para a estrutura `User`.
 * @return Cópia do email do utilizador.
 */
char* getUserEmail(User* user);

/**
 * @brief Getter do nome do utilizador.
 * 
 * @param user Pointer para a estrutura `User`.
 * @return Cópia do nome do utilizador.
 */
char* getUserNome(User* user);

/**
 * @brief Getter do apelido do utilizador.
 * 
 * @param user Pointer para a estrutura `User`.
 * @return Cópia do apelido do utilizador.
 */
char* getUserApelido(User* user);

/**
 * @brief Getter da data de nascimento do utilizador.
 * 
 * @param user Pointer para a estrutura `User`.
 * @return Cópia da string com a data de nascimento do utilizador.
 */
char* getUserBirthDate(User* user);

/**
 * @brief Getter do país do utilizador.
 * 
 * @param user Pointer para a estrutura `User`.
 * @return Cópia da string com o país do utilizador.
 */
char* getUserCountry(User* user);

/**
 * @brief Getter do tipo de subscrição do utilizador.
 * 
 * @param user Pointer para a estrutura `User`.
 * @return Cópia da string com o tipo de subscrição do utilizador.
 */
char* getUserSubscryptionType(User* user);

/**
 * @brief Getter do número de músicas favoritas do utilizador.
 * 
 * @param user Pointer para a estrutura `User`.
 * @return Número de músicas favoritas do utilizador.
 */
int getUserNumberLikedSongs(User* user);


/**
 * @brief Cria uma nova estrutura para agrupar utilizadores por idade.
 * 
 * @return Pointer para a estrutura `Age`.
 */
Age* createUsersAge();



//GETTERS E SETTERS UBA
/**
 * @brief Obtém o número de músicas de um género específico ou total para uma idade.
 * 
 * @param userAge Pointer para a estrutura `Age`.
 * @param idade Idade dos utilizadores.
 * @param i Índice do género (ou -1 para total).
 * @return Número de músicas.
 */
int getUBANumberSongs(Age* userAge, int idade, int i);

/**
 * @brief Getter do género musical de uma idade em um índice específico.
 * 
 * @param userAge Pointer para a estrutura `Age`.
 * @param idade Idade dos utilizadores.
 * @param i Índice do género.
 * @return Pointer para uma string com o género musical.
 */
char* getGenero(Age* userAge, int idade, int i);

/**
 * @brief Getter do número de géneros musicais para uma idade específica.
 * 
 * @param userAge Pointer para a estrutura `Age`.
 * @param idade Idade dos utilizadores.
 * @return Número de géneros musicais.
 */
int getNGeneros(Age* userAge, int idade);

/**
 * @brief Setter de um género musical associado a uma idade.
 * 
 * @param usersByAge Pointer para a estrutura `Age`.
 * @param idade Idade dos utilizadores.
 * @param genero Pointer para uma string com o género musical.
 * @return Pointer atualizado para a estrutura `Age`.
 */
Age* insertGenero(Age* usersByAge, int idade, char* genero);

/**
 * @brief Liberta a memória alocada para a estrutura de agrupamento por idade.
 * 
 * @param usersByAge Pointer para a estrutura `Age` a ser libertada.
 */
void freeUsersByAge(Age* usersByAge);


/**
 * @brief Cria e inicializa uma nova estrutura Query5.
 * 
 * A função aloca memória para a estrutura `Query5` e inicializa seus campos com valores padrão. 
 * A estrutura Query5 é usada para armazenar as preferências dos usuários relacionadas a gêneros musicais.
 * 
 * @param musicController Ponteiro para a estrutura MusicData, usada para acessar dados relacionados a músicas e gêneros.
 * @return Ponteiro para a estrutura Query5 recém-criada e inicializada.
 */
Query5* createQ5Struct(MusicData* musicController);

/**
 * @brief Libera a memória alocada para a estrutura Query5.
 * 
 * A função desaloca toda a memória alocada pela estrutura Query5, incluindo arrays de strings e inteiros, 
 * e os GArrays usados para armazenar as preferências dos usuários e os IDs dos usuários.
 * 
 * @param q5 Ponteiro para a estrutura Query5 a ser liberada.
 */
void freeQ5struct(Query5* q5);

/**
 * @brief Atualiza a preferência de um usuário em relação a um gênero musical.
 * 
 * A função verifica se o gênero já foi registrado na estrutura de preferências de `Query5`. 
 * Se não, o gênero é adicionado à lista. Em seguida, a preferência do usuário para esse gênero é incrementada.
 * 
 * @param genero Nome do gênero musical.
 * @param q5 Ponteiro para a estrutura Query5 onde as preferências dos usuários são armazenadas.
 * @param user Ponteiro para a estrutura User que representa o usuário cuja preferência está sendo atualizada.
 */
void atualizaGeneros(char* genero, Query5* q5, User* user);

/**
 * @brief Cria uma nova linha de preferências para um usuário na estrutura Query5.
 * 
 * A função cria uma nova linha de preferências, inicializando todas as preferências de gênero para zero, 
 * e a insere na estrutura de preferências de `Query5`.
 * 
 * @param posicaoChegada Posição do usuário que está sendo adicionado à estrutura de preferências.
 * @param q5 Ponteiro para a estrutura Query5 onde as preferências dos usuários são armazenadas.
 */
void criaLinhaPreferencia(int posicaoChegada, Query5* q5);

/**
 * @brief Insere o ID de um usuário na estrutura Query5.
 * 
 * A função adiciona o ID de um usuário à lista de IDs de usuários na estrutura `Query5`.
 * 
 * @param username Nome de usuário a ser adicionado.
 * @param q5 Ponteiro para a estrutura Query5 onde os IDs dos usuários são armazenados.
 */
void inserirUserQ5(char* username, Query5* q5);


/**
 * @brief Obtém uma matriz de inteiros representando as preferências dos usuários em relação aos gêneros.
 * 
 * A função aloca memória para uma matriz 2D onde cada linha contém as preferências de um usuário para todos os gêneros.
 * As preferências são copiadas a partir da estrutura Query5.
 * 
 * @param q5 Ponteiro para a estrutura Query5 que contém as preferências dos usuários.
 * @return Ponteiro para uma matriz 2D de inteiros representando as preferências dos usuários.
 */
int** getPreferenciasQ5(Query5* q5);

/**
 * @brief Obtém um array de strings com os IDs dos usuários.
 * 
 * A função aloca memória para um array de strings onde cada string é o ID de um usuário, 
 * e as strings são copiadas da estrutura Query5.
 * 
 * @param q5 Ponteiro para a estrutura Query5 que contém os IDs dos usuários.
 * @return Ponteiro para um array de strings representando os IDs dos usuários.
 */
char** getUsersId(Query5* q5);

/**
 * @brief Obtém um array de strings com os nomes dos gêneros registrados na Query5.
 * 
 * A função aloca memória para um array de strings onde cada string é o nome de um gênero, 
 * e os nomes dos gêneros são copiados da estrutura Query5.
 * 
 * @param q5 Ponteiro para a estrutura Query5 que contém os nomes dos gêneros.
 * @return Ponteiro para um array de strings representando os nomes dos gêneros.
 */
char** getGenerosNomes(Query5* q5);

/**
 * @brief Retorna o número de usuários na estrutura Query5.
 * 
 * A função retorna o número total de usuários armazenados na estrutura Query5.
 * 
 * @param q5 Ponteiro para a estrutura Query5 que contém a informação sobre o número de usuários.
 * @return Número de usuários registrados na estrutura Query5.
 */
int getnumUsers(Query5* q5);

/**
 * @brief Retorna o número de gêneros na estrutura Query5.
 * 
 * A função retorna o número total de gêneros registrados na estrutura Query5.
 * 
 * @param q5 Ponteiro para a estrutura Query5 que contém a informação sobre o número de gêneros.
 * @return Número de gêneros registrados na estrutura Query5.
 */
int getnumGeneros(Query5* q5);

/**
 * @brief Retorna a posição de chegada de um usuário na estrutura User.
 * 
 * A função retorna a posição de chegada do usuário, representada por um número inteiro.
 * 
 * @param user Ponteiro para a estrutura User que contém a informação sobre a posição de chegada.
 * @return A posição de chegada do usuário.
 */
int getPosicaoChegada(User* user);
#endif
