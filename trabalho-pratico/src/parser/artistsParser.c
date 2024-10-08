#include "controler/artistsController.h"
#include "parser/artistsParser.h"
#include "utilidades.h"


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glib.h>
#include <unistd.h>

#define TOKEN_SIZE 10



char** divideGroup(char* group, int numMembros)
{
    // Verificar se a string é vazia ("[]")
    if (strcmp(group, "\"[]\"") == 0) {
        // Alocar um array vazio
        char** result_array = malloc(sizeof(char*));
        result_array[0] = "-1";  // Marcar o fim do array
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




GHashTable* parser_artists(FILE *file) {
    char* line = NULL;
    size_t len = 0;
    char* tokens[TOKEN_SIZE];

    GHashTable* artists_table = init_artists_table();

    // Skip da primeira linha explicativa do ficheiro
    getline(&line, &len, file);

    

    while (getline(&line, &len, file) != -1) {
        // Remove a nova linha no final, se existir
        if (line[strlen(line) - 1] == '\n') {
            line[strlen(line) - 1] = '\0';
        }
        
        
        char* lineCopy = line;
        int i = 0;

        // Divide a linha em tokens usando strsep
        char* token = strsep(&lineCopy, ";");
        while (token != NULL && i < TOKEN_SIZE) {
            tokens[i++] = token;  // Armazenar o token no array
            token = strsep(&lineCopy, ";");
        }

        // Aqui os tokens devem corresponder à ordem dos dados no arquivo
        char* id = remove_quotes(tokens[0]);
        char* name = remove_quotes(tokens[1]);
        char* description = remove_quotes(tokens[2]);
        char* ganhos = remove_quotes(tokens[3]);
        float clean_ganhos = atof(ganhos);
        char* grupo = tokens[4];
        char* country = remove_quotes(tokens[5]);
        char* type = remove_quotes(tokens[6]);

        int numMembros = 1;
        if(strcmp(grupo ,"\"[]\"") == 0){
            numMembros = 0;
        }else{
                 // Conta o número de membros do grupo
        for (int i = 2; grupo[i] != '\0'; i++) {
            if (grupo[i] == ',') numMembros++;
        } 
        }
        
        char** grupos_id = divideGroup(grupo, numMembros);

        ArtistsData* newArtist = create_artist(id, name, description, clean_ganhos, grupos_id, country, type, numMembros);
        // Insere os dados na hash table
        insert_artist_into_table(artists_table, newArtist,id);

        // Libera as strings alocadas com remove_quotes
        freeCleanerArtist(id,name,description,ganhos,country,type);

        free(grupos_id);
    }

    // Libera a memória alocada por getline
    free(line);

    return artists_table;
}