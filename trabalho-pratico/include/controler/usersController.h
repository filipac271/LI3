#ifndef USERSCONTROLLER_H
#define USERSCONTROLLER_H

#include "Entitys/users.h"
#include "controler/musicsController.h"


typedef struct usersData UsersData;



UsersData* usersFeed(char* diretoria, MusicData* musicData);

void print_all_users(UsersData* data);


User* fetchUser(UsersData* controlador, int username);

void destroyUsersData(UsersData* data);

char* getUBAGenero(UsersData * userController,int idade,int i);

int getUBANSongs(UsersData* userController, int idade, int j);

int getUBANGeneros(UsersData * userController,int idade);

void atualizaPrefsUser(char* generoMusica, char* username, UsersData* userController);

int** getElementosMatrizQ5(UsersData* userController);

char** getLinhasMatrizQ5(UsersData* userController);

char** getColunasMatrizQ5(UsersData* userController);


int getNumLinhas(UsersData* userController);

int getNumColunas(UsersData* userController);

int getPosicaoUser(UsersData* userController,char* username);

char* getUserBirthDateControl(UsersData* controlador, int username);

char* getUserEmailControl(UsersData* controlador, int username);

char* getUserNomeControl(UsersData* controlador, int username);

char* getUserApelidoControl(UsersData* controlador, int username);

char* getUserCountryControl(UsersData* controlador, int username);

char* getUserSubscryptionTypeControl(UsersData* controlador, int username) ;

int isUserValid(UsersData* controlador, int userName);

#endif
