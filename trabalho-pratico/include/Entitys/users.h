#ifndef USERS_H
#define USERS_H


typedef struct users User;




User* newUser (char* username_, char* email_, char* first_name, char* last_name, char * birth_Date, char* pais, char* subscricao, char** liked_Songs_id,int songsN);
void freeUser (User* user);
void printUser(User* user);



char* getUserEmail(User* user);
char* getUserNome(User* user);
char* getUserApelido(User* user);
char* getUserBirthDate(User* user);
char* getUserCountry(User* user);
char* getUserSubscryptionType(User* user);
char** getUserLikedSongs(User* user);
int getUserNumberLikedSongs(User* user);


#endif

