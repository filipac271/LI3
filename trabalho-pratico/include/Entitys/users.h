/**
 * @file users.h
 * @brief Definições relacionadas à manipulação de utilizadores e agrupamento por idade.
 * 
 * Este ficheiro contém a definição das estruturas `User` e `Age`, além das funções associadas 
 * que permitem manipular os dados de utilizadores e as suas estatísticas por idade.
 */

#ifndef USERS_H
#define USERS_H

/**
 * @brief Estrutura que representa um utilizador.
 */
typedef struct users User;

/**
 * @brief Estrutura que agrupa utilizadores por idade.
 */
typedef struct usersByAge Age;

/**
 * @brief Cria uma nova instância de `User` e coloca os tokens nos respetivos lugares.
 * 
 * @param tokens Array de strings que contém os parametros do utilizador.
 * @return Pointer para a nova estrutura `User`.
 */
User* newUser(char** tokens);

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

#endif
