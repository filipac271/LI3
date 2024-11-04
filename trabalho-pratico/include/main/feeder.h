#ifndef FEEDER_H
#define FEEDER_H

#include <stdio.h>  
#include <stdlib.h>
#include <string.h>
#include <glib.h>

#include "parser/userParser.h"
#include "controler/mainController.h"

MainController* feeder(char* diretoria);


#endif