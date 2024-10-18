#include "querie/querieManager.h"
#include "controler/usersController.h"
#include "controler/mainController.h"
#include "querie/querie1.h"
#include  "querie/querie3.h"
#include "utilidades.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <glib.h>

struct ageUsers
{
    char** likedSongs;
    int numberSongs;
};

void queries (MainController* data, FILE* querieFile){
  if (querieFile == NULL) {
    printf("Erro ao abrir o arquivo!\n");
    return;
  }
  

  char* line = NULL;  // Ponteiro para a linha, alocado dinamicamente pelo getline
  size_t len = 0;     // Tamanho do buffer usado pelo getline
  int min,max;
  for (int i = 0; getline(&line, &len, querieFile) != -1; i++) {

    // Verifica se a linha tem pelo menos 1 caractere
    if (strlen(line) == 0) continue;

    // Remove a nova linha no final, se existir
    if (line[strlen(line) - 1] == '\n') {
      line[strlen(line) - 1] = '\0';
    }
        UsersData* UserController = getUserController(data);
        GHashTable* table = getUserTable(UserController);
    switch (line[0]) {
      case '1':
        // Verifica se a linha tem pelo menos 3 caracteres
        if (strlen(line) >= 2) {

          querie1(table, line + 2, i);  

        }
        break;

      case '2':
     
        break;

      case '3':
         
        sscanf(line+1, "%d %d", &min, &max);
       //  printf("%d %d\n",min,max);
                
        //querie3(i,tables[1],min,max,userByAge);
        break;

      default:
        break;
    }
  }


/*
  for(int i=0; i<130;i++)
   {
      if(userByAge[i].likedSongs==NULL)
      {
        continue; 
      } 
      else{
        
      for (int j = 0; j < userByAge[i].numberSongs ; j++)
      {
        free(userByAge[i].likedSongs[j]);
      }
       free(userByAge[i].likedSongs);

         
      }
   }
*/

  // Libera a memória alocada por getline
  free(line);
}
