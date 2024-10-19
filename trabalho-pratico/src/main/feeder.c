#include "controler/mainController.h"
#include "controler/artistsController.h"


#include <stdio.h>
#include <stdlib.h>
#include <glib.h>




MainController* feeder(FILE** ficheiros) {

    

MainController* data = mainFeed(ficheiros);


return data;

}
