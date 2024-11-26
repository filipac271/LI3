#include "controler/usersController.h"
#include "controler/artistsController.h"
#include "controler/mainController.h"
#include "querie/querie1.h"
#include  "querie/querie2.h"
#include  "querie/querie3.h"
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

    int i = 0;
    for (i = 0; line != NULL; i++) {


        // Recupera controladores
        UsersData* UserController = getUserController(data);
        ArtistsData* ArtistContoller = getartistController(data);

        switch (line[0]) {
            case '1':
                
                querie1(UserController, line + 2, i, line[1]);
                
                break;

            case '2':
                
                querie2(ArtistContoller, line, i);

                break;

            case '3':
            
                querie3(i, line, UserController);

                break;

            default:
                break;
        }

        free(line);
        line = pegaLinha(parserQ);
    }

    freeParser(parserQ);

    
}
