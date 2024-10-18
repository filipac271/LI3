#include "controler/usersController.h"
#include "controler/musicsController.h"
#include "validacao/validaUser.h"
#include "utilidades.h"
#include "Entitys/users.h"


#include <glib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>



struct usersData
{
    GHashTable* usersTable;
    Age* usersByAge;
};




UsersData* usersFeed(FILE* ficheiro, MusicData* musicData){

 UsersData* UData = malloc(sizeof(UsersData));  // Corrigido: alocando corretamente o tamanho de `ArtistsData`
    
    char *filename = malloc(sizeof(char) * 256);
    sprintf(filename, "resultados/users_errors.csv");
    FILE *errosFileUsers = fopen(filename, "w");
    free(filename);
    
    char* line = NULL;  // Inicializado como NULL para getline alocar memória
    size_t len = 0;
    char* tokens[8];
    
    UData->usersTable = createTable();
   
    UData->usersByAge=createUsersAge();
    // Ignorar a primeira linha
    getline(&line, &len, ficheiro);
    fprintf(errosFileUsers,"%s",line);
    
    while (1) {

        // Pega a próxima linha
        if (pegaLinha(ficheiro, &len, &line) == NULL){
           break; 
        } 
           // Remove a nova linha no final, se existir
    if (line[0] != '\0' && line[strlen(line) - 1] == '\n') {
        line[strlen(line) - 1] = '\0';
    }

        
        // Atualizar o lineOutput em cada iteração
        char lineOutput[2048];
        strncpy(lineOutput, line, 2048);  // Copia a linha para o buffer local
        lineOutput[2048 - 1] = '\0';  // Garante a terminação da string
        int numberSongs=1;
        
        parser(line, tokens);

        // Aqui os tokens devem corresponder à ordem dos dados no arquivo
        char* username = remove_quotes(tokens[0]);
        char* email= remove_quotes(tokens[1]);
        char* nome = remove_quotes(tokens[2]);
        char* apelido = remove_quotes(tokens[3]); 
        char* birth_date = remove_quotes(tokens[4]);
        char* country = remove_quotes(tokens[5]);
        char* subscription_type= remove_quotes(tokens[6]);
        char* songs=tokens[7];


        // Conta o numero de liked songs do user
        for (int i = 2; songs[i]!='\0'; i++){    
            if (songs[i] == ',') numberSongs++;
        }

       char** liked_songs_id =likedSongs(songs,numberSongs);
 

 
     

        int isValid = validaUser(email,birth_date,subscription_type,getMusicsTable(musicData),liked_songs_id,numberSongs);

        if(isValid){
        
        int idade= calcular_idade(birth_date);
        UData->usersByAge= insertLikedSongs(UData->usersByAge,idade,liked_songs_id,numberSongs);
      

        // Inserir os dados na hash table

        User* user= newUser(username, email ,nome , apelido,birth_date, country,subscription_type,liked_songs_id,numberSongs);
         insertUser(UData->usersTable,user,username); 
       
  
        }else{
            fprintf(errosFileUsers,"%s\n",lineOutput);
          
        }

      
        free(liked_songs_id); 
        freeCleanerUsers(username,email,nome , apelido,birth_date, country,subscription_type);
  
    }
    
    // Libera a memória alocada por getline
    free(line);
    
    fclose(errosFileUsers);
    return UData;
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
void insertUser(GHashTable* table, User* user,char* id)
{
       g_hash_table_insert(table, strdup(id), user);

      // printUser(user);
}

// Procurar (ou "Dar fetch")  um user na hash Table
User* fetchUser(GHashTable* table, char* username) {
    return  g_hash_table_lookup(table, username);
}


// Função callback para imprimir a hash table
void print_user_entry (gpointer key, gpointer value, gpointer user_data) {
    char* username = (char*)key;
    User* user= (User*)value;

    printUser(user);
}

// Função para imprimir toda a hash table
void print_all_users(UsersData* data) {
    printf("----- Hash Table de Users -----\n");
    sleep(3);
    g_hash_table_foreach(data->usersTable, print_user_entry, NULL);
    printf("----- Fim da Hash Table -----\n");
}

void destroyUsersData(UsersData* data){
    g_hash_table_destroy(data->usersTable);
    freeUsersByAge(data->usersByAge);
    printf("Tabela dos users destruida\n");
}



GHashTable* getUserTable(UsersData* data){
    return data->usersTable;
}
Age* getUsersByAge(UsersData* data){
    return data->usersByAge;
}


// Adiciona as cancoes à idade certa
Age* insertLikedSongs( Age* usersByAge, int idade,char** newSongs,int newSongCount)  {
 
   
    if (getUBANumberSongs(usersByAge,idade) == 0) {
       usersByAge=newAge(usersByAge,idade,newSongCount,newSongs);
    
    } else {
        // Quando já há cancoes
      usersByAge= newSongsAge(usersByAge,idade,newSongCount,newSongs);
    }
   // free(newSongs);
  return usersByAge;
    
}