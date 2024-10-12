
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <glib.h>
#include <unistd.h>
#include <ctype.h>





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