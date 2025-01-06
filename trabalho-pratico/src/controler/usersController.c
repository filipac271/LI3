#include "controler/usersController.h"
#include "controler/musicsController.h"
#include "validacao/validaUser.h"
#include "utilidades.h"
#include "Entities/users.h"
#include "Input.h"

#include <glib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>



struct usersData
{
    GHashTable* usersTable;
    Age* usersByAge;
    Query5* usersMatrizQ5;
};


// Criar a Hash Table dos Users
GHashTable* createTable() {

    // A key da Hash Table é o UserName  
   GHashTable* usersTable=g_hash_table_new_full(g_int_hash, g_int_equal, free, (GDestroyNotify)freeUser);

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
void insertUser(GHashTable* table, User* user,int id)
{
    int* key = malloc(sizeof(int));  // Aloca memória para a chave
    *key = id;
    g_hash_table_insert(table,key, user);

}

// Inserir os géneros das músicas no array usersByAge
Age* insertGeneros(Age* usersByAge, int idade,int* liked_songs_id,int SongCount, MusicData* musicController)
{

   for(int i=0;i<SongCount;i++)
    {
        char* genero = getMusicGenreControl(&liked_songs_id[i],musicController,'i');
        usersByAge= insertGenero(usersByAge,idade,genero);
        free(genero);
    }

     return usersByAge;    
}





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
    UData->usersMatrizQ5 = createQ5Struct(musicData);
     //Inicia o Parser e abre o ficheiro "users.csv" do dataset
    Parser* parserE= newParser(diretoria,"users.csv");

    // Ignorar a primeira linha
    char* line = pegaLinha(parserE);
    //Enviar a linha para o ficheiro users_erros.csv, esta não será inserida hashTable
    outputErros(Erros,line);
    free(line);
    int posicaoChegada = 0;
    while (1) {

        parserE= parser(parserE); 
        char** tokens= getTokens(parserE); 
        
        if (tokens==NULL){
        // Fecha o ficheiro guardado no Parser e liberta a memória alocada neste
        freeParser(parserE); break;

        }
    
        // Linha do input para validação, esta será enviada para o output de erros caso não seja válida
        char* linhaE=getLineError(parserE);
        int numSongs=calculate_num_members(tokens[7]);
        int isValid = validaUser(tokens[1],tokens[4],tokens[6],musicData,tokens[7],numSongs,Erros,linhaE);

        if(isValid){  
            
            int idade= calcular_idade(tokens[4]); 
            int* liked_songs_id = divideArray(tokens[7],numSongs);

            //  Inserir os Géneros das Liked Songs no array usersByAge
            UData->usersByAge= insertGeneros(UData->usersByAge,idade,liked_songs_id,numSongs, musicData);
            // Criar o User e inseri-lo na Hash Table
            User* user= newUser(tokens,posicaoChegada);
            insertUser(UData->usersTable,user,transformaIds(tokens[0])); 
            freeArray(liked_songs_id);

            inserirUserQ5(tokens[0],UData->usersMatrizQ5);  
            criaLinhaPreferencia(posicaoChegada,UData->usersMatrizQ5);
            posicaoChegada++;     
        }
        free(linhaE);
        free(getLine(parserE));
    }
    // Liberta a memória alocada pelo Output Erros e fecha o ficheiro dos erros
    freeOutput(Erros);
    return UData;
}



// Procurar um user na hash Table
User* fetchUser(UsersData* controlador, int username) {

    return  g_hash_table_lookup(controlador->usersTable, &username);

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
    freeQ5struct(data->usersMatrizQ5);
    printf("Tabela dos users destruida\n");

}


// Procura o género no array usersByAge de uma dada idade na posição i
char* getUBAGenero(UsersData * userController,int idade,int i) {

    char* genero= getGenero(userController->usersByAge,idade,i);
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



void atualizaPrefsUser(char* generoMusica, char* username, UsersData* userController){

    User* user = fetchUser(userController,transformaIds(username));

    atualizaGeneros(generoMusica,userController->usersMatrizQ5,user);
    
}



int** getElementosMatrizQ5(UsersData* userController){
    
    return getPreferenciasQ5(userController->usersMatrizQ5);//Manda copia da estrutura da Q5
}


char** getLinhasMatrizQ5(UsersData* userController){

    return getUsersId(userController->usersMatrizQ5);//Manda copia da estrutura da Q5
}

char** getColunasMatrizQ5(UsersData* userController){
     
    return getGenerosNomes(userController->usersMatrizQ5);//Manda copia da estrutura da Q5
}


int getNumLinhas(UsersData* userController){
    int numLinhas = getnumUsers(userController->usersMatrizQ5);

    return numLinhas;
}

int getNumColunas(UsersData* userController){
    int numColunas = getnumGeneros(userController->usersMatrizQ5);

    return numColunas;
}


int getPosicaoUser(UsersData* userController,char* username){
    User* user = fetchUser(userController,transformaIds(username));
    if(user == NULL) return -1;
    int posicao = getPosicaoChegada(user);
    return posicao;
}



// Retorna a data de nascimento
 char* getUserBirthDateControl(UsersData* controlador, int username) {
    User* user = fetchUser(controlador,username);
    return getUserBirthDate(user);
}

// Retorna o email
 char* getUserEmailControl(UsersData* controlador, int username) {
    User* user = fetchUser(controlador,username);
    return getUserEmail(user);
}

// Retorna o nome
 char* getUserNomeControl(UsersData* controlador, int username) {
    User* user = fetchUser(controlador,username);
    return getUserNome(user);
}

// Retorna o apelido
 char* getUserApelidoControl(UsersData* controlador, int username) {
    User* user = fetchUser(controlador,username);
    return getUserApelido(user);
}

// Retorna o país
 char* getUserCountryControl(UsersData* controlador, int username) {
    User* user = fetchUser(controlador,username);
    return getUserCountry(user);
}

// Retorna o SubscryptionType
 char* getUserSubscryptionTypeControl(UsersData* controlador, int username) {
    User* user = fetchUser(controlador,username);
    return getUserSubscryptionType(user);
}


int isUserValid(UsersData* controlador, int userName){
    User* user = fetchUser(controlador,userName);
    if(user == NULL) return 1;
    return 0;
}