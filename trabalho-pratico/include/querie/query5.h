#ifndef QUERY5_H
#define QUERY5_H
#include "controler/usersController.h"

void freeQ5Matrizes(int** elementosMatriz,char** idsUsers,char** nomesGeneros, UsersData* userControllador);
void query5(char* line, int i, UsersData* userControllador,int** elementosMatriz,char** idsUsers,char** nomesGeneros);

#endif