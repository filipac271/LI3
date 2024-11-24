#include "Entitys/users.h"
#include "utilidades.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define numGenerosDif 15
#define numIdades 130


struct users
{
    int username;
    char* email;
    char* nome;
    char* apelido;
    char* birth_date;
    char* country;
    char* subscription_type;
    int* liked_songs_id;
    int number_liked_songs;

};



struct usersByAge
{
    char** generos;
    int numSongs[numGenerosDif];
    int numGeneros;
};

//Dá print de um user
void printUser(User* user) {
    if (user) {
        printf("User: %d\n", user->username);
        printf("mail: %s\n", user->email);
        printf("Name: %s\n", user->nome);
        printf("Last name: %s\n", user->apelido);
        printf("Data aniversario: %s\n", user->birth_date);
        printf("pais: %s\n", user->country);
        printf("SUBS: %s\n", user->subscription_type);
        printf("cancoes :\n");

        for(int i=0; i<user->number_liked_songs;i++)
        {
        printf("%d  ",user->liked_songs_id[i]);
        }
        printf("\n");

    }
    else printf("N tenho nada para printar\n");
}

 Age* createUsersAge()
{
  
    struct usersByAge* usersAge = malloc(numIdades * sizeof(struct usersByAge));
    for (int i = 0; i < numIdades; i++) {
    usersAge[i].numGeneros = 0; 
    for (int j=0;j<numGenerosDif;j++)
    {
        usersAge[i].numSongs[j]=0;
    }
    
    }

    return usersAge;
}


// Cria um novo user 
User* newUser (char** tokens)
{
    User* user= malloc(sizeof(User));
    if(user == NULL){
        fprintf(stderr, "Memory allocation failed for new user\n");
        exit(1);
    }

    char* songs = tokens[7];
    int numSongs=calculate_num_members(songs);
    int* liked_songs_id =divideArray(songs,numSongs);
 
    //O remove quotes já manda uma cópia

    user->username =transformaIds(tokens[0]);

    user->email=remove_quotes(tokens[1]);
    user->nome=remove_quotes(tokens[2]);
    user->apelido=remove_quotes(tokens[3]);
    user->birth_date=remove_quotes(tokens[4]);
    user->country=remove_quotes(tokens[5]);
    user->subscription_type=remove_quotes(tokens[6]); 

    user->liked_songs_id = malloc((numSongs) * sizeof(int));
    for (int i = 0; i < numSongs; i++) {
        user->liked_songs_id[i] = liked_songs_id[i];
    }
    user->number_liked_songs= numSongs;


    freeArray(liked_songs_id);

    
    return user; 
}



Age *insertGenero(Age* usersByAge, int idade, char* genero )

{
    int inserido=0;
    int nGeneros=usersByAge[idade].numGeneros;

    if (nGeneros==0)
    {     
        usersByAge[idade].generos=malloc(numGenerosDif * sizeof(char*));
        usersByAge[idade].generos[nGeneros]=strdup(genero);
        usersByAge[idade].numSongs[nGeneros]=1;
        usersByAge[idade].numGeneros=1;
    }
    else{

 
    for(int i=0;i<nGeneros && !inserido;i++)
    {
        if(strcmp(usersByAge[idade].generos[i],genero)==0)
        {
            usersByAge[idade].numSongs[i]++;
            inserido=1;
        }
    }
    if(!inserido )
    {
        usersByAge[idade].generos[nGeneros]=strdup(genero);
        usersByAge[idade].numSongs[nGeneros]+=1;
        usersByAge[idade].numGeneros++;
    }

      }
    return usersByAge;
}

void freeUser(User* user) {
    
    if (user == NULL)
    {    
         return;
    }
  
    free(user->email);
    free(user->nome);
    free(user->apelido);
    free(user->birth_date);
    free(user->country); 
    free(user->subscription_type);
 
    free(user->liked_songs_id);
    free(user); 
}
   
void freeUsersByAge(Age* usersByAge){
    
   for (int i=0;i<numIdades;i++)
   {
    if(usersByAge[i].numGeneros>0)
    {
      
        for(int j = 0 ; j < usersByAge[i].numGeneros; j++)
            {
             free(usersByAge[i].generos[j]);
            }

        free(usersByAge[i].generos);
    }
   }

    free(usersByAge);

}


//Getters

// Retorna a data de nascimento
 char* getUserBirthDate(User* user) {
    return strdup(user->birth_date);
}

// Retorna o email
 char* getUserEmail(User* user) {
    return strdup(user->email);
}

// Retorna o nome
 char* getUserNome(User* user) {
    return strdup(user->nome);
}

// Retorna o apelido
 char* getUserApelido(User* user) {
    return strdup(user->apelido);
}

// Retorna o país
 char* getUserCountry(User* user) {
    return strdup(user->country);
}

// Retorna o SubscryptionType
 char* getUserSubscryptionType(User* user) {
    return strdup(user->subscription_type);
}

// // Retorna o liked_songs
//  char** getUserLikedSongs(User* user) {
//     return user->liked_songs_id;
// }

// Retorna o número de liked_songs
 int getUserNumberLikedSongs(User* user) {
    return user->number_liked_songs;
}

int getUBANumberSongs(Age *userAge,int idade, int i){

    return (userAge[idade].numSongs[i]);
}



char* getGenero(Age *userAge,int idade,int i){
    char * genero= strdup(userAge[idade].generos[i]);
    return genero ;
}

int getNGeneros(Age* userAge,int idade)
{
    return userAge[idade].numGeneros;
}



