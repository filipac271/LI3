#include "querie/querieManager.h"
#include "querie/querie1.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <glib.h>


void queries (GHashTable** tables, FILE* querieFile){
  if (querieFile == NULL) {
    printf("Erro ao abrir o arquivo!\n");
    return;
  }

  char* line = NULL;  // Ponteiro para a linha, alocado dinamicamente pelo getline
  size_t len = 0;     // Tamanho do buffer usado pelo getline

  for (int i = 0; getline(&line, &len, querieFile) != -1; i++) {
    printf("Entrou\n");

    // Verifica se a linha tem pelo menos 1 caractere
    if (strlen(line) == 0) continue;

    // Remove a nova linha no final, se existir
    if (line[strlen(line) - 1] == '\n') {
      line[strlen(line) - 1] = '\0';
    }

    switch (line[0]) {
      case '1':
        // Verifica se a linha tem pelo menos 3 caracteres
        if (strlen(line) >= 2) {
          querie1(tables[2], line + 2, i);
        }
        break;

      case '2':
        // Implementar querie 2
        break;

      case '3':
        // Implementar querie 3
        break;

      default:
        break;
    }
  }

  // Libera a memória alocada por getline
  free(line);
}
