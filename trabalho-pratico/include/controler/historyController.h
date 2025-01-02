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
 * @brief 
 */
typedef struct historyData HistoryData;



/**
 * @brief Procura um domingo específico na tabela hash externa.
 * 
 * @param domingo Ponteiro para a tabela hash de domingos.
 * @param data String representando a data no formato yyyy/mm/dd.
 * @return Ponteiro para a estrutura Domingo correspondente à data, ou NULL se não for encontrada.
 */
Domingo* lookup_domingo(GHashTable* domingo, char* data);

/**
 * @brief Cria um novo domingo ou atualiza um existente com base nos tokens fornecidos.
 * 
 * Esta função começa por obter a data a partir do token que contem o timestamp, de seguida calcula o domingo anterior a essa data,
 * tirando se for um domingo, nesse caso a data mantêm-se. De seguida, verificamos se já existe uma hashtable interna associada a essa data.
 * Se já existir chamamos a função new_or_add. Caso contrario, criamos uma nova hashtable, um novo Domingo.
 * 
 * @param controller Ponteiro para o Controller de dados do histórico.
 * @param tokens Array de strings que contêm os tokens que serão processados.
 * @param musicController Ponteiro para o Controller dos dados referentes às musicas.
 */
void newDomingo_orNot(HistoryData* controller, char** tokens, MusicData* musicController);

/**
 * @brief Processa o histórico de um ficheiro e preenche as estruturas de dados relacionadas.
 * 
 * @param diretoria Caminho para o ficheiro de entrada.
 * @param musicData Ponteiro para o controlador de dados de músicas.
 * @param artistData Ponteiro para o controlador de dados de artistas.
 * @param usersData Ponteiro para o controlador de dados de utilizadores.
 * @return Ponteiro para a estrutura HistoryData criada e populada.
 */
HistoryData* historyFeed(char* diretoria, MusicData* musicData, ArtistsData* artistData, UsersData* usersData);

/**
 * @brief Liberta a memória associada à estrutura HistoryData.
 * 
 * @param data Ponteiro para a estrutura HistoryData que será destruida.
 */
void destroyHistoryData(HistoryData* data);

/**
 * @brief Printa todos os dados armazendos em HistoryData.
 * 
 * @param history Ponteiro para a estrutura HistoryData a ser impressa.
 */
void print_all_history(HistoryData* history);

/**
 * @brief Obtém a Hash table externa a partir de uma estrutura HistoryData.
 * 
 * @param data Ponteiro para a estrutura HistoryData.
 * @return Ponteiro para a GHashTable de domingos.
 */
GHashTable* get_Domingo_from_HD(HistoryData* data);

/**
 * @brief Determina o ID associado ao maior número de ocorrências em uma tabela hash de domingos quando a data não é um parâmetro.
 * 
 * @param domingo Ponteiro para a Hash Table externa de domingos.
 * @param maior_n_ocorrencias Ponteiro para armazenar o maior número de ocorrências encontrado.
 * @return ID associado ao maior número de ocorrências.
 */
int id_maiores_ocorrencias(GHashTable* domingo, int* maior_n_ocorrencias);

/**
 * @brief Identifica o artista mais frequente entre duas datas específicas.
 * 
 * @param semanas Ponteiro para a Hash Table externa.
 * @param data_inicio String que contem a data inicial no formato yyyy/mm/dd.
 * @param data_fim String que contem a data final no formato yyyy/mm/dd.
 * @param ocorrencia_final Ponteiro para armazenar o número total de ocorrências do artista mais frequente.
 * @return ID do artista mais frequente entre as datas fornecidas.
 */
int artista_mais_frequente_com_data(GHashTable* semanas, char* data_inicio, char* data_fim, int* ocorrencia_final);


#endif