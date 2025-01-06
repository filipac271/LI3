#ifndef HISTORYCONTROLLER_H
#define HISTORYCONTROLLER_H
#include <stdio.h>
#include "controler/usersController.h"
#include "controler/artistsController.h"
#include "controler/musicsController.h"
#include "controler/historyController.h"
#include "Entities/history.h"


/**
 * @typedef 
 * @brief Estrutura do Controller dos historys
 */
typedef struct historyData HistoryData;



/**
 * @brief Processa o histórico de um ficheiro e preenche todas as estruturas de dados relacionadas.
 * 
 * Esta função começa por criar a estrutura HistoryData. Seguidamente inicia o output de erros pois os dados antes de serem inseridos
 * serão validados e aqueles que contêm erros serão escritos no ficheiro de erros iniciado.
 * ACABAR DEPOIS PORQUE AINDA FALTA A PARTE DA CAROL
 * 
 * @param diretoria Caminho para o ficheiro de entrada.
 * @param musicData Pointer para o controlador de dados de músicas.
 * @param artistData Pointer para o controlador de dados de artistas.
 * @param usersData Pointer para o controlador de dados de utilizadores.
 * @return Pointer para a estrutura HistoryData criada e preenchida.
 */
HistoryData* historyFeed(char* diretoria, MusicData* musicData, ArtistsData* artistData, UsersData* usersData);

/**
 * @brief Procura e devolve a posição do ano no GArray anos do history do user.
 * 
 *  Esta função começa por procurar o history do user, se não existir devolve -1, se existir chama a função procuraAno
 *  qu devolve a posição do ano neste se a encontrar, em caso negativo devolve -1. 
 * 
 * @param  historyController Pointer para a estrutura HistoryData que contem a hash table history.
 * @param  user_id Id do user.
 * @param  ano ano cuja posicao vai ser devolvida.
 ** @return int da posicao do ano no array anos do history do user.
 */
int getPosicaoAno(HistoryData* historyController,int user_id, int ano);


/**
 * @brief A função obtém os N artistas mais ouvidos pelo user,o número de músicas ouvidas e o tempo total de audição, de cada artista. 
 * 
 * Esta função começa por procurar o history do user, e depois chama a função NartistasMaisOuvidos e devolve o seu resultado.
 * A função devolve, se N>0, um array de strings com os N artistas mais ouvidos, o número de músicas ouvidas 
 * e o tempo total de audição de cada um pelo user, ou se N==0 um array de strings com apenas uma única posição com o 
 * artista mais ouvido o número de músicas distintas ouvidas no total pelo user e o tempo total de audição deste.
 * 
 * @param  historyController Pointer para a estrutura HistoryData que contem a hash table history.
 * @param  musicController Pointer para a estrutura MusicData 
 * @param  user_id Id do user.
 * @param  posicaoAno posicao do ano desta estatística no GArray anos do history do user.
 * @param  N número de linhas da matriz (artistas).
 * @return Array de strings, cada linha sendo um artista, o número de músicas ouvidas pelo user deste e o tempo total que o user as ouviu.
 */
char** getNartistasMaisOuvidos(HistoryData* historyController, MusicData*musicController, int user_id,int  posicaoAno,int N);

/**
 * @brief Devolve a data em que o user ouviu mais músicas, incluindo músicas repetidas.
 * 
 *  Esta função começa por procurar o history do user, e depois chama a função DataMaisMusicas e devolve o que esta retorna,
 * quee é a data em que o user ouviu mais músicas, incluindo músicas repetidas.
 * 
 * @param  historyController Pointer para a estrutura HistoryData que contem a hash table history.
 * @param  user_id Id do user.
 * @param  ano ano desta estatística.
 ** @return String da data em que user ouviu mais músicas.
 */
char* getDia(HistoryData*  historyController,int user_id,int ano);

/**
 * @brief Devolve o id do album favorito e o género de música mais ouvido de um user num certo ano.
 * 
 *  Esta função começa por procurar o history do user, necessário para depois chamar a função AlbumGenero que calcula e devolve 
 * a string com o album e o género favorito.No final devolve o resultado que a função chamada devolve.
 * 
 * @param  historyController Pointer para a estrutura HistoryData que contem a hash table history.
 * @param  musicController
 * @param  albumController 
 * @param  userId Id do user
 * @param  posicaoAno Posicao do ano no GArray anos da hash table history.
 ** @return String do albumId e genero.
 */
char * getAlbumGenero(HistoryData* historyController,MusicData* musicController, AlbumsData* albumController, int userId,int posicaoAno);

/**
 * @brief Devolve a hora em que um user ouviu mais músicas durante um certo ano.
 * 
 *  Esta função começa por procurar o history do user, necessário para chamar a função HoraMaisAudicoes 
 * que calcula a hora em que um user ouviu mais músicas durante um certo ano. Depois de chamar a função devolve o seu resultado.
 * 
 * @param  historyController Pointer para a estrutura HistoryData que contem a hash table history.
 * @param  user_id Id do user.
 * @param  ano ano desta estatística.
 ** @return String da hora em que o user ouviu mais músicas.
 */
char* getHora(HistoryData* historyController,int user_id,int ano);

/**
 * @brief Liberta a memória associada à estrutura HistoryData.
 * 
 * @param data Pointer para a estrutura HistoryData que será destruida.
 */
void destroyHistoryData(HistoryData* data);

/**
 * @brief Printa todos os dados armazendos em HistoryData.
 * 
 * @param history Pointer para a estrutura HistoryData a ser impressa.
 */
void print_all_history(HistoryData* history);

/**
 * @brief Determina o ID associado ao maior número de ocorrências em uma Hash Table de domingos quando a data não é um parâmetro.
 * 
 * A função começa por criar uma Hash Table auxiliar que será usuada para armazenar a soma do ocorrências de cada artista, sendo o id do respetivo artista
 * a key da Hash Table. SDe seguida inicia max_ocorrencias e mais_freq_artist a -1 pois no fim da função teremos o id do artista mais frequente e o 
 * numero de ocorrencias do respetivo artista.
 * Seguidamente começamos a iterar a Hash Table externa e para cada data iteramos o GArray que esta contém. Ao iterar o GArray interno verificamos 
 * se o id do artista atual já se encontra na Hash Table auxiliar. Se já estiver, adicionamos à Hash Table auxiliar mais uma unidade pois aquele id ocorreu mais uma vez.
 * Se o id ainda não se encontrar na Hash Table auxiliar então adicionamos e inciamos as ocorrencias do mesmo a 1.
 * Á medida que vamos fazendo isto, vamos verificando e atualizando tanto o valor de max_ocorrencias como o mais_freq_artist.
 * No final, libertamos a hashtbale auxiliar para evitar memory leaks e retornamos o id do artista mais frequente.
 * 
 * @param HistoryController Pointer para a estrutura HistoryData.
 * @param maior_n_ocorrencias Pointer para armazenar o maior número de ocorrências encontrado.
 * @return ID associado ao maior número de ocorrências.
 */
int id_maiores_ocorrencias(HistoryData* HistoryController, int* maior_n_ocorrencias);

/**
 * @brief Identifica o artista mais frequente entre duas datas específicas.
 * 
 * A função começa por criar uma Hash Table auxiliar que será usuada para armazenar a soma do ocorrências de cada artista, sendo o id do respetivo artista
 * a key da Hash Table. de seguida inicia max_ocorrencias e mais_freq_artist a -1 pois no fim da função teremos o id do artista mais frequente e o 
 * número de ocorrências do respetivo artista.
 * Seguidamente começamos a iterar a Hash Table externa verificando se a key da mesma, isto é a data se encontra no intervalo de datas. Se tal acontecer 
 * para cada data iteramos o GArray que esta contém. Ao iterar o Garray interno verificamos se o id do artista atual já se encontra na Hash Table auxiliar. 
 * Se já estiver, adicionamos à Hash Table auxiliar mais uma unidade pois aquele id ocorreu mais uma vez. 
 * Se o id ainda não se encontrar na Hash Table auxiliar então adicionamos e inciamos as ocorrencias do mesmo a 1.
 * Á medida que vamos fazendo isto, vamos verificando e atualizando tanto o valor de max_ocorrencias como o mais_freq_artist.
 * No final, libertamos a hashtbale auxiliar para evitar memory leaks e retornamos o id do artista mais frequente.
 * 
 * @param  HistoryController Pointer para a estrutura HistoryData.
 * @param data_inicio String que contem a data inicial no formato yyyy/mm/dd.
 * @param data_fim String que contem a data final no formato yyyy/mm/dd.
 * @param ocorrencia_final Pointer para armazenar o número total de ocorrências do artista mais frequente.
 * @return ID do artista mais frequente entre as datas fornecidas.
 */
int artista_mais_frequente_com_data (HistoryData* HistoryController, char* data_inicio, char* data_fim, int *ocorrencia_final);


#endif