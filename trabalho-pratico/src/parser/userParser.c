#include "controler/usersController.h"
#include "parser/userParser.h"
#include "utilidades.h"
#include "validacao/validaUser.h"


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glib.h>
#include <unistd.h>



#define TOKEN_SIZE 8



//dividir a string das liked_songs_id num arrays de stings (cada string um id)
char** likedSongs(char* songs, int numberS)
{
    // Retira os primeiros elementos : "[' 
    char* song_copy = &songs[3];
    char* likedSong[numberS];
    int i = 0;
    
    char* likedSongs = strsep(&song_copy, "\'");  

    //Divide as liked songs 
    while (likedSongs != NULL && i < numberS) {
        likedSong[i++] = likedSongs;  // Armazenar o token no array
        likedSongs = strsep(&song_copy, "\'");  
        likedSongs = strsep(&song_copy, "\'"); 
    }

    // Alocação do array de strings liked_songs_id
    char** liked_songs_id = malloc((numberS+1 ) * sizeof(char*));
   
    //Passa para o array de strings as cancoes ja divididas
    for (int s = 0; s < numberS; s++) {
        liked_songs_id[s] = likedSong[s];  // Duplicar cada ID
   
    }

    // Liberta a memória alocada para uma string auxiliar do processo
    free(song_copy);  


    return liked_songs_id;
}


GHashTable* userParser(FILE *file,GHashTable* musicsTable) {


    char *filename = malloc(sizeof(char) * 256);
    sprintf(filename, "resultados/users_errors.csv");
    FILE *errosFileUser = fopen(filename, "w");

    free(filename);
  

    char* line = NULL;  // Ponteiro para a linha, alocado dinamicamente pelo getline
    size_t len = 0;     // Tamanho do buffer usado pelo getline

    char* tokens[TOKEN_SIZE];
   
    GHashTable* userTable = createTable();

    // Skip da primeira linha explicativa do ficheiro
    getline(&line, &len, file);

    fprintf(errosFileUser,"%s",line);

    while (getline(&line, &len, file) != -1) {
        // Remove a nova linha no final, se existir
        if (line[strlen(line) - 1] == '\n') {
            line[strlen(line) - 1] = '\0';
        }

        char* lineCopy = line;  // Usar o ponteiro da linha original
        // Cria um buffer local para armazenar uma cópia da linha
        char lineOutput[1024];
        strncpy(lineOutput, line, 1024);  // Copia a linha para o buffer local
        lineOutput[1024 - 1] = '\0'; // Garante a terminação da string
        int i = 0;
        int nM=1;
        // Divide a linha em tokens 
        char* token = strsep(&lineCopy, ";");  
        while (token != NULL && i < TOKEN_SIZE) {
            tokens[i++] = token;  
            token = strsep(&lineCopy, ";");  
        }

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
            if (songs[i] == ',') nM++;
        }

 
        char** liked_songs_id =likedSongs(songs,nM);

        int isValid = validaUser(email,birth_date,subscription_type,musicsTable,liked_songs_id,nM);

        if(isValid){
          
        
  

        // Inserir os dados na hash table
        User* user= newUser(username, email ,nome , apelido,birth_date, country,subscription_type,liked_songs_id,nM);
        insertUser(userTable,user);
        }else{
            fprintf(errosFileUser,"%s\n",lineOutput);
        }


        free(liked_songs_id); 
        freeCleanerUsers(username,email,nome , apelido,birth_date, country,subscription_type);

        
    }  

    fclose(errosFileUser);
 
    // Liberta a memória alocada por getline
    free(line);

    


    return userTable;
 
}


