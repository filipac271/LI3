#ifndef USERSCONTROLLER_H
#define USERSCONTROLLER_H
#include <glib.h>
#include <stdio.h>
#include <stdlib.h>
#include "Entitys/users.h"
#include "controler/musicsController.h"


typedef struct usersData UsersData;


UsersData* usersFeed(char* diretoria, MusicData* musicData);

GHashTable* createTable();
void insertUser(GHashTable* table, User* user,char* id);
void print_all_users(UsersData* data);
void print_user_entry (gpointer key, gpointer value, gpointer user_data);
User* fetchUser(UsersData* controlador, char* username);
void destroyUsersData(UsersData* data);
Age* getUsersByAge(UsersData* data);
Age* insertLikedSongs( Age* usersByAge, int idade,char** newSongs,int newSongCount);


#endif
