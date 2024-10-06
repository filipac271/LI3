#ifndef USERSCONTROLLER_H
#define USERSCONTROLLER_H

typedef struct users
{
char* username;
char* email;
char* nome;
char* apelido;
char* birth_date;
char* country;
char* subscription_type;
char** liked_songs_id;
int number_liked_songs;

}User;



User* newUser (char* username_, char* email_, char* first_name, char* last_name, char * birth_Date, char* pais, char* subscricao, char** liked_Songs_id,int songsN);
void freeUser (User* user);


GHashTable* createTable();
void printUser(User* user);
void insertUser(GHashTable* table, User* user);
void print_all_users(GHashTable* userTable);
void print_user_entry (gpointer key, gpointer value, gpointer user_data);
User* fetchUser(GHashTable* table, char* username);


#endif
