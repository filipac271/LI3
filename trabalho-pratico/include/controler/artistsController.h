#ifndef ARTISTSCONTROLLER_H
#define ARTISTSCONTROLLER_H
#include <glib.h>
#include "Entitys/artists.h"

/**
 * @typedef 
 * @brief Estrutura do Controller dos artistas
 */
typedef struct artistsData ArtistsData;

/**
 * @brief Cria e preenche a estrutura ArtistsData a partir de um diretório.
 * 
 * Esta função inicializa a tabela hash de artistas, valida os dados e insere artistas válidos na tabela.
 * Linhas inválidas são registradas no arquivo "artists_errors.csv".
 * 
 * @param diretoria Caminho para o diretório onde o arquivo "artists.csv" está localizado.
 * @return Ponteiro para a estrutura ArtistsData preenchida.
 */
ArtistsData* artistFeed(char* diretoria);

/**
 * @brief Soma a duração de uma música à discografia dos artistas.
 * 
 * Esta função converte a duração de uma música para segundos e atribui entre os membros de um grupo.
 * Ou a soma diretamente ao artista individual.
 * 
 * @param controller Ponteiro para ArtistsData contendo a tabela hash de artistas.
 * @param music_durationAspas Duração da música como string (com aspas).
 * @param music_artists IDs dos artistas da música como string.
 */
void inserir_discography_into_artist (ArtistsData* controller, char* music_durationAspas, char* music_artists);



/**
 * @brief Imprime todos os artistas na tabela hash.
 * 
 * @param data Ponteiro para ArtistsData contendo a tabela hash de artistas.
 */
void print_all_artists(ArtistsData* data);

/**
 * @brief Liberta a memória alocada pela tabela hash em ArtistsData.
 * 
 * Esta função destrói a tabela hash de artistas e libera os recursos associados.
 * 
 * @param ArtistData Ponteiro para a estrutura ArtistsData a ser liberada.
 */
void destroyTableArtist(ArtistsData* ArtistData);


/**
 * @brief Filtra artistas por país e os insere em um GArray.
 * 
 * @param controller Ponteiro para ArtistsData contendo a tabela hash de artistas.
 * @param array GArray onde os artistas filtrados serão inseridos.
 * @param country Nome do país usado como critério de filtragem.
 */
void fill_filtered_artists(ArtistsData* controller, GArray *array, char *country);

/**
 * @brief Atualiza os streams de artistas com base em tipos e ganhos.
 * 
 * Esta função calcula os ganhos de streams e os distribui entre artistas individuais ou grupos.
 * 
 * @param numartistas Número de artistas no array.
 * @param arrayArtistas Array de IDs dos artistas.
 * @param controller Ponteiro para ArtistsData contendo a tabela hash de artistas.
 */
void put_stream_into_Artist (int numartistas, int* arrayArtistas, ArtistsData* controller);

/**
 * @brief Atualiza os álbuns associados a artistas.
 * 
 * Esta função incrementa o contador de álbuns dos artistas listados no array fornecido.
 * 
 * @param arrayAlbuns String com IDs dos artistas cujos álbuns serão atualizados.
 * @param controller Ponteiro para ArtistsData contendo a tabela hash de artistas.
 */
void atualizaAlbuns (char* arrayAlbuns, ArtistsData* controller);

/**
 * @brief Obtém o nome de um artista pelo ID.
 * 
 * @param controlador Ponteiro para ArtistsData contendo a tabela hash de artistas.
 * @param id ID do artista.
 * @return Nome do artista como string.
 */
char* getArtistNameControl(ArtistsData* controlador, int id);

/**
 * @brief Obtém o país de um artista pelo ID.
 * 
 * @param controlador Ponteiro para ArtistsData contendo a tabela hash de artistas.
 * @param id ID do artista.
 * @return País do artista como string.
 */
char* getArtistCountryControl(ArtistsData* controlador, int id);


/**
 * @brief Obtém o tipo de um artista pelo ID.
 * 
 * @param controlador Ponteiro para ArtistsData contendo a tabela hash de artistas.
 * @param id ID do artista.
 * @return Tipo do artista como string.
 */
char* getArtistTypeControl(ArtistsData* controlador, int id);

/**
 * @brief Obtém o número de álbuns individuais de um artista.
 * 
 * @param controlador Ponteiro para ArtistsData contendo a tabela hash de artistas.
 * @param id ID do artista.
 * @return Número de álbuns individuais.
 */
int getArtistAlbunsIndividuaisControl(ArtistsData* controlador, int id);

/**
 * @brief Obtém os lucros de um artista pelo ID.
 * 
 * @param controlador Ponteiro para ArtistsData contendo a tabela hash de artistas.
 * @param id ID do artista.
 * @return Lucro do artista como double.
 */
double getArtistProfitsControl(ArtistsData* controlador, int id);

/**
 * @brief Obtém a discografia de um artista pelo ID.
 * 
 * @param controlador Ponteiro para ArtistsData contendo a tabela hash de artistas.
 * @param id ID do artista.
 * @return Duração total da discografia em segundos.
 */
int getArtistDiscographyControl(ArtistsData* controlador, int id);


/**
 * @brief Verifica se um artista com o ID fornecido é válido.
 * 
 * @param controlador Ponteiro para ArtistsData contendo a tabela hash de artistas.
 * @param id ID do artista a ser validado.
 * @return 1 se o artista não existe, 0 caso contrário.
 */
int isArtistValid (ArtistsData* controlador , int id);



#endif