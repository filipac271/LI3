#include "../../include/controler/usersController.h"
#include "../../include/controler/musicsController.h"
#include "controler/usersController.h"
#include "utilidades.h"
#include "Entitys/musics.h"
#include "Entitys/users.h"
#include "querie/querie3.h"
#include "IOManager.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <glib.h>
#include <unistd.h> 

struct querie3
{
   char* genero;
   int numMusicas;
};

void querie3(int num, int min, int max, UsersData* userController)
{

   Genero array[15];
    int validCount = 0;

    for (int i = 0; i < 15; i++) {
        array[i].numMusicas = -1;
        array[i].genero = NULL;
    }


 for (int i = min; i < max + 1; i++) {
        for (int j = 0; j < getUBANGeneros(userController, i); j++) {
            int inserido = 0;
            char* genero = NULL;
            int numSongs = -1;
            genero = getUBAGenero(userController, i, j);
            numSongs = getUBANSongs(userController, i, j);

            for (int a = 0; a < validCount; a++) {
                if (array[a].genero != NULL && strcmp(array[a].genero, genero) == 0) {
                    array[a].numMusicas += numSongs;
                    inserido = 1;
                    break;
                }
            }

            if (!inserido) {
                array[validCount].genero = strdup(genero);
                if (array[validCount].genero == NULL) {
                    printf("Erro ao alocar memória para o gênero.\n");
                    return;
                }
                array[validCount].numMusicas = numSongs;
                validCount++;
            }

            free(genero);
        }
    }

    // Ordenação
    if (validCount > 0) {
        for (int i = 1; i < validCount; i++) {
            struct querie3 key = array[i];
            int nm = array[i].numMusicas;
            char* gnr = array[i].genero;
            int j = i - 1;

            while (j >= 0 && (array[j].numMusicas < nm || (array[j].numMusicas == nm && strcmp(gnr, array[j].genero) < 0))) {
                array[j + 1] = array[j];
                j--;
            }
            array[j + 1] = key;
        }
    }

    // Gravar o arquivo
    char *filename = malloc(sizeof(char) * 256);

    if (filename == NULL) {
        printf("Erro ao alocar memória para o nome do arquivo.\n");
        return;
    }
  sprintf(filename, "resultados/command%d_output.txt",num+1);
   Output* output= iniciaOutput(filename);


    if (validCount == 0) {
         outputNULL(output);
    } else {
        for (int i = 0; i < validCount; i++) {
                output3(output, array[i].genero,array[i].numMusicas);
            free(array[i].genero);
        }
    }



freeOutput (output);
    free(filename);
}

