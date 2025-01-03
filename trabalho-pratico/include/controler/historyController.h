#ifndef HISTORYCONTROLLER_H
#define HISTORYCONTROLLER_H
#include <stdio.h>
#include "controler/usersController.h"
#include "controler/artistsController.h"
#include "controler/musicsController.h"
#include "controler/historyController.h"
#include "Entitys/history.h"


/**
 * @typedef 
 * @brief Estrutura do Controller dos historys
 */
typedef struct historyData HistoryData;



/**
 * @brief Procura um domingo específico na Hash Table externa.
 * 
 * @param domingo Pointer para a Hash Table de domingos.
 * @param data String representando a data no formato yyyy/mm/dd.
 * @return Pointer para a estrutura Domingo correspondente à data, ou NULL se não for encontrada.
 */
Domingo* lookup_domingo(GHashTable* domingo, char* data);

/**
 * @brief Cria um novo domingo ou atualiza um existente com base nos tokens fornecidos.
 * 
 * Esta função começa por obter a data a partir do token que contem o timestamp, de seguida calcula o domingo anterior a essa data,
 * tirando se for um domingo, nesse caso a data mantêm-se. De seguida, verificamos se já existe uma hashtable interna associada a essa data.
 * Se já existir chamamos a função new_or_add. Caso contrario, criamos uma nova hashtable, um novo Domingo.
 * 
 * @param controller Pointer para o Controller de dados do histórico.
 * @param tokens Array de strings que contêm os tokens que serão processados.
 * @param musicController Pointer para o Controller dos dados referentes às musicas.
 */
void newDomingo_orNot(HistoryData* controller, char** tokens, MusicData* musicController);

/**
 * @brief Converte os dados de uma Hash Table para um GArray.
 * 
 * @param data Pointer para a estrutura HistoryData que contem a informação que será convertida.
 * 
 * Esta função processa a Hash Table armazenada em `HistoryData` e transfere seus elementos 
 * para uma GArray ao chamar passa_domingo_para_garray que transforma a hashtable interna em GArray. 
 * Passamos então a ter uma Hash Table externa constituida internamente por GArrays
 */
void passa_hastable_para_garray(HistoryData* data);

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
 * a key da Hash Table. de seguida inicia max_ocorrencias e mais_freq_artist a -1 pois no fim da função teremos o id do artista mais frequente e o 
 * numero de ocorrencias do respetivo artista.
 * Seguidamente começamos a iteraar a Hash Table externa e para cada data iteramos o GArray que esta contém. AO iterar o Garray interno verificamos 
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
 * numero de ocorrencias do respetivo artista.
 * Seguidamente começamos a iterar a Hash Table externa verificando se a key da mesma, isto é a data se encontra no intervalo de datas. Se tal acontecer 
 * para cada data iteramos o GArray que esta contém. AO iterar o Garray interno verificamos se o id do artista atual já se encontra na Hash Table auxiliar. 
 * Se já estiver, adicionamos à Hash Table auxiliar mais uma unidade pois aquele id 
 * ocorreu mais uma vez. Se o id ainda não se encontrar na Hash Table auxiliar então adicionamos e inciamos as ocorrencias do mesmo a 1.
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