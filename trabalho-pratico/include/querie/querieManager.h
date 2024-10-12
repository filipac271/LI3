#ifndef QUERIEMANAGER_H
#define QUERIEMANAGER_H



#include <stdio.h>
#include <stdlib.h>
#include <glib.h>
#include "parser/userParser.h" 

void queries (GHashTable** tables, FILE* querieFile, Age* userByAge);



#endif