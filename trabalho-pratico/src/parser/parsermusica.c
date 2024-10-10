#include "parser/parsermusica.h"
#include "controler/musicsController.h"
#include "utilidades.h"
#include "validacao/validaMusic.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glib.h>
#include <unistd.h>



#define TOKEN_SIZE 10

GHashTable* parser_musica(FILE *file) {



    char *filename = malloc(sizeof(char) * 256);
    sprintf(filename, "resultados/musics_errors.csv");
    FILE *errosFileMusics = fopen(filename, "w");

    free(filename);


    char* line = NULL;  // Ponteiro para a linha, alocado dinamicamente pelo getline
    size_t len = 0;     // Tamanho do buffer usado pelo getline

    char* tokens[TOKEN_SIZE];

    GHashTable* hash_musica = iniciar_hash_musica();

    // Skip da primeira linha explicativa do ficheiro
    getline(&line, &len, file);

    fprintf(errosFileMusics,"%s",line);


    while (getline(&line, &len, file) != -1) {
        // Remove a nova linha no final, se existir
        if (line[strlen(line) - 1] == '\n') {
            line[strlen(line) - 1] = '\0';
        }

        char* lineCopy = line;  // Usar o ponteiro da linha original

        // Cria um buffer local para armazenar uma cópia da linha
        char lineOutput[2048];
        strncpy(lineOutput, line, 2048);  // Copia a linha para o buffer local
        lineOutput[2048 - 1] = '\0'; // Garante a terminação da string

        int i = 0;

        // Divide a linha em tokens usando strsep
        char* token = strsep(&lineCopy, ";");  // Dá o primeiro valor a token para poder entrar no loop
        while (token != NULL && i < TOKEN_SIZE) {
            tokens[i++] = token;  // Armazenar o token no array
            token = strsep(&lineCopy, ";");  // Pegar o próximo token
        }

        // Aqui os tokens devem corresponder à ordem dos dados no arquivo
        char *music_id = remove_quotes(tokens[0]);
        char *music_title = remove_quotes(tokens[1]);
        char *music_artist_id = remove_quotes(tokens[2]);
        char *music_duration = remove_quotes(tokens[3]);
        char *music_genre = remove_quotes(tokens[4]);
        char *music_year = remove_quotes(tokens[5]);
        char *music_lyrics = remove_quotes(tokens[6]);

        int isValid = validaMusic(music_duration);
        if(isValid){
            // Inserir os dados na hash table
        inserir_musica_na_htable(hash_musica, music_id, music_title, music_artist_id, music_duration, music_genre, music_year, music_lyrics);





        }else{
            fprintf(errosFileMusics,"%s\n",lineOutput);
        }

        freeCleanerMusics(music_id,music_title,music_artist_id,music_duration,music_genre,music_year,music_lyrics);

    }  
    
    // Verificar se o artista foi inserido corretamente
    //falar para depois fazer uma geral desta
    // MusicData* looked = lookup_musica(hash_musica,"S0040231");
    // print_musicas(looked);


    //Como imprimir todos os artistas
    //print_musics(hash_musica);
    
    fclose (errosFileMusics);
    // Libera a memória alocada por getline
    free(line);

    

    return hash_musica;
}


