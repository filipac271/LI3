#ifndef UTILIDADES_H
#define UTILIDADES_H

#include <stdlib.h>
#include <stdio.h>
#include <glib.h>

#include "Entitys/users.h"


//FALTA A DESCRIÇÃO GRANDE DO TRANSFORMAiDS E DOS DIVIDIR GROUPS E PENSAR EM COMO ESCREVER O DO COMPARAR
/**
 * @brief Calcula a idade com base na data de nascimento.
 * 
 * Esta função calcula a idade de um user. Ao receber a data de nascimento, verifica o ano e caso o ano, seguidamente o mês 
 * e os dias e caso necessário ajusta a idade.
 * 
 * @param data_nascimento_str String no formato "YYYY-MM-DD" que representa a data de nascimento, neste caso de um user.
 * @return A idade em anos do respetivo user..
 */
int calcular_idade(char* data_nascimento_str);

/**
 * @brief Obtém o tamanho de um GArray.
 * 
 * Esta função é um getter para o tamanho de um GArray. Se o GArray for NULL retorn 0, caso contrário, returna o seu respetivo tamanho.
 * 
 * @param array Pointer para o GArray.
 * @return Número de elementos no GArray.
 */
guint get_garray_length(GArray *array);

/**
 * @brief Converte segundos para o formato "hh:mm:ss".
 * 
 * Esta função começa por alocar memoria para uma string char*, tomando todas as precauções
 * relacionadas a este processo. Seguidamente faz os calculos necessários para obter o numero
 * de horas, minutos e segundos. Por fim, coloca os numeros na string alocada com o formato desejado.
 * 
 * 
 * @param total_seconds Número total de segundos.
 * @return String no formato "hh:mm:ss". Como a função aloca memoria é necessário libertar a mesma depois de ser utilizada.
 */
char* seconds_to_hhmmss(int total_seconds);

/**
 * @brief Remove aspas ou plicas de uma string.
 * 
 * Esta função retira as aspas/plicas de uma string tendo o cuidado de verificar se a string recebida possui 
 * destes parametros. Caso não tenha, devolve uma copia da string original sem nenhuma alteração. Se tiver,
 * prossede à retiragem das mesmas e no fim retorna uma cópia da string original sem aspas.
 * 
 * @param str String original com aspas/plicas.
 * @return Nova string sem aspas/plicas. Deve ser liberada após o uso uma vez que devolve uma cópia da string original, mas sem aspas/plicas.
 */
char* remove_quotes(char* str);

/**
 * @brief Valida se a data fornecida está no formato correto e se segue todas as limitações impostas(NAO SEI SE É PRECISO FALAR DAS LIMITAÇOES).
 * 
 * Esta função verifica se uma data cumpre todos os pré-requesitos para ser considerada uma dataa valida.
 * Assim, começa por verificar o seu tamanho. De seguida verifica se os caracteres de pontuação estão no devido lugar.
 * Então, verifca se todos os paramentros numericos estão dentro dos respetivos limites, i.e se a data não é negativa, 
 * maiores que 12 ou menores que 1 e se os dias são superiores a 31. 
 * Por fim, verifica se a data é mais recente do que 2024/09/09.
 * 
 * @param date String no formato "YYYY-MM-DD".
 * @return 1 se válida, 0 caso contrário.
 */
int validaData(char* date);

/**
 * @brief Valida se o email fornecido está no formato correto.
 * 
 * Esta função verifica se um email cumpre todos os prá-requesitos para ser considerado válido.
 * Começa por verificas se antes do @ esta o username em minusculo. Seguidamente, verifica se 
 * existe pelo menos um caracter no username pois este não pode ser vazio. A seguir verifica 
 * se o que vem a seguir ao '.' (rstring) não contém caracteres invalidos e se contem 2 ou 3 caracteres.
 * 
 * @param email String que contem o email.
 * @return 1 se válido, 0 caso contrário.
 */
int validaEmail(char* email);

/**
 * @brief Valida se a duração fornecida está no formato correto e se segue todas as limitações impostas.
 * 
 * Esta função valida se a duração no formato "hh:mm:ss" segue todos os pré-requesitos para ser considerada uma 
 * duração valida. Começa por verificar o tamanho da mesma e de sequida se os separadores do tempo são ':'. 
 * Depois verfica se os parametos de tempo estão entre os numeros supostos, isto é, se as horas estão enter 0 e 99
 * e se os minutos e segundos estão enter 0 e 59.
 * 
 * @param duracao String representando a duração.
 * @return 1 se válida, 0 caso contrário.
 */
int validaDuracao(char* duracao);


/**
 * @brief Calcula o número de membros em um grupo.
 * 
 * Esta função calcula o numero de elementos de um grupo. Começa por verificar se se trata de um grupo vazio. Se esse for o caso 
 * então retorna 0 como o numero de elementos. Caso contrario, começando com numero de membros a 1, procede à contagem 
 * das virgulas que separam estes elementos. Quando termina a contagem, retora o resultado da mesma.
 * 
 * @param grupo String contendo a definição do grupo.
 * @return Número de membros no grupo.
 */
int calculate_num_members(char* grupo);

/**
 * @brief Libera a memória de um array de inteiros.
 * 
 * Esta função verifica se um array se encontra vazio e caso tal não aconteça liberta o array.
 * 
 * @param array Pointer para o array de inteiros.
 */
void freeArray(int* array);

/**
 * @brief Divide um grupo de artistas/users consoante as aspas/plicas de forma a ficar com os elementos individuais num array.
 * 
 * 
 * 
 * @param group String original com todos os elementos do grupo.
 * @param numMembros Número de elementos do grupo.
 * @return Ponteiro para um array de inteiros que contem os elementos separados. Uma vez que foi alocada memoria, este precisa de ser libertado após o uso.
 */
int* divideGroup(char* group, int numMembros);

/**
 * @brief Divide uma string de array em elementos individuais.
 * 
 * @param arrayString String representando o array.
 * @param numElements Número de elementos no array.
 * @return Ponteiro para um array de inteiros. Deve ser liberado após o uso.
 */
int* divideArray(char* arrayString, int numElements);

/**
 * @brief Transforma um Id em String em um Id em Inteiro.
 * 
 * @param idString Id em string.
 * @return Id em inteiro.
 */
int transformaIds(char* idString);

/** 
 * @brief Compara dois ficheiros linha por linha.
 * 
 * @param file1 Caminho para o primeiro ficheiro.
 * @param file2 Caminho para o segundo ficheiro.
 * @param ocorrenciasCorretas Ponteiro para armazenar o número de ocorrências corretas.
 * @return Número de linhas iguais.
 */
int compararFicheirosPorLinha(char *file1, char *file2, int *ocorrenciasCorretas);


void toLowerCase(char *str);


//FUNCOES NAO COMENTADAS

void pega_data(char* datetime, char* data);

int diasNoMes(int ano, int mes);

int diaDaSemana(int ano, int mes, int dia);

void calcularDomingoAnterior(const char *data, char *resultado);

void destransforma_IDs(int numero, char *resultado);

int pertence_ao_intervalo(char* data_inicial, char* data_final, char* data);

int verificaOrdemDatas(char *data1, char *data2);

#endif // UTILIDADES_H
