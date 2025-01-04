#ifndef HISTORY_H
#define HISTORY_H
#include <stdio.h>
#include "controler/usersController.h"
#include "controler/artistsController.h"
#include "controler/musicsController.h"


/**
 * @brief Estrutura que contem os dados que consideramos significativos sobre o histórico de um artista.
 */
typedef struct artistahistory UmArtista;

/**
 * @brief Estrutura que divide os dados por semanas
 */
typedef struct domingo Domingo;


typedef struct genero Generos;
typedef struct album Albuns;

typedef struct artista Artistas;
typedef struct dia Dia;
typedef struct hora Hora;
typedef struct musica Musica;
typedef struct ano Ano;
typedef struct userHistory History;

char* HoraMaisAudicoes(History* userHistory,int anoP);

char**NartistasMaisOuvidos(History *userHistory, MusicData* musicController, int pAno, int N);

char * AlbumGenero(MusicData* musicController,History* userHistory,AlbumsData*albumController, int posicaoAno);

char* DataMaisMusicas(History* userHistory,int anoP);

int procuraAno(History* history, int ano);

void adicionaUserHistory(History* userHistory,int musicId,int ano,int mes,int dia,int hora,int duration);

History* inicializaUserHistory(int userId,int musicId,int ano,int mes, int dia,int hora,int duration);

void freeUserHistory(History* history);

/**
 * @brief Liberta a memória associada a um artista.
 * 
 * @param artista Ponteiro para a estrutura UmArtista a ser libertada.
 */
void freeUmArtista(UmArtista* artista);

/**
 * @brief Liberta o GArray juntamente com os dados que ele contém.
 * 
 * @param array Ponteiro para o GArray a ser libertado.
 */
void free_garray_with_data(GArray* array);

/**
 * @brief Liberta a memória associada a um Domingo assim como os dados que ela contém.
 * 
 * @param domingo Ponteiro para a estrutura Domingo a ser libertada.
 */

void freeDomingo(Domingo* domingo);

/**
 * @brief Cria um novo domingo com a data especificada.
 * 
 * Esta função cria um novo Domingo, alocando já espaço para a Hash Table e o GArray
 * que este tem.
 * 
 * @param data String data no formato yyyy/mm/dd.
 * @return Ponteiro para a nova estrutura Domingo criada.
 */
Domingo* newDomingo(char* data);

/**
 * @brief Cria um novo artista com o ID e os segundos especificados.
 * 
 * @param artist_id ID do artista.
 * @param segundos Número de segundos que determinada musica do respetivo artista foi ouvida.
 * @return Ponteiro para a nova estrutura UmArtista criada.
 */
UmArtista* new_umArtista(int artist_id, int segundos);

/**
 * @brief Insere um artista na Hash Table da semana.
 * 
 * @param artisthistory Ponteiro para a Hash Table de histórico de artistas.
 * @param novo_artista Ponteiro para a estrutura UmArtista a ser adicionada.
 * @param artist_id ID do artista a ser inserido.
 */
void inserir_umartista_na_semana(GHashTable* artisthistory, UmArtista* novo_artista, int artist_id);

/**
 * @brief Adiciona novos dados ou atualiza os existentes em um Domingo.
 * 
 * Esta função começa por obter o ID dos artistas que fizem parte de determinada musica. Obtendo também o numero de artistas e o array com esses artistas.
 * Calcula também os segundos de musica do artista ouvida.
 * 
 * @param domingo Ponteiro para a estrutura Domingo a ser atualizada.
 * @param tokens Array de strings contendo os dados a processar.
 * @param musicController Ponteiro para o controlador de dados de músicas.
 */
void new_or_add(Domingo* domingo, char** tokens, MusicData* musicController);

/**
 * @brief Converte os dados de um domingo em uma GArray.
 * 
 * @param domingo Ponteiro para a estrutura Domingo a ser convertida.
 */
void passa_Domingo_para_garray(Domingo* domingo);

/**
 * @brief Compara dois valores com base no número de segundos.
 * 
 * @param a Ponteiro para o primeiro valor a ser comparado.
 * @param b Ponteiro para o segundo valor a ser comparado.
 * @return Resultado da comparação: < 0 se a < b, 0 se a == b, > 0 se a > b.
 */
gint compare_seconds(gconstpointer a, gconstpointer b);


/**
 * @brief Procura um artista específico na tabela hash de histórico de artistas.
 * 
 * @param Artista Ponteiro para a tabela hash de artistas.
 * @param artist_id ID do artista a ser procurado.
 * @return Ponteiro para a estrutura UmArtista correspondente ao ID, ou NULL se não encontrado.
 */
UmArtista* lookup_artista_historico(GHashTable* Artista, int artist_id);


/**
 * @brief Obtém a GArray de um domingo.
 * 
 * @param domingo Ponteiro para a estrutura Domingo.
 * @return Ponteiro para a GArray associada ao domingo.
 */
GArray* get_garray_from_domingo(Domingo* domingo);

/**
 * @brief Obtém o comprimento da GArray associada a um domingo.
 * 
 * @param domingo Ponteiro para a estrutura Domingo.
 * @return Número de elementos na GArray.
 */
int get_garray_len(Domingo* domingo);

/**
 * @brief Obtém o ID do artista a partir de uma estrutura UmArtista.
 * 
 * @param artista Ponteiro para a estrutura UmArtista.
 * @return ID do artista.
 */
int get_artist_id_from_garray(UmArtista* artista);

/**
 * @brief Obtém o número de segundos associados a um artista a partir de uma estrutura UmArtista.
 * 
 * @param artista Ponteiro para a estrutura UmArtista.
 * @return Número de segundos associados ao artista.
 */
int get_seconds_from_garray(UmArtista* artista);

/**
 * @brief Imprime as informações de um histórico de artista.
 * 
 * @param artista Ponteiro para a estrutura UmArtista a ser impressa.
 */
void print_artisthistory(UmArtista* artista);

/**
 * @brief Imprime os elementos de uma GArray.
 * 
 * @param array Ponteiro para a GArray a ser impressa.
 */
void print_garray(GArray* array);

/**
 * @brief Imprime os dados de um domingo.
 * 
 * @param domingo Ponteiro para a estrutura Domingo a ser impressa.
 */
void printf_domingo(Domingo* domingo);

/**
 * @brief Imprime uma entrada de histórico de artistas.
 * 
 * @param key Chave da entrada.
 * @param value Valor da entrada.
 * @param user_data Dados adicionais fornecidos pelo utilizador.
 */
void print_artisthistory_entry(gpointer key, gpointer value, gpointer user_data);

/**
 * @brief Imprime a semana completa de dados.
 * 
 * @param key Chave da entrada.
 * @param value Valor da entrada.
 * @param user_data Dados adicionais fornecidos pelo utilizador.
 */
void print_semana_completa(gpointer key, gpointer value, gpointer user_data);




GArray* get_artistahistory_garray_copy(Domingo* dom);

void free_garray_with_data2(GArray* array);

#endif