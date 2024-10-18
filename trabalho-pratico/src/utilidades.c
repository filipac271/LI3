
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <glib.h>
#include <unistd.h>
#include <ctype.h>

#include "utilidades.h"

#define TOKEN_SIZE 8

struct ageUsers
{
    char** likedSongs;
    int numberSongs;
};


// Função para remover aspas de uma string
char* remove_quotes(const char* str) {
    size_t len = strlen(str);

    // Verifica se a string tem pelo menos 2 caracteres (as aspas)
    if (len < 2 || str[0] != '"' || str[len - 1] != '"') {
        // Se não tiver aspas, retorna uma cópia da string original
        return strdup(str);
    }

    // Aloca memória para a nova string (tamanho original - 2 para as aspas)
    char* new_str = (char*)malloc((len - 1) * sizeof(char));

    // Copia os caracteres da string original, excluindo as aspas
    strncpy(new_str, str + 1, len - 2);
    

    // Adiciona o terminador nulo ao final da nova string
    new_str[len - 2] = '\0';

    return new_str;
}



void freeCleanerArtist(char* clean_id,char* clean_name,char* clean_description,char* ganhos, char* clean_country,char* clean_type){

        free(clean_id);
        free(clean_name);
        free(clean_description);
        free(ganhos);
        free(clean_country);
        free(clean_type);
}



void freeCleanerMusics(char* music_id,char* music_title,char* music_artist_id,char* music_duration,char* music_genre,char* music_year,char* music_lyrics){

        free(music_id);
        free(music_title);
        free(music_artist_id);
        free(music_duration);
        free(music_genre);
        free(music_year);
        free(music_lyrics);

}


void freeCleanerUsers(char* username,char* email,char* nome ,char*  apelido,char* birth_date,char*  country,char* subscription_type){
        free(username);
        free(email);
        free(nome);
        free(apelido);
        free(birth_date);
        free(country);
        free(subscription_type);


}


int validaData(char* date) {
    int year, month, day;

    // Verifica o tamanho esperado da string (aaaa/mm/dd = 10 caracteres)
    if (strlen(date) != 10) {
        return 0;
    }

    // Verifica o formato: os caracteres nas posições 4 e 7 devem ser '/'
    if (date[4] != '/' || date[7] != '/') {
        return 0;
    }

    // Usa sscanf para extrair ano, mês e dia da string
    if (sscanf(date, "%d/%d/%d", &year, &month, &day) != 3) {
        return 0;
    }

    // Verifica os valores de ano, mês e dia
    if (year < 0 || month < 1 || month > 12 || day < 1 || day > 31) {
        return 0;
    }

    // Verifica se a data é mais recente que 2024/09/09
    if (year > 2024 || (year == 2024 && month > 9) || (year == 2024 && month == 9 && day > 9)) {
        return 0;
    }

    return 1;
}



int validaEmail(char* email) {
    int i = 0, j = 0, k = 0;

    // Verificar o username (antes do '@')
    for (i = 0; email[i] != '@'; i++) {
        if (!(islower(email[i]) || isdigit(email[i]))) {
            return 0;  // O username contém caracteres inválidos
        }
    }

    // Verificar se há pelo menos um caractere no username
    if (i == 0) {
        return 0;  // O username não pode ser vazio
    }

    i++;  // Saltar o '@'

    // Verificar o lstring (antes do '.')
    for (j = 0; email[i] != '.'; i++, j++) {
        if (!(islower(email[i]))) {
            return 0;  // lstring contém caracteres inválidos
        }
    }

    // Verificar se o lstring tem pelo menos 1 caractere
    if (j == 0) {
        return 0;  // lstring não pode ser vazio
    }

    i++;  // Saltar o '.'

    // Verificar o rstring (após o '.')
    for (k = 0; email[i] != '\0'; i++, k++) {
        if (!(islower(email[i]))) {
            return 0;  // rstring contém caracteres inválidos
        }
    }

    // Verificar se o rstring tem 2 ou 3 caracteres
    if (k != 2 && k != 3) {
        return 0;  // rstring deve ter 2 ou 3 caracteres
    }

    return 1;  // O e-mail é válido
}



int validaDuraçao (char* duracao){
        int hh, mm, ss;

    // Verificar se a duração tem exatamente 8 caracteres (no formato hh:mm:ss)
    if (strlen(duracao) != 8) {
        return 0;  // Formato inválido
    }

    // Verificar se os separadores são ':'
    if (duracao[2] != ':' || duracao[5] != ':') {
        return 0;  // Separadores inválidos
    }

    // Usar sscanf para extrair horas, minutos e segundos no formato esperado
    if (sscanf(duracao, "%2d:%2d:%2d", &hh, &mm, &ss) != 3) {
        return 0;  // Formato inválido
    }

    // Verificar se as horas estão entre 0 e 99
    if (hh < 0 || hh > 99) {
        return 0;  // Horas inválidas
    }

    // Verificar se os minutos estão entre 0 e 59
    if (mm < 0 || mm > 59) {
        return 0;  // Minutos inválidos
    }

    // Verificar se os segundos estão entre 0 e 59
    if (ss < 0 || ss > 59) {
        return 0;  // Segundos inválidos
    }

    return 1;  // Duração válida
}




char* pegaLinha(FILE* ficheiro, size_t* len, char** line) {
    ssize_t linhaParsed = getline(line, len, ficheiro);
    if (linhaParsed == -1) {
        // getline retorna -1 em caso de erro ou fim de arquivo
        return NULL;
    }
    return *line;
}


void parser(char* linha, char* tokens[]) {
    char* lineCopy = linha;
    int i = 0;

    // Divide a linha em tokens usando strsep
    char* token = strsep(&lineCopy, ";");
    while (token != NULL && i < TOKEN_SIZE) {
        tokens[i++] = token;  // Armazenar o token no array
        token = strsep(&lineCopy, ";");
    }
}


char** divideGroup(char* group, int numMembros)
{
    // Verificar se a string é vazia ("[]")
    if (strcmp(group, "\"[]\"") == 0) {
        // Alocar um array vazio
        char** result_array = malloc(sizeof(char*));
        result_array[0] = NULL;  // Marcar o fim do array
        return result_array;
    }


    // Retira os primeiros elementos, por exemplo: "['
    char* group_copy = &group[3];
    char* artistas_array[numMembros];
    int i = 0;

    // Obter o primeiro elemento separado por aspas simples
    char* membro = strsep(&group_copy, "\'");

    // Dividir os itens do grupo
    while (membro != NULL && i < numMembros) {
        artistas_array[i++] = membro;  // Armazena o token no array
        membro = strsep(&group_copy, "\''");  // Salta a vírgula e o espaço
        membro = strsep(&group_copy, "\''");  // Pega o próximo membro entre aspas
    }

    // Aloca o array de strings
    char** result_array = malloc((numMembros + 1) * sizeof(char*));

    // Copia os itens do array temporário para o array final
    for (int j = 0; j < numMembros; j++) {
        result_array[j] = artistas_array[j];
    }

    // Adiciona um NULL no final para marcar o fim do array
    result_array[numMembros] = NULL;
   
    // Libera a memória temporária
    free(group_copy);

    
    return result_array;
}


// Função para contar o número de membros
int contar_elementos(char *str) {
    int count = 0;
    char *p = str;
    while (*p) {
        if (*p == ',') count++;
        p++;
    }
    return count + 1;
}

char** divideArtists(char* music_artist) {

    // tira os [ ] e o \0
    // [ 'aooooo', 'a00000' ]\0
    char* artistId_copy = &music_artist[2];
    int copy_len = strlen(artistId_copy);

    int numMembros = contar_elementos(artistId_copy);


    //aloca espaço para os membros mais um para o \0
    char** result_array = malloc((numMembros + 1) * sizeof(char*));

    if (result_array == NULL) {
        printf("malloc falhou");
        g_free(artistId_copy);
        free(result_array);
        return NULL;
    }
    if(music_artist[0] == 'A'){
        result_array[0] = music_artist;

        return result_array;
    }
    /*
    //se a sting nao tiver len > 2 ou se nao tiver entre [] nao funciona 
    if (len < 2 || music_artist[0] != '[' || music_artist[len - 1] != ']') {
        printf( "Formato inválido da string:%s\n",music_artist);
        
    }*/

    artistId_copy[copy_len-1] = NULL;
    artistId_copy[copy_len-2] = '\0';

    int i = 0;
    char* artist;
    //artist para a ser igual à string até a virgula
    while ((artist = strsep(&artistId_copy, ",")) != NULL && i < numMembros) {
        while (*artist == ' ' || *artist == '\'') artist++;
        int artist_len = strlen(artist);
        while (artist_len > 0 && (artist[artist_len - 1] == '\'' || artist[artist_len - 1] == ' ')) {
            artist[--artist_len] = '\0';
        }

        result_array[i] = (artist);
        if (result_array[i] == NULL) {
            printf("strdup falhou");
            for (int j = 0; j < i; j++) {
                g_free(result_array[j]);
            }
            free(result_array);
            g_free(artistId_copy);
            g_free(artist);

            return NULL;
        }
        i++;
    }

    result_array[i] = NULL; // Finalizar o array com NULL
    g_free(artistId_copy); 
    g_free(artist);
    return result_array;
}


// Adiciona as cancoes à idade certa
Age* addLikedSongs( Age* songsByAge, int idade,char** newSongs,int newSongCount)  {
   
    
    if (songsByAge[idade].numberSongs == 0) {
       
    songsByAge[idade].likedSongs=(char**)malloc(newSongCount * sizeof(char*));
       for (int j = 0; j < newSongCount; j++) {
            songsByAge[idade].likedSongs[j] = strdup(newSongs[j]);  // Copy the song strings
        }
        songsByAge[idade].numberSongs = newSongCount;
    } else {
        // Quando já há cancoes
        int oldSongCount = songsByAge[idade].numberSongs;
        int totalSongs = oldSongCount + newSongCount;
          
        songsByAge[idade].likedSongs = (char**)realloc(songsByAge[idade].likedSongs, totalSongs * sizeof(char*));

        for (int j = 0; j < newSongCount; j++) {
            songsByAge[idade].likedSongs[oldSongCount + j] = strdup(newSongs[j]);
        }
        songsByAge[idade].numberSongs = totalSongs; // Update the song count
    }
   // free(newSongs);
  return songsByAge;
    
}

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
liked_songs_id[numberS] = NULL;
    // Liberta a memória alocada para uma string auxiliar do processo
  //  free(song_copy);  


    return liked_songs_id;
}
