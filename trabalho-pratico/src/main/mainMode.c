#include "main/feeder.h"
#include "parser/parsermusica.h"
#include "parser/userParser.h"
#include "controler/artistsController.h"
#include "controler/usersController.h"
#include "controler/musicsController.h"
#include "controler/mainController.h"
#include "querie/querieManager.h"
#include "IOManager.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <glib.h>





int principal(char** argv) {

    char* pastaPrincipal = argv[1];  // Recebe a pasta principal como argumento
    
    char* queriesFile = argv[2];    // Recebe o ficheiro das queries como argumento


    MainController* data = feeder(pastaPrincipal);
    print_all_Data(data);



    queries(data,queriesFile);
    
    destroyData(data);



    return 0;
}