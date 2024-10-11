#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <glib.h>

#include "utilidades.h"

int validaMusic(char* duracao,char** artistsId,GHashTable* artistsTable ) {

    int d;
    int pertence = 0;
    d = validaDuraçao(duracao);

    for (int i = 0;artistsId[i] != NULL; i++)
    {
        printf("%s\n",artistsId[i]);

       if(g_hash_table_lookup(artistsTable,artistsId[i]) == NULL) {
        pertence = 0;
        break;
        printf("QUASE SAIU\n");

       }else pertence = 1;



    }
    
    printf("%d\n",pertence);

    printf("SAIU\n");

    return (d & pertence);

}