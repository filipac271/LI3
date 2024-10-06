#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glib.h>
#include <unistd.h>
#include "artistsController.h"

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
    char* group_copy = strdup(&group[3]);
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
        result_array[j] = strdup(artistas_array[j]);
    }

    // Adiciona um NULL no final para marcar o fim do array
    result_array[numMembros] = NULL;

    // Libera a memória temporária
    free(group_copy);

    return result_array;
}









GHashTable* parser_artists(FILE *file) {
    char* line = NULL;  // Ponteiro para a linha, alocado dinamicamente pelo getline
    size_t len = 0;     // Tamanho do buffer usado pelo getline

    char* tokens[TOKEN_SIZE];

    GHashTable* artists_table = init_artists_table();

    // Skip da primeira linha explicativa do ficheiro
    getline(&line, &len, file);

    while (getline(&line, &len, file) != -1) {
        // Remove a nova linha no final, se existir
        if (line[strlen(line) - 1] == '\n') {
            line[strlen(line) - 1] = '\0';
        }

        char* lineCopy = line;  // Usar o ponteiro da linha original
        int i = 0;

        // Divide a linha em tokens usando strsep
        char* token = strsep(&lineCopy, ";");  // Dá o primeiro valor a token para poder entrar no loop
        while (token != NULL && i < TOKEN_SIZE) {
            tokens[i++] = token;  // Armazenar o token no array
            token = strsep(&lineCopy, ";");  // Pegar o próximo token
        }

        // Aqui os tokens devem corresponder à ordem dos dados no arquivo
        char* id = tokens[0];
        char* name = tokens[1];
        char* description = tokens[2];
        float ganho = atof(tokens[3]);  // Conversão de string para float
        char* grupo = tokens[4];  // Aqui, o grupo pode ser gerenciado como necessário
        char* country = tokens[5];
        char* type = tokens[6];

        int numMembros=1;
        
        // printf("%s\n\n\n",grupo);
        // sleep(1);

        // Conta o numero de liked songs do user
        for (int i = 2; grupo[i]!='\0'; i++) {
            
        if (grupo[i] == ',') numMembros++;

        }
        


        char** grupos_id = divideGroup(grupo,numMembros);

        // Inserir os dados na hash table
        insert_artist_into_table(artists_table, id, name, description, ganho, grupos_id, country, type,numMembros);
        
        
       
    


    }  
    
    // Verificar se o artista foi inserido corretamente
    //ArtistsData* looked = lookup_artist(artists_table,"\"A0000143\"");
    //print_artist(looked);

    //Como imprimir todos os artistas
    //print_all_artists(artists_table);

    // Libera a memória alocada por getline
    free(line);
    
    // Destruir a hash table após o uso
    //g_hash_table_destroy(artists_table);
    return artists_table;
}
