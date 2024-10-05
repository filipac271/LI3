#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <glib.h>


void queries (GHashTable** tables, FILE* querieFile){




char* line = NULL;  // Ponteiro para a linha, alocado dinamicamente pelo getline
size_t len = 0;     // Tamanho do buffer usado pelo getline



// Skip da primeira linha explicativa do ficheiro
getline(&line, &len, querieFile);


for (int i = 0; getline(&line, &len, querieFile) != -1;i++) {
        // Remove a nova linha no final, se existir
        if (line[strlen(line) - 1] == '\n') {
            line[strlen(line) - 1] = '\0';
        }



    switch (line[0])
    {
    case '1':
    
      break;
    
    case '2':


      break;

    case '3':

      break;
    
    default:
      break;
    }




}    



}