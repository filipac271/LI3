#ifndef QUERIEMANAGER_H
#define QUERIEMANAGER_H



#include <stdio.h>
#include <stdlib.h>
#include <glib.h>
#include "controler/usersController.h"
#include "controler/mainController.h"
#include "utilidades.h" 

/**
 * @brief Função para validar o input da query 1.
 * 
 * @param argumentos Argumentos a serem validados.
 * @param possivelS Caracter que pode ser 'S' ou '\0'.
 * @return Retorna 1 se o input for válido, 0 caso contrário.
 */
int validaQ1Input(char *argumentos, char possivelS);

/**
 * @brief Função para validar o input da query 2.
 * 
 * @param argumentos Argumentos a serem validados.
 * @param possivelS Caracter que pode ser 'S' ou '\0'.
 * @return Retorna 1 se o input for válido, 0 caso contrário.
 */
int validaQ2Input(char *argumentos, char possivelS);

/**
 * @brief Função para validar o input da query 3.
 * 
 * @param argumentos Argumentos a serem validados.
 * @param possivelS Caracter que pode ser 'S' ou '\0'.
 * @return Retorna 1 se o input for válido, 0 caso contrário.
 */
int validaQ3Input(char *argumentos, char possivelS);

/**
 * @brief Função para validar o input da query 4.
 * 
 * @param argumentos Argumentos a serem validados.
 * @param possivelS Caracter que pode ser 'S' ou '\0'.
 * @return Retorna 1 se o input for válido, 0 caso contrário.
 */
int validaQ4Input(char *argumentos, char possivelS);

/**
 * @brief Função para validar o input da query 5.
 * 
 * @param argumentos Argumentos a serem validados.
 * @param possivelS Caracter que pode ser 'S' ou '\0'.
 * @return Retorna 1 se o input for válido, 0 caso contrário.
 */
int validaQ5Input(char *argumentos, char possivelS);

/**
 * @brief Função para validar o input da query 6.
 * 
 * @param argumentos Argumentos a serem validados.
 * @param possivelS Caracter que pode ser 'S' ou '\0'.
 * @return Retorna 1 se o input for válido, 0 caso contrário.
 */
int validaQ6Input(char *argumentos, char possivelS);

/**
 * @brief Função para processar as queries de acordo com o arquivo de entrada.
 * 
 * @param data Controlador principal com os dados.
 * @param querieFile Arquivo contendo as queries a serem processadas.
 */
void queries(MainController *data, char *querieFile);


#endif