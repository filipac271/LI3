#include "controler/usersController.h"
#include "validacao/validaUser.h"
#include "utilidades.h"


#include <glib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

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


// Criar uma nova hash table
GHashTable* createTable() {
   GHashTable* usersTable=g_hash_table_new_full(g_str_hash, g_str_equal, free, (GDestroyNotify)freeUser);
       if (usersTable == NULL) {
        printf("Erro: Hash table dos users não foi criada.\n");
        exit(1);
    } else {
        printf("Hash table dos users criada com sucesso.\n");
    }
    return usersTable;
}

//Inseir user na Hash Table
void insertUser(GHashTable* table, User* user)
{
       g_hash_table_insert(table, strdup(user->username), user);

      // printUser(user);
}

// Procurar (ou "Dar fetch")  um user na hash Table
User* fetchUser(GHashTable* table, char* username) {
    return (User*) g_hash_table_lookup(table, username);
}


// Função callback para imprimir a hash table
void print_user_entry (gpointer key, gpointer value, gpointer user_data) {
    char* username = (char*)key;
    User* user= (User*)value;

    printUser(user);
}

// Função para imprimir toda a hash table
void print_all_users(GHashTable* userTable) {
    printf("----- Hash Table de Users -----\n");
    sleep(3);
    g_hash_table_foreach(userTable, print_user_entry, NULL);
    printf("----- Fim da Hash Table -----\n");
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





