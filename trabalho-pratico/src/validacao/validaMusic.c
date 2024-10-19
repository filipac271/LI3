#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <glib.h>

#include "utilidades.h"

int validaMusic(char* duracao, char** artistsId, GHashTable* artistsTable,int numArtistsId) {
    int d;
    int pertence = 1;  // Assumir que todos os artistas pertencem

    d = validaDuraçao(duracao);

    for (int i = 0; i < numArtistsId; i++) {
    if (artistsId[i] == NULL) {
        printf("Erro: artistsId[%d] é NULL\n", i);
        pertence = 0;
        break;
    }



    if (g_hash_table_lookup(artistsTable, artistsId[i]) == NULL) {
        //printf("Artista %s não encontrado na hash table\n", artistsId[i]);
        pertence = 0;
        break;
    }
}


    return (d & pertence);  // Combinação bitwise dos resultados de duração e artistas
}
