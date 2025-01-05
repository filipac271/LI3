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
 * @brief Estrutura que divide os dados por semanas.
 */
typedef struct domingo Domingo;

/**
 * @brief Estrutura que armazena os generos e o tempo de audição correspondente.
 */
typedef struct genero Generos;

/**
 * @brief Estrutura que armazena os id's dos albuns, os nomes e os respetivos tempo de audição.
 */
typedef struct album Albuns;

/**
 * @brief Estrutura que armazena os id's dos artistas, o número de músicas ouvidas e o tempo de audição correspondente.
 */
typedef struct artista Artistas;

/**
 * @brief Estrutura que armazena o dia,o mes e o número de músicas ouvidas correspondente. 
 */
typedef struct dia Dia;

/**
 * @brief Estrutura que armazena a hora e o tempo de audição do user durante esta.
 */
typedef struct hora Hora;

/**
 * @brief Estrutura que armazena os id's das músicas e o tempo de audição do user.
 */
typedef struct musica Musica;

/**
 * @brief Estrutura que armazena os anos do histórico do user.
 */
typedef struct ano Ano;

/**
 * @brief Estrutura que armazena o histórico de um user.
 */
typedef struct userHistory History;

/**
 * @brief Devolve a hora em que o user ouviu mais músicas, determinada através do tempo de audicão total.
 * 
 *  Esta função começa por obter a estrutura ano do user, contida no userHistory. 
 *  De seguida percorre o GArray horas contido nela calculando a hora com um maior tempo de audição total.
 * 
 * @param  userHistory Pointer para a estrutura history de um certo user.
 * @param  anoP Posicao em que o ano requerido da estatística se encontra.
 ** @return Uma string com a hora em que user ouviu mais músicas, calculada através do tempo de audição.
 */
char* HoraMaisAudicoes(History* userHistory,int anoP);

/**
 * @brief Obtém uma lista dos N artistas mais ouvidos de um utilizador num determinado ano.
 *
 *   Esta função começa por aceder ao ano pedido para as estatísticas. Vai percorrendo o GArray das musicas contido na estrutura ano, do userHistory, 
 * e armazenando num GArray Artistas o id de cada artista, o número de músicas distintas destes, ouvidas pelo user  e o tempo total de Audição do user de cada artista.
 * Além disso, vai somando o tempo total de audição do user naquele ano. 
 *  Se N for igual a zero a função devolve um array de strings com apenas uma posição, que contém o id do artista mais ouvido, 
 * o número total de músicas distintas que o user ouviu e o tempo total de audição. 
 *  Se N for maior que zero devolve um array de N+1 strings com o id dos N artistas mais ouvidos, quantas músicas distintas o user ouviu desse artista e o tempo total que o user as ouviu,
 *  sendo a última string nula para sinalizar o fim do array.
 * Se o user tiver ouvido menos de N strings, a função devolve um array com mais uma string do que o número de artistas ouvidos, a string nula.  ???????
 * 
 * @param userHistory Ponteiro para o histórico do user.
 * @param musicController Ponteiro 
 * @param pAno Índice do ano 
 * @param N Número de artistas mais ouvidos a retornar. Se for 0, retorna o artista mais ouvido.
 * 
 * @return Um array de strings, onde cada string contém as informações de um artista no formato:
 *         "id_artista nMusicas tempoAudicao". O array é terminado com `NULL` caso N diferente de 0.
 *         - Se N == 0, retorna um array com uma única string contendo o artista mais ouvido, o número total de músicas ouvidas pelo user e o tempo total de audição.
 *         - Se N>0, retorna um array de strings com até os N artistas mais ouvidos, o número de músicas ouvidas pelo user de cada um e o tempo de audição.
 */
char** NartistasMaisOuvidos(History *userHistory, MusicData* musicController, int pAno, int N);

/**
 * @brief Devolve o album e o género favorito do user num certo ano, determinados através do tempo de audicão total.
 * 
 *  Esta função começa por obter a estrutura ano do user, contida no userHistory, na posicao anoP do GArray anos. 
 *  De seguida percorre o GArray Musicas contido nela, preenchendo o GArray generos, com o nome do genero e o tempo total que o user esteve a ouvir músicas desse género,
 *  e o GArray albuns, com o id do album, o seu nome e o tempo total que o user teve a ouvi-lo. Depois calcula qual o album e o género com maior tempo de audição, com desempate por ordem alfabética.
 * 
 * @param musicController Pointer para as estruturas das músicas.
 * @param  userHistory Pointer para a estrutura history de um certo user.
 * @param  albumController Pointer para a estrutura dos albuns.
 * @param  posicaoAno Posição em que o ano requerido da estatística se encontra.
 ** @return Uma string com o album e o genero favorito do user, calculada através do tempo de audição.
 */
char * AlbumGenero(MusicData* musicController,History* userHistory,AlbumsData* albumController, int posicaoAno);

/**
 * @brief Devolve a data em que o user ouviu mais músicas num certo ano, determinados através do número de músicas (incluindo repetidas).
 * 
 *  Esta função começa por obter a estrutura ano do user, contida no userHistory, na posicao anoP do GArray anos. 
 *  De seguida percorre o GArray dia contido nela, calculando o dia do ano com o maior número de músicas, com desempate por data mais recente.
 * 
 * @param  userHistory Pointer para a estrutura history do user.
 * @param  anoP Posição em que o ano requerido da estatística se encontra.
 ** @return Uma string com a data em que o user ouviu mais músicas, calculada através do número de músicas.
 */
char* DataMaisMusicas(History* userHistory,int anoP);

/**
 * @brief Devolve a posição do ano no GArray anos do history do user.
 * 
 * @param  userHistory Pointer para a estrutura history do user.
 * @param  ano Ano a ser procurado.
 ** @return A posição do ano no GArray anos do history do user .
 */
int procuraAno(History* history, int ano);

/**
 * @brief Adiciona as informações do histórico, ao ano correspondente , do history do user já existente.
 * 
 * @param userHistory Pointer para a estrutura history do user.
 * @param musicId Id da música a que o histórico se refere.
 * @param ano Ano do histórico.
 * @param mes Mes do histórico.
 * @param dia Dia do histórico.
 * @param hora Hora do histórico.
 * @param duration Duração da audição da música.
 ** @return Uma string com a data em que o user ouviu mais músicas, calculada através do número de músicas.
 */
void adicionaUserHistory(History* userHistory,int musicId,int ano,int mes,int dia,int hora,int duration);

/**
 * @brief Aloca memória para o history do user e adiciona as informações do histórico .
 * 
 * @param userId Id do user.
 * @param musicId Id da música a que o histórico se refere.
 * @param ano Ano do histórico.
 * @param mes Mes do histórico.
 * @param dia Dia do histórico.
 * @param hora Hora do histórico.
 * @param duration Duração da audição da música.
 */
History* inicializaUserHistory(int userId,int musicId,int ano,int mes, int dia,int hora,int duration);

/**
 * @brief Liberta a memória associada a um history de um user.
 * 
 * @param history Ponteiro para a estrutura History a ser libertada.
 */
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