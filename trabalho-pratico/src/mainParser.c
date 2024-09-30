#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINE_SIZE 1024 * 16
#define TOKEN_SIZE 20

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINE_SIZE 1024 * 16
#define TOKEN_SIZE 20

void parser(FILE *file) {
    char first_line[LINE_SIZE];
    char lines[LINE_SIZE];
    char* tokens[TOKEN_SIZE];

    // Skip da primeira linha explicativa do ficheiro
    fgets(first_line, LINE_SIZE, file);

    while (fgets(lines, LINE_SIZE, file) != NULL) {
        // Remove a nova linha no final, se existir
        int len = strlen(lines);
        if (len > 0 && lines[len - 1] == '\n') {
            lines[len - 1] = '\0';
        }

        // Como o strsep modifica as strings que dá parse (substituindo o delimitador por \0) 
        // É essencial usar uma "cópia" da string principal (lines) lineCopy

        char* lineCopy = lines; 
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
}
