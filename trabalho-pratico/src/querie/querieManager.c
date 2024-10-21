#include "querie/querieManager.h"
#include "controler/usersController.h"
#include "controler/mainController.h"
#include "querie/querie1.h"
#include  "querie/querie2.h"
#include  "querie/querie3.h"
#include "utilidades.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <glib.h>

struct ageUsers
{
    char** likedSongs;
    int numberSongs;
};



void queries (MainController* data, FILE* querieFile) {
    if (querieFile == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }

    char* line = NULL;  // Ponteiro para a linha, alocado dinamicamente pelo getline
    size_t len = 0;     // Tamanho do buffer usado pelo getline
    int min, max;
    int n;
    char country[256] = "";  // String para armazenar o país, inicializada como string vazia

    for (int i = 0; getline(&line, &len, querieFile) != -1; i++) {
        // Verifica se a linha tem pelo menos 1 caractere
        if (strlen(line) == 0) continue;

        // Remove a nova linha no final, se existir
        if (line[strlen(line) - 1] == '\n') {
            line[strlen(line) - 1] = '\0';
        }

        // Recupera controladores
        UsersData* UserController = getUserController(data);
        GHashTable* Utable = getUserTable(UserController);
        Age* usersAge = getUsersByAge(UserController);
        MusicData* MusicController = getMusicController(data);
        GHashTable* Mtable = getMusicsTable(MusicController);
        GHashTable* DInfotable = getDinfoTable(MusicController);
        ArtistsData* ArtistContoller = getartistController(data);
        GHashTable* ATable = getArtistsTable(ArtistContoller);

        switch (line[0]) {
            case '1':
                if (strlen(line) >= 2) {
                    querie1(Utable, line + 2, i);
                }
                break;

            case '2':
                // Limpa a string `country` antes de processar cada linha
                strcpy(country, "");

                // Lê o número e a string entre aspas, se existir
                int query2_result = sscanf(line + 1, "%d \"%[^\"]\"", &n, country);

                if (query2_result == 1) {
                    // Apenas o número foi lido, país não fornecido
                    strcpy(country, "");  // Define `country` como string vazia
                }

                // Debug para verificar o valor capturado de `country`
                printf("COUNTRY DA QUERY: '%s'\n", country);

                // Executa a query 2
                querie2(DInfotable, ATable, n, i, country);
                break;

            case '3':
                sscanf(line + 1, "%d %d", &min, &max);
                querie3(i, Mtable, min, max, usersAge);
                break;

            default:
                break;
        }
    }

    // Libera a memória alocada por getline
    free(line);
}

