#include "controler/usersController.h"
#include "controler/musicsController.h"
#include "validacao/validaUser.h"
#include "utilidades.h"
#include "Entitys/users.h"
#include "IOManager.h"



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




UsersData* usersFeed(char* diretoria, MusicData* musicData){

 UsersData* UData = malloc(sizeof(UsersData));  // Corrigido: alocando corretamente o tamanho de `ArtistsData`

    char *filename = malloc(sizeof(char) * 256);
    sprintf(filename, "resultados/users_errors.csv");
    Output* Erros= iniciaOutput(filename);
    free(filename);
    
    // char* line = NULL;  // Inicializado como NULL para getline alocar memória
    // size_t len = 0;
    // char* tokens[8];
    
    UData->usersTable = createTable();
   
    UData->usersByAge=createUsersAge();
    Parser* parserE= newParser(diretoria,"users.csv");
    // Ignorar a primeira linha


    char* line = pegaLinha(parserE);
    outputErros(Erros,line);
    free(line);

    while (1) {


      

        
        parserE= parser(parserE); 


      char** tokens= getTokens(parserE); 
      if (tokens==NULL) 
     {
          freeParser(parserE); break;
     }
        
        int numberSongs=1;
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
 

 
     
         char* linhaE=getLineError(parserE);
        int isValid = validaUser(email,birth_date,subscription_type,musicData,liked_songs_id,numberSongs,Erros,linhaE);

        if(isValid){
           
        
        int idade= calcular_idade(birth_date);
     
        UData->usersByAge= insertGeneros(UData->usersByAge,idade,liked_songs_id,numberSongs, musicData);
       

        // Inserir os dados na hash table

        User* user= newUser(username, email ,nome , apelido,birth_date, country,subscription_type,liked_songs_id,numberSongs);
         insertUser(UData->usersTable,user,username); 
       
  

        }

      
        free(liked_songs_id); 
        freeCleanerUsers(username,email,nome , apelido,birth_date, country,subscription_type);
        free(linhaE);
        free(getLine(parserE));
    
    }


    freeOutput(Erros);
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
User* fetchUser(UsersData* controlador, char* username) {
    return  g_hash_table_lookup(controlador->usersTable, username);
}


// Função callback para imprimir a hash table
void print_user_entry (gpointer key, gpointer value, gpointer user_data) {

    if (key == NULL || value == NULL) {
        printf( "Chave ou valor nulo encontrado.\n");
        sleep(2);
        return;
    }

    // Suprime o aviso de variáveis não usadas
    (void)user_data;
    //char* username = (char*)key;
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


/*
GHashTable* getUserTable(UsersData* data){
    return data->usersTable;
}*/
Age* getUsersByAge(UsersData* data){
    return data->usersByAge;
}


Age* insertGeneros(Age* usersByAge, int idade,char** Songs,int SongCount, MusicData* musicController)
{
   

    for(int i=0;i<SongCount;i++)
    {
        Music* song= lookup_musica(musicController,Songs[i]);
         char* genero=get_music_genre(song);
        usersByAge= insertGenero(usersByAge,idade,genero);
       
    }
     return usersByAge;
        
        
}



char* getUBAGenero(UsersData * userController,int idade,int i) {
    Age* usersByAge= getUsersByAge(userController);

    char* genero= strdup (getGenero(usersByAge,idade,i) );

    return genero;

}

int getUBANSongs(UsersData* userController, int idade, int j)
{

      Age* usersByAge= userController->usersByAge;
      int Nsongs=getUBANumberSongs(usersByAge,idade, j);
      return Nsongs;



}
int getUBANGeneros(UsersData * userController,int idade)
{
      Age* usersByAge= userController->usersByAge;
      int nGeneros= getNGeneros(usersByAge, idade);
      return nGeneros;
}
