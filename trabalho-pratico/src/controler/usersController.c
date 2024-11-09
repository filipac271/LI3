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


    UsersData* UData = malloc(sizeof(UsersData));
    if(UData == NULL){
        fprintf(stderr,"Alocação de memória do UsersController não foi bem sucedido");
        exit(1);
    }  

    //Abre o ficheiro  "users_errors.csv" e aloca memória para o respetivo pointer 
    Output* Erros= iniciaOutput("resultados/users_errors.csv");

    
    UData->usersTable = createTable();
    UData->usersByAge=createUsersAge();

     //Inicia o Parser e abre o ficheiro "users.csv" do dataset
    Parser* parserE= newParser(diretoria,"users.csv");

    // Ignorar a primeira linha
     char* line = pegaLinha(parserE);
     //Enviar a linha para o ficheiro users_erros.csv, esta não será inserida hashTable
    outputErros(Erros,line);
    free(line);

    while (1) {

        
        parserE= parser(parserE); 

        char** tokens= getTokens(parserE); 
      


        if (tokens==NULL) 
         {
            // Fecha o ficheiro guardado no Parser e liberta a memória alocada neste
              freeParser(parserE); break;

         }
        
      
        char* username = remove_quotes(tokens[0]);
        char* email= remove_quotes(tokens[1]);
        char* nome = remove_quotes(tokens[2]);
        char* apelido = remove_quotes(tokens[3]); 
        char* birth_date = remove_quotes(tokens[4]);
        char* country = remove_quotes(tokens[5]);
        char* subscription_type= remove_quotes(tokens[6]);
        char* songs=tokens[7];


        int numberSongs=1;

        // Conta o número de liked songs do user
        for (int i = 2; songs[i]!='\0'; i++){    
            if (songs[i] == ',') numberSongs++;
        }

        char** liked_songs_id =likedSongs(songs,numberSongs);
 
        // Linha do input para validação, esta será enviada para o output de erros caso não seja válida
        char* linhaE=getLineError(parserE);
        int isValid = validaUser(email,birth_date,subscription_type,musicData,liked_songs_id,numberSongs,Erros,linhaE);


        if(isValid){  
            
            int idade= calcular_idade(birth_date); 

            //  Inserir os Géneros das Liked Songs no array usersByAge
            UData->usersByAge= insertGeneros(UData->usersByAge,idade,liked_songs_id,numberSongs, musicData);
       
            // Criar o User e inseri-lo na Hash Table
             User* user= newUser(username, email ,nome , apelido,birth_date, country,subscription_type,liked_songs_id,numberSongs);
             insertUser(UData->usersTable,user,username); 

        }

      
        free(liked_songs_id); 
        freeCleanerUsers(username,email,nome , apelido,birth_date, country,subscription_type);
        free(linhaE);
        free(getLine(parserE));
    
    }

    // Liberta a memória alocada pelo Output Erros e fecha o ficheiro dos erros
    freeOutput(Erros);
    return UData;
}






// Criar a Hash Table dos Users
GHashTable* createTable() {

    // A key da Hash Table é o UserName  
   GHashTable* usersTable=g_hash_table_new_full(g_str_hash, g_str_equal, free, (GDestroyNotify)freeUser);

   // Verificar se a hash table foi criada corretamente 
   if (usersTable == NULL) {

        printf("Erro: Hash table dos users não foi criada.\n");
        exit(1);

    } else {
        printf("Hash table dos users criada com sucesso.\n");
    }

    return usersTable;
}


//Inserir o user na Hash Table
void insertUser(GHashTable* table, User* user,char* id)
{
       g_hash_table_insert(table, strdup(id), user);

}

// Procurar um user na hash Table
User* fetchUser(UsersData* controlador, char* username) {

    return  g_hash_table_lookup(controlador->usersTable, username);

}


// Função callback para imprimir a hash table dos users
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

// Função para imprimir toda a hash table dos Users
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


Age* getUsersByAge(UsersData* data){
    return data->usersByAge;
}


// Inserir os géneros das músicas no array usersByAge
Age* insertGeneros(Age* usersByAge, int idade,char** Songs,int SongCount, MusicData* musicController)
{
   for(int i=0;i<SongCount;i++)
    {
        Music* song= lookup_musica(musicController,Songs[i]);
         char* genero=get_music_genre(song);
        usersByAge= insertGenero(usersByAge,idade,genero);
        free(genero);
       
    }

     return usersByAge;    
  
}



// Procura o género no array usersByAge de uma dada idade na posição i
char* getUBAGenero(UsersData * userController,int idade,int i) {

    Age* usersByAge= getUsersByAge(userController);
    char* genero= getGenero(usersByAge,idade,i);
    char* copiaGenero = strdup(genero);
    free(genero);

    return copiaGenero;

}


/// Procura o número de músicas no array usersByAge de uma dada idade na posição i
int getUBANSongs(UsersData* userController, int idade, int j)
{

      Age* usersByAge= userController->usersByAge;
      int Nsongs=getUBANumberSongs(usersByAge,idade, j);

      return Nsongs;

}


/// Procura o número de géneros no array usersByAge de uma dada idade 
int getUBANGeneros(UsersData * userController,int idade)
{
      Age* usersByAge= userController->usersByAge;
      int nGeneros= getNGeneros(usersByAge, idade);

      return nGeneros;
}
