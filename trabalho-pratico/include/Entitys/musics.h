/**
 * @file musics.h
 * @brief Definições relacionadas à manipulação de músicas.
 * 
 * Este ficheiro contém a definição da estrutura `Music` e as funções associadas 
 * que permitem manipular os dados de músicas, nomeadamente getters e setter e  libertação de memória.
 */

#ifndef MUSICS_H
#define MUSICS_H

/**
 * @brief Estrutura que representa uma música.
 */
typedef struct music Music;

/**
 * @brief Cria uma nova instância de `Music` e coloca os tokens no seu devido lugar.
 * 
 * @param tokens Array de strings que contêm os dados que constituirão esta estrutura.
 * @return Pointer para a nova estrutura `Music`.
 */
Music* new_music(char** tokens);

/**
 * @brief Liberta a memória alocada para uma música.
 * 
 * @param musica Pointer para a estrutura `Music` a ser liberada.
 */
void free_musica(Music* musica);

/**
 * @brief Imprime(Printa) todos os parametros que constituem uma estrutura 'Music'.
 * 
 * @param musica Pointer para a estrutura `Music`.
 */
void print_musicas(Music* musica);

/**
 * @brief Getter para o ID da música.
 * 
 * @param music Pointer para a estrutura `Music`.
 * @return Cópia do campo ID de uma musica.
 */
int get_music_id(Music* music);

/**
 * @brief Getter para o título da música.
 * 
 * @param music Pointer para a estrutura `Music`.
 * @return Cópia de uma string com o título da música.
 */
char* get_music_title(Music* music);

/**
 * @brief Getter da duração da musica no formato 'hh:mm:ss'
 * 
 * @param music Pointer para a estrutura `Music`.
 * @return PCópia da duração da música no formato 'hh:mm:ss'.
 */
char* get_music_duration(Music* music);

/**
 * @brief Realiza as contas necessárias para passar o campo de music_duration do formato 'hh:mm:ss' para segundos.
 * 
 * @param music_duration String representando a duração da música (formato hh:mm:ss).
 * @return Duração em segundos.
 */
int duration_to_seconds(char* music_duration);

/**
 * @brief Getter para a duração da música em segundos.
 * 
 * @param musica Pointer para a estrutura `Music`.
 * @return Duração da música em segundos.
 */
int get_music_duration_seconds(Music* musica);

/**
 * @brief Getter para o género da música.
 * 
 * @param music Pointer para a estrutura `Music`.
 * @return Cópia do género da música.
 */
char* get_music_genre(Music* music);

/**
 * @brief Getter para o ano da música.
 * 
 * @param music Pointer para a estrutura `Music`.
 * @return Cópia de uma string com o ano da música.
 */
char* get_music_year(Music* music);




//NAO COMENTADO 
int get_music_album(Music* music);

int get_numArtistsId (Music* music);

int get_artistID_at_index(Music* song, int index);

int* getArtistIDfromMuiscID(Music* music);


#endif
