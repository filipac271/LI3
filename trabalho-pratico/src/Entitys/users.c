#include "Entitys/users.h"
#include "controler/musicsController.h"
#include "utilidades.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#define numGenerosDif 10
#define numIdades 130
#define InitMaxUsers 260000


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
    int posicaoChegada;

};



struct usersByAge
{
    char** generos;
    int numSongs[numGenerosDif];
    int numGeneros;
};

struct query5 {
    GArray* usersIds;
    char** nomesGeneros;
    int numUsers;
    int numGeneros;
    GArray* preferencias;
    int numGenerosDiferentes;


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

Query5* createQ5Struct(MusicData* musicController) {

    Query5* usersMatrizQ5 = malloc(sizeof(Query5));
    if (!usersMatrizQ5) {
        fprintf(stderr, "Erro ao alocar memória para Query5\n");
        exit(1);
    }

    usersMatrizQ5->numGenerosDiferentes = getnumGenerosDif(musicController);

    usersMatrizQ5->nomesGeneros = malloc(sizeof(char*) * usersMatrizQ5->numGenerosDiferentes);


    for (int i = 0; i < usersMatrizQ5->numGenerosDiferentes; i++) {
        usersMatrizQ5->nomesGeneros[i] = NULL;
    }


    // Inicializando o GArray para usersIds
    usersMatrizQ5->usersIds = g_array_new(TRUE, TRUE, sizeof(char*));  // GArray de strings (char*)

    // Inicializando o GArray para preferencias
    usersMatrizQ5->preferencias = g_array_new(FALSE, TRUE, sizeof(int*)); // GArray de arrays de inteiros

    usersMatrizQ5->numGeneros = 0;
    usersMatrizQ5->numUsers = 0;


    return usersMatrizQ5;
}




// Cria um novo user 
User* newUser (char** tokens,int posicaoChegada)
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

    user->posicaoChegada = posicaoChegada;

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


void freeQ5struct(Query5* q5) {
    if (!q5) return;

    for (int j = 0; j < q5->numGeneros; j++)
    {
        free(q5->nomesGeneros[j]);
    }
    free(q5->nomesGeneros);

    for (int i = 0; i < q5->numUsers; i++) {
        free(g_array_index(q5->usersIds, char*, i));  
    }
    g_array_free(q5->usersIds, TRUE);  

    for (int i = 0; i < q5->numUsers; i++) {
        free(g_array_index(q5->preferencias, int*, i));  
    }
    g_array_free(q5->preferencias, TRUE);  


    free(q5);
}



void atualizaGeneros(char* genero,Query5* q5,User* user){

    int i = 0;

    while (i < q5->numGeneros + 1)
    {
    if (q5->nomesGeneros[i] == NULL ){
        q5->nomesGeneros[i] = genero;
        q5->numGeneros += 1;
        g_array_index(q5->preferencias, int*, user->posicaoChegada)[i] += 1;
        break;
    } 
    if(strcmp(q5->nomesGeneros[i],genero) == 0){
        free(genero);
        g_array_index(q5->preferencias, int*, user->posicaoChegada)[i] += 1;
        break;
    }

    i++;
    }
  
}

void criaLinhaPreferencia(int posicaoChegada, Query5* q5) {
    int* novaPreferencia = malloc(sizeof(int) * q5->numGenerosDiferentes);
    
    for (int i = 0; i < q5->numGenerosDiferentes; i++) {   
        novaPreferencia[i] = 0;
    }

    g_array_insert_val(q5->preferencias, posicaoChegada, novaPreferencia);

}



void inserirUserQ5(char* username, Query5* q5) {
    
    size_t len = strlen(username);
    char* user_copy = g_strndup(username + 1, len - 2);  // Copia a string sem as aspas
    g_array_append_val(q5->usersIds, user_copy);

    
    q5->numUsers++;
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


int** getPreferenciasQ5(Query5* q5){
    int** prefre = malloc(q5->numUsers * sizeof(int*));
    for (int i = 0; i < q5->numUsers; i++) {
        prefre[i] = malloc(sizeof(int) * q5->numGeneros);

        int* preferenciasUsuario = g_array_index(q5->preferencias, int*, i); 

        memcpy(prefre[i], preferenciasUsuario, q5->numGeneros * sizeof(int)); 
    }    
    return prefre;
}



char** getUsersId(Query5* q5){
    char** usersId = malloc(q5->numUsers * sizeof(char*));

    for (int i = 0; i < q5->numUsers; i++) {
        usersId[i] = strdup(g_array_index(q5->usersIds, char*, i)); 
    }

    return usersId;
}



char** getGenerosNomes(Query5* q5){
    char** nomeSGeneros = malloc(q5->numGeneros * sizeof(char*));
    for (int i = 0; i < q5->numGeneros; i++)
    {
        nomeSGeneros[i] = strdup(q5->nomesGeneros[i]);
    }

    return nomeSGeneros;
}

int getnumUsers (Query5* q5){
    return q5->numUsers;
}

int getnumGeneros (Query5* q5){
    return q5->numGeneros;
}

int getPosicaoChegada (User* user){
    return user->posicaoChegada;
}

