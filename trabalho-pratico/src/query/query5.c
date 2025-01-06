#include "recomendador.h"
#include "Output.h"
#include "controler/usersController.h"
#include "recomendador.h"
#include "personalRecomendador.h"
#include <unistd.h>
#include <stdlib.h>


void freeQ5Matrizes(int** elementosMatriz,char** idsUsers,char** nomesGeneros, UsersData* userControllador){
    int numLinhas = getNumLinhas(userControllador);
    int numColunas = getNumColunas(userControllador);
    for (int i = 0; i < numLinhas; i++)
    {
        free(idsUsers[i]);
    }
    
    for (int i = 0; i < numColunas; i++)
    {
        free(nomesGeneros[i]);
    }

    for (int i = 0; i < numLinhas; i++)
    {
        free(elementosMatriz[i]);
    }
    
    free(idsUsers);
    free(elementosMatriz);
    free(nomesGeneros);
}


void query5(char* line, int i, UsersData* userControllador, int** elementosMatriz, char** idsUsers, char** nomesGeneros) {



    char *filename = malloc(sizeof(char) * 256);
    sprintf(filename, "resultados/command%d_output.txt", i + 1);
    char c = line[1];

    Output* output = iniciaOutput(filename);

    char userID[9]; 
    int numrecomendacoes;

    if (c == 'S') {
        if (sscanf(line, "5S %8s %d", userID, &numrecomendacoes) != 2) {
            fprintf(stderr, "Erro ao fazer parsing da linha: %s\n", line);
            freeOutput(output);
            free(filename);
            return;
        }
    } else {
        if (sscanf(line, "5 %8s %d", userID, &numrecomendacoes) != 2) {
            fprintf(stderr, "Erro ao fazer parsing da linha: %s\n", line);
            freeOutput(output);
            free(filename);
            return;
        }
    }

    if(numrecomendacoes == 0){
        outputNULL(output);
        freeOutput(output);
        free(filename);
        return;
    }

    int numLinhas = getNumLinhas(userControllador);
    int numColunas = getNumColunas(userControllador);
    int posicao = getPosicaoUser(userControllador, userID);



    if (posicao == -1) {
        outputNULL(output);
        freeOutput(output);
        free(filename);
        return;
    }

    char** usersSugeridos;    
 
    usersSugeridos = recomendaUtilizadores(userID, elementosMatriz, idsUsers, nomesGeneros, numLinhas, numColunas, numrecomendacoes);


    output5(output, usersSugeridos, numrecomendacoes);


    free(usersSugeridos);
    free(filename);
    freeOutput(output);



}

