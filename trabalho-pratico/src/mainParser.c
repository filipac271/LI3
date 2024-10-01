#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINE_SIZE 1024 * 16
#define TOKEN_SIZE 20


void parser(FILE *file) {
    char* line = NULL;  // Ponteiro para a linha, alocado dinamicamente pelo getline
    size_t len = 0;     // Tamanho do buffer usado pelo getline

    char* tokens[TOKEN_SIZE];

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

        // Imprimir os tokens
        for (int j = 0; j < i; j++) {
            printf("Token %d: %s\n", j, tokens[j]);
        }
    }

    // Libera a memória alocada por getline
    free(line);
}
