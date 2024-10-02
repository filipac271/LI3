#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glib.h>
#include <unistd.h>
#include "artistsController.h"

#define TOKEN_SIZE 10


void parser_artists(FILE *file) {
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
        char** grupo = NULL;  // Aqui, o grupo pode ser gerenciado como necessário
        char* country = tokens[4];
        char* type = tokens[5];

        // Inserir os dados na hash table
        insert_artist_into_table(artists_table, id, name, description, ganho, grupo, country, type);
        
    }  
    
    // Verificar se o artista foi inserido corretamente
    //ArtistsData* looked = lookup_artist(artists_table,"\"A0000143\"");
    //print_artist(looked);

    //Como imprimir todos os artistas
    //print_all_artists(artists_table);
    
    // Libera a memória alocada por getline
    free(line);
    
    // Destruir a hash table após o uso
    g_hash_table_destroy(artists_table);
}
