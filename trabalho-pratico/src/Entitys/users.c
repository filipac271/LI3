#include "Entitys/users.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <glib.h>


struct users
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

};


struct usersByAge
{
    char** likedSongs;
    int numberSongs;
};


//Dá print de um user
void printUser(User* user) {
    if (user) {
        printf("User: %s\n", user->username);
        printf("mail: %s\n", user->email);
        printf("Name: %s\n", user->nome);
        printf("Last name: %s\n", user->apelido);
        printf("Data aniversario: %s\n", user->birth_date);
        printf("pais: %s\n", user->country);
        printf("SUBS: %s\n", user->subscription_type);
        printf("cancoes :\n");
        for(int i=0; i<user->number_liked_songs;i++)
        {
        printf("%s  ",user->liked_songs_id[i]);
        }
        printf("\n");
    }
    else printf("N tenho nada para printar\n");
}

 Age* createUsersAge()
{
  
    Age * usersAge=malloc(130* sizeof(Age));
     memset(usersAge, 0, 130 * sizeof(Age));
    return usersAge;
}


// Cria um novo user 
User* newUser (char* username_, char* email_, char* first_name, char* last_name, char * birth_Date, char* pais, char* subscricao, char** liked_Songs_id,int songsN)
{
    User* user= malloc(sizeof(User));
    
    user->username=strdup(username_);
    user->email=strdup(email_);
    user->nome=strdup(first_name);
    user->apelido=strdup(last_name);
    user->birth_date=strdup(birth_Date);
    user->country=strdup(pais);
    user->subscription_type=strdup(subscricao); 
  
    user->liked_songs_id = malloc((songsN+1) * sizeof(char*));  // Aloca memória para o array de ponteiros
    for (int i = 0; i < songsN; i++) {
      user->liked_songs_id[i] = strdup(liked_Songs_id[i]);  // Duplica cada string  
    }

  
    user->number_liked_songs= songsN;
    
    return user;
   
}


Age* newAge(Age* usersByAge, int idade,int newSongCount, char** newSongs)
{
 
     usersByAge[idade].likedSongs=(char**)malloc(newSongCount * sizeof(char*));
       for (int j = 0; j < newSongCount; j++) { 

            usersByAge[idade].likedSongs[j] = strdup(newSongs[j]);  // Copy the song strings
        }
        usersByAge[idade].numberSongs = newSongCount;
        return usersByAge;
       
}

Age* newSongsAge (Age* usersByAge, int idade,int newSongCount, char** newSongs)
{
      int oldSongCount = usersByAge[idade].numberSongs;
        int totalSongs = oldSongCount + newSongCount;
          
        usersByAge[idade].likedSongs = (char**)realloc(usersByAge[idade].likedSongs, totalSongs * sizeof(char*));

        for (int j = 0; j < newSongCount; j++) {
            usersByAge[idade].likedSongs[oldSongCount + j] = strdup(newSongs[j]);
        }
        usersByAge[idade].numberSongs = totalSongs; // Update the song count
        return usersByAge;
     
}


void freeUser(User* user) {
    
     if (user == NULL)
    {    
         return;
    }
  
    free(user->username); 
    free(user->email);
    free(user->nome);
    free(user->apelido);
    free(user->birth_date);
    free(user->country); 
    free(user->subscription_type);
 
    int i;
    for( i=0;i<user->number_liked_songs;i++)
       {  
         free(user->liked_songs_id[i]);  
       }
    free(user->liked_songs_id);
    free(user); 
}
   
void freeUsersByAge(Age* usersByAge){
      for(int i=0; i<130;i++)
   {
      if(usersByAge[i].likedSongs==NULL)
      {
        continue; 
      } 
      else{
        
      for (int j = 0; j < usersByAge[i].numberSongs ; j++)
      {
        free(usersByAge[i].likedSongs[j]);
      }
       free(usersByAge[i].likedSongs);

         
      }
   }
     free(usersByAge);

}



// Retorna a data de nascimento
 char* getUserBirthDate(User* user) {
    return user->birth_date;
}

// Retorna o email
 char* getUserEmail(User* user) {
    return user->email;
}

// Retorna o nome
 char* getUserNome(User* user) {
    return user->nome;
}

// Retorna o apelido
 char* getUserApelido(User* user) {
    return user->apelido;
}

// Retorna o país
 char* getUserCountry(User* user) {
    return user->country;
}

// Retorna o SubscryptionType
 char* getUserSubscryptionType(User* user) {
    return user->subscription_type;
}

// Retorna o liked_songs
 char** getUserLikedSongs(User* user) {
    return user->liked_songs_id;
}

// Retorna o número de liked_songs
 int getUserNumberLikedSongs(User* user) {
    return user->number_liked_songs;
}

int getUBANumberSongs(Age *userAge,int idade){
    return (userAge[idade].numberSongs);
}


char** getUBALikedSongs(Age *userAge,int idade){
    return strdup (userAge[idade].likedSongs);
}
