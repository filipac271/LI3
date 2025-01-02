#ifndef MUSICSCONTROLLER_H
#define MUSICSCONTROLLER_H
#include "Entitys/musics.h"
#include "controler/artistsController.h"
#include "controler/albumsController.h"

/**
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
 * @brief Procura uma música pelo seu ID.
 * 
 * @param controller Ponteiro para a estrutura MusicData.
 * @param music_id ID da música a ser procurada.
 * @return Ponteiro para a música encontrada, ou NULL se não encontrada.
 */
Music* lookup_musica(MusicData* controller, int music_id);

/**
 * @brief Imprime uma entrada da tabela de músicas.
 * 
 * @param key Chave da entrada (por exemplo, o ID da música).
 * @param value Valor associado à entrada (dados da música).
 * @param user_data Dados adicionais fornecidos pelo utilizador.
 */
void print_music_entry(gpointer key, gpointer value, gpointer user_data);

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


#endif