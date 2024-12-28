#include "controler/usersController.h"
#include "controler/artistsController.h"
#include "controler/mainController.h"
#include "controler/historyController.h"
#include "querie/querie1.h"
#include  "querie/querie2.h"
#include  "querie/querie3.h"
#include "querie/query4.h"
#include "querie/query5.h"
#include "utilidades.h"
#include "Input.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <glib.h>





void queries (MainController* data, char* querieFile) {
    Parser* parserQ = newParser(querieFile,"");
    char* line = NULL;
    line = pegaLinha(parserQ); 
    // Recupera controladores
    UsersData* UserController = getUserController(data);
    ArtistsData* ArtistController = getartistController(data);
    HistoryData* HistoryConctoller = gethistoryController(data);

    int** elementosMatriz = getElementosMatrizQ5(UserController);
    char** idsUsers = getLinhasMatrizQ5(UserController);
    char** nomesGeneros = getColunasMatrizQ5(UserController);
    
    int i = 0;
    for (i = 0; line != NULL; i++) {

        switch (line[0]) {
            case '1':
                
                querie1(UserController, line, i,ArtistController);
                
                break;

            case '2':
                
                querie2(ArtistController, line, i);

                break;

            case '3':
            
                querie3(i, line, UserController);

                break;

            case '4':
            
                query4(HistoryConctoller, ArtistController, line, i );

                break;

            case'5':

                query5(line,i,UserController,elementosMatriz,idsUsers,nomesGeneros);


            break;
            default:
                break;
        }
        
        free(line);
        line = pegaLinha(parserQ);
    }
    freeQ5Matrizes(elementosMatriz,idsUsers,nomesGeneros,UserController);

    freeParser(parserQ);

    
}
