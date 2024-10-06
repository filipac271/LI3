
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <glib.h>
#include <unistd.h>





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