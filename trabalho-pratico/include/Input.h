#ifndef IOMANAGER
#define IOMANAGER

#include <stdio.h>
#include <stdlib.h>
#include "querie/querie3.h"

/** VER SE É PRECISO ESCREVER MAIS ALGUMA COISA NAS ESTRUTURAS
 * @typedef Parser
 * @brief Representa um objeto de parsing.
 */
typedef struct parser Parser;

/**
 * @typedef Output
 * @brief Representa um objeto de saída de dados.
 */
typedef struct output Output;

/**
 * @brief Abre um ficheiro na diretoria e subdiretoria especificadas.
 * 
 * Ao receber uma diretoria e a respetiva subdiretoria, esta função abre o ficheiro em modo de leitura.
 * 
 * @param diretoria O caminho da diretoria principal.
 * @param subdiretoria O caminho da subdiretoria.
 * @return Um ponteiro para o ficheiro aberto.
 */
FILE* abrirFILE(char* diretoria, char* subdiretoria);

/**
 * @brief Fecha um ficheiro.
 * 
 * 
 * @param ficheiro Um ponteiro para o ficheiro a fechar.
 */
void fecharFILE(FILE* ficheiro);

/**
 * @brief Abre um ficheiro para registo de erros na diretoria especificada.
 * 
 * @param diretoria O caminho da diretoria principal.
 * @return Um ponteiro para o ficheiro de registo de erros.
 */
FILE* abrirFILE_ERROS(char* diretoria);

/**
 * @brief Faz o parsing com a ajuda de um objeto parsing
 * 
 * Esta função tem como principal objetivo fazer o parse de uma linha. 
 * No objeto parse tenho o ficheiro assim como as linhas e assim nesta função
 * comelamos por verificar se aquela linha existe, caso já tenhamos lido o ficheiro todo
 * ou algum outro motivo para o ficheirp já não ter linhas para ler.
 * Caso haja uma linha para ler, começa por remover o '\n' e coloca um '\0' no seu lugar. 
 * De seguida, faz uma copia da linha para a estrutura lineError e para line que constituem a estrutura ParserE.
 * Por fim, divide a linha em tokens usando a função strsep para separar os tokens consoante os ';' colocando-os
 * na estrutura tokens da estrutura ParserE
 * 
 * @param parserE Um objeto de parsing existente.
 * @return Um ponteiro para o objeto de parsing inicializado.
 */
Parser* parser(Parser* parserE);

/**
 * @brief Obtém uma linha do objeto de parsing.
 * 
 * Esta função funciona como um getter do campo line da estrutura parserE.
 * 
 * @param parserE O objeto de parsing.
 * @return Uma string contendo a linha.
 */
char* pegaLinha(Parser* parserE);

/**
 * @brief Cria um novo objeto de parsing.
 * 
 * Esta função cria uma nova estrutura parserE alocando memoria e colocando os campos line e lineError a NULL.
 * 
 * @param diretoria O caminho da diretoria.
 * @param subdiretoria O caminho da subdiretoria.
 * @return Um ponteiro para o novo objeto de parsing.
 */
Parser* newParser(char* diretoria, char* subdiretoria);

/**
 * @brief Liberta a memória alocada para um objeto de parsing.
 * 
 * Esta função começa por fechar o ficheiro aberto no qual foi feito o parsing. De seguida liberta
 * os tokens e por fim a propria estrutura parserE.
 * 
 * @param parserE O objeto de parsing a libertar.
 */
void freeParser(Parser* parserE);

/**
 * @brief Obtém tokens do objeto de parsing.
 * 
 * Esta função começa por verificar se a estrutura parserE possui tokens. Caso possua, então devolve esses tokens, caso contrario devolve NULL.
 * 
 * @param parserE O objeto de parsing.
 * @return Um array de strings com os tokens.
 */
char** getTokens(Parser* parserE);

/**
 * @brief Obtém a linha onde ocorreu um erro.
 * 
 * @param parserE O objeto de parsing.
 * @return Uma string com a linha do erro.
 */
char* getLineError(Parser* parserE);

/**
 * @brief Obtém a linha atual do objeto de parsing.
 * 
 * @param parserE O objeto de parsing.
 * @return Uma string com a linha atual.
 */
char* getLine(Parser* parserE);


/**
 * @brief Conta o número de linhas num ficheiro.
 * 
 * @param nome_ficheiro O nome do ficheiro.
 * @return O número de linhas no ficheiro.
 */
int contar_linhas(char* nome_ficheiro);

#endif 
