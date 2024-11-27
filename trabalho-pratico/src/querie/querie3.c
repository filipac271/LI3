#include "controler/usersController.h"
#include "utilidades.h"
#include "Entitys/users.h"
#include "Output.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <glib.h>
#include <unistd.h>

#include "querie/querie3.h"

struct querie3 {
    char* genero;     // Nome do género musical
    int numMusicas;   // Número de músicas para o género
};

// Função `querie3`: realiza a consulta de géneros de música entre uma faixa de idades 
// e grava os resultados num ficheiro de saída.
void querie3(int num, char* line, UsersData* userController) {
    int min, max;
    sscanf(line + 2, "%d %d", &min, &max);  // Lê o intervalo de idades (min e max) a partir da linha de entrada

    Genero array[15];   // Array para armazenar géneros e contagem de músicas
    int validCount = 0; // Contador de géneros válidos (diferentes)

    // Inicializa o array com valores nulos
    for (int i = 0; i < 15; i++) {
        array[i].numMusicas = 0;
        array[i].genero = NULL;
    }

    // Itera sobre o intervalo de idades fornecido
    for (int i = min; i <= max; i++) {
        // Para cada idade, itera sobre todos os géneros de música associados a essa idade
        for (int j = 0; j < getUBANGeneros(userController, i); j++) {
            int inserido = 0;
            char* genero = NULL;
            int numSongs = 0;
            genero = getUBAGenero(userController, i, j);  // Obtém o nome do género
            numSongs = getUBANSongs(userController, i, j); // Obtém a contagem de músicas para o género

            // Verifica se o género já está no array
            for (int a = 0; a < validCount; a++) {
                if (array[a].genero != NULL && strcmp(array[a].genero, genero) == 0) {
                    array[a].numMusicas += numSongs;  // Atualiza a contagem de músicas
                    inserido = 1;
                    break;
                }
            }

            // Se o género ainda não foi adicionado ao array, insere-o como um novo género
            if (!inserido) {
                array[validCount].genero = strdup(genero);
                if (array[validCount].genero == NULL) {
                    printf("Erro ao alocar memória para o género.\n");
                    return;
                }
                array[validCount].numMusicas = numSongs;
                validCount++;
            }

            free(genero);  // Liberta a memória alocada para o género atual
        }
    }

    // Ordenação do array 
    if (validCount > 0) {
        for (int i = 1; i < validCount; i++) {
            struct querie3 key = array[i];
            int nm = array[i].numMusicas;
            char* gnr = array[i].genero;
            int j = i - 1;

            while (j >= 0 && (array[j].numMusicas < nm || 
                (array[j].numMusicas == nm && strcmp(gnr, array[j].genero) < 0))) {
                array[j + 1] = array[j];
                j--;
            }
            array[j + 1] = key;
        }
    }

    // Criação do ficheiro de saída para gravar os resultados da consulta
    char* filename = malloc(sizeof(char) * 256);
    if (filename == NULL) {
        printf("Erro ao alocar memória para o nome do ficheiro.\n");
        return;
    }
    sprintf(filename, "resultados/command%d_output.txt", num + 1);
    Output* output = iniciaOutput(filename);

    // Grava o resultado no ficheiro
    if (validCount == 0) {
        outputNULL(output);
    } else {
        for (int i = 0; i < validCount; i++) {
            output3(output, array[i].genero, array[i].numMusicas, line[1]);  // Grava cada género e contagem de músicas no ficheiro
            free(array[i].genero);  // Liberta a memória alocada para o nome do género
        }
    }

    // Liberta os recursos
    freeOutput(output);
    free(filename);
}