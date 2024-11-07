#include "querie/querieManager.h"
#include "controler/usersController.h"
#include "controler/mainController.h"
#include "querie/querie1.h"
#include  "querie/querie2.h"
#include  "querie/querie3.h"
#include "utilidades.h"
#include "IOManager.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <glib.h>





void queries (MainController* data, char* querieFile) {

    Parser* parserQ = newParser(querieFile,"");
    char* line = NULL;
    line = pegaLinha(parserQ);


    int min, max;
    int n;
    char country[256] = "";  // String para armazenar o país, inicializada como string vazia
    int i = 0;
    for (i = 0; line != NULL; i++) {
        // Verifica se a linha tem pelo menos 1 caractere
        if (strlen(line) == 0) continue;


        // Recupera controladores
        UsersData* UserController = getUserController(data);
        ArtistsData* ArtistContoller = getartistController(data);

        switch (line[0]) {
            case '1':
                if (strlen(line) >= 2) {
                    querie1(UserController, line + 2, i);
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


                // Executa a query 2
                querie2(ArtistContoller, n, i, country);
                break;

            case '3':
                sscanf(line + 1, "%d %d", &min, &max);
                querie3(i, min, max, UserController);
                break;

            default:
                break;
        }

        free(line);
        line = pegaLinha(parserQ);
    }

    freeParser(parserQ);

    
}

