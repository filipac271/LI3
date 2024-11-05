#include "controler/mainController.h"
#include "controler/artistsController.h"


#include <stdio.h>
#include <stdlib.h>
#include <glib.h>




MainController* feeder(char* diretoria) {

    

MainController* data = mainFeed(diretoria);


return data;

}
