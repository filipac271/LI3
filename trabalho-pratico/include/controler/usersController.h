#ifndef USERSCONTROLLER_H
#define USERSCONTROLLER_H
#include <glib.h>
#include <stdio.h>
#include <stdlib.h>
#include "Entitys/users.h"
#include "controler/musicsController.h"


typedef struct usersData UsersData;

UsersData* usersFeed(char* diretoria, MusicData* musicData);

void print_all_users(UsersData* data);

void print_user_entry (gpointer key, gpointer value, gpointer user_data);

User* fetchUser(UsersData* controlador, int username);

void destroyUsersData(UsersData* data);

Age* getUsersByAge(UsersData* data);

char* getUBAGenero(UsersData * userController,int idade,int i);

int getUBANSongs(UsersData* userController, int idade, int j);

int getUBANGeneros(UsersData * userController,int idade);

#endif
