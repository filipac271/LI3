#ifndef MUSICSCONTROLLER_H
#define MUSICSCONTROLLER_H
#include "Entitys/musics.h"
#include "controler/artistsController.h"
#include "controler/albumsController.h"

/**
 * @typedef
 * @brief Estrutura que representa os dados de músicas.
 */
typedef struct musicData MusicData;

/**
 * @brief Inicializa a estrutura de dados de músicas a partir de um diretório.
 * 
 * @param diretoria String representando o caminho do diretório com os dados.
 * @param artistsData Ponteiro para os dados dos artistas.
 * @param albumData Ponteiro para os dados dos álbuns.
 * @return Ponteiro para a estrutura MusicData inicializada.
 */
MusicData* musicsFeed(char* diretoria, ArtistsData* artistsData, AlbumsData* albumData);




/**
 * @brief Imprime todas as músicas armazenadas.
 * 
 * @param musica Ponteiro para a estrutura MusicData contendo os dados das músicas.
 */
void print_all_musics(MusicData* musica);

/**
 * @brief Liberta a memória associada à estrutura MusicData.
 * 
 * @param data Ponteiro para a estrutura MusicData a ser libertada.
 */
void destroyMusicData(MusicData* data);

/**
 * @brief Obtém o número de géneros musicais diferentes.
 * 
 * @param musicController Ponteiro para a estrutura MusicData.
 * @return Número de géneros musicais diferentes.
 */
int getnumGenerosDif(MusicData* musicController);

/**
 * @brief Atualiza o número de streams de uma música.
 * 
 * @param idMusica ID da música cuja contagem de streams será atualizada.
 * @param musicController Ponteiro para a estrutura MusicData.
 * @param artistcontroller Ponteiro para o controlador de dados dos artistas.
 */
void atualizaStreams(char* idMusica, MusicData* musicController, ArtistsData* artistcontroller);

/**
 * @brief Obtém o género de uma música.
 * 
 * @param idMusic Ponteiro para o ID da música.
 * @param musicController Ponteiro para a estrutura MusicData.
 * @param type Tipo do dado a ser obtido (por exemplo, como string ou número).
 * @return String representando o género da música.
 */
char* getMusicGenreControl(void* idMusic, MusicData* musicController, char type);

/**
 * @brief Obtém o número de artistas associados a uma música.
 * 
 * @param musicController Ponteiro para a estrutura MusicData.
 * @param id ID da música.
 * @return Número de artistas associados à música.
 */
int getnumartistaMusicControl(MusicData* musicController, int id);

/**
 * @brief Obtém um array de IDs de artistas associados a uma música.
 * 
 * @param musicController Ponteiro para a estrutura MusicData.
 * @param id ID da música.
 * @param numartistas Número de artistas associados à música.
 * @return Ponteiro para um array de IDs de artistas.
 */
int* getarrayArtistasMusicControl(MusicData* musicController, int id, int numartistas);

/**
 * @brief Obtém o ID de uma música.
 * 
 * @param musicController Ponteiro para o controlador de músicas.
 * @param id ID da música a ser pesquisada.
 * @return ID da música. 
 */
int get_music_id_control(MusicData* musicController, int id);

/**
 * @brief Obtém o título de uma música.
 * 
 * @param musicController Ponteiro para o controlador de músicas.
 * @param id ID da música a ser pesquisada.
 * @return Ponteiro para o título da música. 
 */
char* get_music_title_control(MusicData* musicController, int id);

/**
 * @brief Obtém a duração de uma música como string.
 * 
 * @param musicController Ponteiro para o controlador de músicas.
 * @param id ID da música a ser pesquisada.
 * @return Ponteiro para a string que representa a duração da música. 
 */
char* get_music_duration_control(MusicData* musicController, int id);

/**
 * @brief Obtém a duração de uma música em segundos.
 * 
 * @param musicController Ponteiro para o controlador de músicas.
 * @param id ID da música a ser pesquisada.
 * @return Duração da música em segundos. 
 */
int get_music_duration_seconds_control(MusicData* musicController, int id);

/**
 * @brief Obtém o ano de uma música.
 * 
 * @param musicController Ponteiro para o controlador de músicas.
 * @param id ID da música a ser pesquisada.
 * @return Ponteiro para o ano da música como string. 
 */
char* get_music_year_control(MusicData* musicController, int id);

/**
 * @brief Obtém o id do album de uma música.
 * 
 * @param musicController Ponteiro para o controlador de músicas.
 * @param id ID da música a ser pesquisada.
 * @return Id do Album da música como int. 
 */
int get_musicAlbum(MusicData* musicController , int musicId);

/**
 * @brief Verifica se uma música com o ID fornecido é válida.
 * 
 * @param controlador Ponteiro para o controlador de músicas.
 * @param id ID da música a ser verificada.
 * @return 1 se a música não existir (inválida), 0 se a música existir (válida).
 */
int isMusicValid (MusicData* controlador , int id);

#endif