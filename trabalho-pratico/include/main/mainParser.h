#ifndef MAINPARSER_H
#define MAINPARSER_H

#include <stdio.h>  
#include <stdlib.h>
#include <string.h>
#include <glib.h>

#include "parser/userParser.h"

GHashTable** parser(FILE** ficheiros, Age* songsByAge);


#endif