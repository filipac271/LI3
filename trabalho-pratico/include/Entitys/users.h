#ifndef USERS_H
#define USERS_H


typedef struct users User;

typedef struct usersByAge Age;


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


Age* newAge(Age* usersByAge, int idade,int newSongCount, char** newSongs);
Age* newSongsAge (Age* usersByAge, int idade,int newSongCount, char** newSongs);
Age* createUsersAge();


char** getUBALikedSongs(Age *userAge,int idade);
int getUBANumberSongs(Age *userAge,int idade);
void freeUsersByAge(Age* usersByAge);
#endif

