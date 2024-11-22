#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <glib.h>
#include <unistd.h>
#include <ctype.h>

#include "utilidades.h"
#include "controler/musicsController.h"



// Função para calcular a idade
int calcular_idade( char* data_nascimento_str) {
    // Data atual
    int ano_atual = 2024, mes_atual = 9, dia_atual = 9;

    // Variáveis para armazenar ano, mês e dia de nascimento
    int ano_nascimento, mes_nascimento, dia_nascimento;

    // Converter a string da data de nascimento para inteiros
    if(data_nascimento_str[0] == '\"'){

    sscanf(data_nascimento_str, "\"%d/%d/%d\"", &ano_nascimento, &mes_nascimento, &dia_nascimento);
    }else{
    sscanf(data_nascimento_str, "%d/%d/%d", &ano_nascimento, &mes_nascimento, &dia_nascimento);

    }


    // Calcular a idade base
    int idade = ano_atual - ano_nascimento;

    // Ajustar se o mês atual for anterior ao mês de nascimento,
    // ou se for o mesmo mês, mas o dia atual for anterior ao dia de nascimento
    if (mes_atual < mes_nascimento || (mes_atual == mes_nascimento && dia_atual < dia_nascimento)) {
        idade--;
    }
    return idade;
}


guint get_garray_length(GArray *array) {
    if (array == NULL) {
        return 0; // Retorna 0 se o GArray for NULL
    }
    return array->len; // Retorna o tamanho do GArray
}


char* seconds_to_hhmmss(int total_seconds) {
    // Aloca memória para a string de saída
    char *time_string = malloc(16); // hh:mm:ss + \0 = 9 caracteres
    if (time_string == NULL) {
        return NULL; // Verifica se a alocação foi bem-sucedida
    }

    // Calcula horas, minutos e segundos
    int hours = total_seconds / 3600;
    int minutes = (total_seconds % 3600) / 60;
    int seconds = total_seconds % 60;

    // Formata a string no formato hh:mm:ss
    //mudar aqui tambem para 16 caso se queira tirar os warning
    snprintf(time_string, 16, "%02d:%02d:%02d", hours, minutes, seconds);

    return time_string;
}


// Função para remover aspas de uma string
char* remove_quotes(char* str) {
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


int calculate_num_members(char* grupo) {

    if (strcmp(grupo, "\"[]\"") == 0) {
        return 0; // Nenhum membro no grupo
    }

    int numMembros = 1; // Pelo menos um membro
    for (int i = 2; grupo[i] != '\0'; i++) { // Começa no índice 2 para pular as aspas iniciais e o colchete
        if (grupo[i] == ',') {
            numMembros++;
        }
    }
    return numMembros;
}




int validaData(char* date) {
    int year, month, day;

    // Verifica o tamanho esperado da string (aaaa/mm/dd = 10 caracteres)
    if (strlen(date) != 12) {
        return 0;
    }

    // Verifica o formato: os caracteres nas posições 4 e 7 devem ser '/'
    if (date[5] != '/' || date[8] != '/') {
        return 0;
    }

    // Usa sscanf para extrair ano, mês e dia da string
    if (sscanf(date, "\"%d/%d/%d\"", &year, &month, &day) != 3) {
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



int validaEmail(char* emailAspas) {
    char* email = remove_quotes(emailAspas);
    int i = 0, j = 0, k = 0;

    // Verificar o username (antes do '@')
    for (i = 0; email[i] != '@'; i++) {
        if (!(islower(email[i]) || isdigit(email[i]))) {
            free(email);
            return 0;  // O username contém caracteres inválidos
        }
    }

    // Verificar se há pelo menos um caractere no username
    if (i == 0) {
        free(email);
        return 0;  // O username não pode ser vazio
    }

    i++;  // Saltar o '@'

    // Verificar o lstring (antes do '.')
    for (j = 0; email[i] != '.'; i++, j++) {
        if (!(islower(email[i]))) {
            free(email);
            return 0;  // lstring contém caracteres inválidos
        }
    }

    // Verificar se o lstring tem pelo menos 1 caractere
    if (j == 0) {
        free(email);
        return 0;  // lstring não pode ser vazio
    }

    i++;  // Saltar o '.'

    // Verificar o rstring (após o '.')
    for (k = 0; email[i] != '\0'; i++, k++) {
        if (!(islower(email[i]))) {
            free(email);
            return 0;  // rstring contém caracteres inválidos
        }
    }

    // Verificar se o rstring tem 2 ou 3 caracteres
    if (k != 2 && k != 3) {
        free(email);
        return 0;  // rstring deve ter 2 ou 3 caracteres
    }
    free(email);
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



int* divideGroup(char* group, int numMembros)
{
    // Verificar se a string é vazia ("[]")
    if (strcmp(group, "\"[]\"") == 0) {
        // Retornar um array vazio
        int* result_array = malloc(sizeof(int)); // Aloca espaço para um array vazio
        result_array[0] = -1;  // Indicador de array vazio
        return result_array;
    }

    // Avança o ponteiro para ignorar os primeiros caracteres: "['
    char* group_copy = &group[3];
    int* result_array = malloc(numMembros * sizeof(int));
    if (result_array == NULL) {
        fprintf(stderr, "Erro ao alocar memória para o array de inteiros\n");
        exit(1);
    }

    int i = 0;

    // Obter o primeiro elemento separado por aspas simples
    char* membro = strsep(&group_copy, "\'");

    // Dividir os itens do grupo
    while (membro != NULL && i < numMembros) {
        result_array[i++] = transformaIds(membro);  // Usa transformaIds para converter o token em inteiro
        membro = strsep(&group_copy, "\'");  // Salta a vírgula e o espaço
        membro = strsep(&group_copy, "\'");  // Pega o próximo membro entre aspas
    }

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
        // g_free(artistId_copy);
        free(result_array);
        return NULL;
    }
    if(music_artist[0] == 'A'){
        result_array[0] = music_artist;

        return result_array;
    }


    artistId_copy[copy_len-1] = '\0';

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
            // g_free(artistId_copy);
            // g_free(artist);

            return NULL;
        }
        i++;
    }

    result_array[i] = NULL; // Finalizar o array com NULL
    // g_free(artistId_copy); 
    // g_free(artist);
    return result_array;
}



//Funçao para dar free das copias do likedSongs
void freeArray(int* array) {
    if (array == NULL) return; // Proteção contra ponteiros nulos

    free(array); // Libera o array de ponteiros
}



//Função likedSongs que agora usa transformaIds
int* likedSongs(char* songs, int numberS) {
    // Copia a string original
    char* song_copy = strdup(songs);
    char* song_ptr = &song_copy[3]; // Ponteiro auxiliar para percorrer a string

    // Cria um array de inteiros para armazenar os ids
    int* likedSongIds = malloc(numberS * sizeof(int));
    if (likedSongIds == NULL) {
        fprintf(stderr, "Erro ao alocar memória para likedSongIds\n");
        free(song_copy);
        return NULL;
    }

    int i = 0;
    char* likedSong = strsep(&song_ptr, "\'");  // Divide a string original

    // Divide as liked songs e aplica transformaIds em cada ID
    while (likedSong != NULL && i < numberS) {
        likedSongIds[i++] = transformaIds(likedSong);  // Chama a função transformaIds
        likedSong = strsep(&song_ptr, "\'");
        likedSong = strsep(&song_ptr, "\'");
    }

    // Libera a memória alocada para a cópia da string original
    free(song_copy);

    return likedSongIds;
}




// Função para comparar linha a linha dois arquivos e contar ocorrências corretas
int compararFicheirosPorLinha(char *file1,char *file2, int *ocorrenciasCorretas) {
    FILE *f1 = fopen(file1, "r");
    FILE *f2 = fopen(file2, "r");

    if (f1 == NULL || f2 == NULL) {
        printf("Erro ao abrir um dos arquivos para comparação%s",file2);
        return -1;  // Erro ao abrir arquivos
    }


    char linha1[1024], linha2[1024];
    int linhaNumero = 1;
    *ocorrenciasCorretas = 0;

    while (fgets(linha1, sizeof(linha1), f1) && fgets(linha2, sizeof(linha2), f2)) {
        // Remover quebra de linha para evitar diferenças acidentais
        linha1[strcspn(linha1, "\n")] = '\0';
        linha2[strcspn(linha2, "\n")] = '\0';


        if (strcmp(linha1, linha2) == 0) {            
            (*ocorrenciasCorretas)++;  // Incrementa ocorrências corretas
        } else {
            printf("\nDiferença encontrada na linha %d do arquivo %s\n", linhaNumero, file1);
            fclose(f1);
            fclose(f2);
            return 0;  // Arquivo é diferente
        }
        linhaNumero++;
    }
    



    fclose(f1);
    fclose(f2);
    return 1;  // Arquivos são iguais
}

int transformaIds (char* idString){

    char* id = &idString[1];
    //int tamanho = strlen(id);
    //id[tamanho-1] = '\0';
    // printf("%s\n",id);
    // sleep(1);
    int idINT = atoi(id);
    //printf("%d\n",idINT);

    return idINT;
}