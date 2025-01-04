/**
 * @file artists.h
 * @brief Definições relacionadas à manipulação de artistas.
 * 
 * Este ficheiro contém a definição da estrutura `Artist` e as funções associadas 
 * para manipular os dados de artistas, como getters e setters de determinados campos assim como para libertar memória.
 */

#ifndef ARTISTS_H
#define ARTISTS_H

/** VER SE É PRECISO MAIS ALGUMA COISA
 * @brief Estrutura que representa um artista.
 */
typedef struct artists Artist;

/**
 * @brief Getter do ID de um artista.
 * 
 * @param artista Pointer para a estrutura Artist.
 * @return Cópia do campo ID de um artista.
 */
int getArtistId(Artist* artista);

/**
 * @brief Getter do nome de um artista.
 * 
 * @param artista Pointer para a estrutura Artist.
 * @return Cópia do campo nome de um artista
 */
char* getArtistName(Artist* artista);

/**
 * @brief Getter do campo ganho de um artista..
 * 
 * @param artista Pointer para a estrutura Artist.
 * @return Ganho financeiro do artista.
 */
double getArtistGanho(Artist* artista);

/**
 * @brief Obtém o país do artista.
 * 
 * @param artista Pointer para a estrutura Artist.
 * @return Pointer para uma string com o país do artista.
 */
char* getArtistCountry(Artist* artista);

/**
 * @brief Getter do tipo de artista(i.e. individual ou grupo).
 * 
 * @param artista Pointer para a estrutura Artist.
 * @return Cópia do campo type de um artista
 */
char* getArtistType(Artist* artista);

/**
 * @brief Getter da quantidade de membros de um grupo.
 * 
 * @param artista Pointer para a estrutura Artist.
 * @return O número de membros.
 */
int getArtistNumMembros(Artist* artista);

/**
 * @brief Getter da discografia de um artista em segundos
 * 
 * @param artista Pointer para a estrutura Artist.
 * @return Número de discos na discografia do artista.
 */
int getArtistDiscography(Artist* artista);

/**
 * @brief Setter para definir a discografia em segundos de um artista.
 * 
 * @param artista Pointer para a estrutura Artist.
 * @param discography Segundos de musica de determinado artista
 */
void setArtistDiscography(Artist* artista, int discography);

/**
 * @brief Cria uma nova instância de `Artist` e coloca os tokens nos respetivos lugares.
 * 
 * @param tokens Array de strings com os parametros do artista.
 * @return Pointer para a nova estrutura `Artist`.
 */
Artist* create_artist(char** tokens);

/**
 * @brief Imprime (Printa) todos os campos que constiruem um Artist.
 * 
 * @param artist Pointer para a estrutura Artist.
 */
void print_artist(Artist* artist);

/**
 * @brief Liberta a memória alocada para um artista.
 * 
 * @param artist Pointer para a estrutura Artist que será libertada.
 */
void free_artist(Artist* artist);


/**
 * @brief Atualiza o lucro total de um artista com base no número de streams.
 * 
 * @param artista Ponteiro para o artista a ser atualizado.
 * @param stream Valor dos lucros obtidos com streams.
 */
void setStreams(Artist* artista, double stream);

/**
 * @brief Incrementa o número de álbuns individuais do artista.
 * 
 * @param artista Ponteiro para o artista a ser atualizado.
 */
void setAlbuns(Artist* artista);

/**
 * @brief Obtém o lucro total de um artista.
 * 
 * @param artista Ponteiro para o artista.
 * @return Lucro total do artista.
 */
double getArtistProfits(Artist* artista);

/**
 * @brief Obtém o número de álbuns individuais do artista.
 * 
 * @param artista Ponteiro para o artista.
 * @return Número de álbuns individuais do artista.
 */
int getArtistAlbunsIndividuais(Artist* artista);

/**
 * @brief Obtém os IDs dos membros do grupo de um artista.
 * 
 * @param artista Ponteiro para o artista.
 * @return Array dinâmico contendo os IDs dos membros do grupo. 
 *         O utilizador deve liberar a memória alocada para este array após o uso.
 */
int* getArtistGrupo(Artist* artista);

#endif
