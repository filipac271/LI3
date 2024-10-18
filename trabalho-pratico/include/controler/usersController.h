#ifndef USERSCONTROLLER_H
#define USERSCONTROLLER_H
#include <glib.h>
#include <stdio.h>
#include <stdlib.h>
#include "Entitys/users.h"
#include "controler/musicsController.h"


typedef struct usersData UsersData;


UsersData* usersFeed(FILE* ficheiro, MusicData* musicData);

GHashTable* createTable();
void insertUser(GHashTable* table, User* user,char* id);
void print_all_users(UsersData* data);
void print_user_entry (gpointer key, gpointer value, gpointer user_data);
User* fetchUser(GHashTable* table, char* username);
void destroyUsersTable(UsersData* data);


GHashTable* getUserTable(UsersData* data);


#endif
