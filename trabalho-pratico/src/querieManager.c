#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <glib.h>
#include <querie1.h>


void queries (GHashTable** tables, FILE* querieFile){




char* line = NULL;  // Ponteiro para a linha, alocado dinamicamente pelo getline
size_t len = 0;     // Tamanho do buffer usado pelo getline





for (int i = 0; getline(&line, &len, querieFile) != -1;i++) {
        // Remove a nova linha no final, se existir
        if (line[strlen(line) - 1] == '\n') {
            line[strlen(line) - 1] = '\0';
        }

    


    switch (line[0])
    {
    case '1':
    //line +2 para ignorar o tipo de querie e o espaço
      querie1(tables[2],line+2);
      break;
    
    case '2':


      break;

    case '3':
      

      break;
    
    default:
      break;
    }




}    
 // Libera a memória alocada por getline
    free(line);


}