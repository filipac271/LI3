#ifndef USERSCONTROLLER_H
#define USERSCONTROLLER_H
#include <glib.h>

typedef struct users User;



User* newUser (char* username_, char* email_, char* first_name, char* last_name, char * birth_Date, char* pais, char* subscricao, char** liked_Songs_id,int songsN);
void freeUser (User* user);


GHashTable* createTable();
void printUser(User* user);
void insertUser(GHashTable* table, User* user);
void print_all_users(GHashTable* userTable);
void print_user_entry (gpointer key, gpointer value, gpointer user_data);
User* fetchUser(GHashTable* table, char* username);


char* getUserEmail(User* user);
char* getUserNome(User* user);
char* getUserApelido(User* user);
char* getUserBirthDate(User* user);
char* getUserCountry(User* user);
char* getUserSubscryptionType(User* user);
char** getUserLikedSongs(User* user);
int getUserNumberLikedSongs(User* user);




#endif
