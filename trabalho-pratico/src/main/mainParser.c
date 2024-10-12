#include "parser/artistsParser.h"
#include "parser/parsermusica.h"
#include "parser/userParser.h"

#include <stdio.h>
#include <stdlib.h>
#include <glib.h>


GHashTable** parser(FILE** ficheiros) {
    // Aloca um array para três ponteiros de GHashTable
    GHashTable** hash_tables = malloc(3 * sizeof(GHashTable*));

    // Inicializa as posições do array com NULL
    hash_tables[0] = NULL;
    hash_tables[1] = NULL;
    hash_tables[2] = NULL;

    for (int i = 0; i < 3; i++) {
        // Verifica se o ficheiro foi aberto corretamente
        if (ficheiros[i] == NULL) {
            printf("Erro: Ficheiro %d não foi aberto corretamente.\n", i);
            continue;  // Ignora este ficheiro e passa para o próximo
        }

        switch (i) {
            case 0:
                hash_tables[0] = parser_artists(ficheiros[0]);  // Armazena a tabela de artistas
                break;

            case 1:
                hash_tables[1] = parser_musica(ficheiros[1],hash_tables[0]);   // Armazena a tabela de músicas
                break;

            case 2:
                hash_tables[2] = userParser(ficheiros[2],hash_tables[1]);      // Armazena a tabela de users
                break;

            default:
                break;
        }
    }

    return hash_tables;  // Retorna o array de tabelas de hash
}
