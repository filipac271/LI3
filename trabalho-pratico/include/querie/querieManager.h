#ifndef QUERIEMANAGER_H
#define QUERIEMANAGER_H



#include <stdio.h>
#include <stdlib.h>
#include <glib.h>
#include "controler/usersController.h"
#include "controler/mainController.h"
#include "utilidades.h" 

int validaQ1Input(char *argumentos,char possivelS);
int validaQ2Input(char *argumentos,char possivelS);
int validaQ3Input(char *argumentos,char possivelS);
int validaQ4Input(char *argumentos,char possivelS);
int validaQ5Input(char *argumentos,char possivelS);
int validaQ6Input(char *argumentos,char possivelS);


void queries (MainController* data, char* querieFile);



#endif