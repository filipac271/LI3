#include "parser/parsermusica.h"
#include "controler/musicsController.h"
#include "utilidades.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glib.h>
#include <unistd.h>



#define TOKEN_SIZE 10

char** divideArtists(char* music_artist) {
    //tamanho da string original
    int len = strlen(music_artist);
    
    //se a sting nao tiver len > 2 ou se nao tiver entre [] nao funciona 
    if (len < 2 || music_artist[0] != '[' || music_artist[len - 1] != ']') {
        printf(stderr, "Formato inválido da string.\n");
        return NULL;
    }

    // tira os [ ] e o \0
    // [ 'aooooo', 'a00000' ]\0
    char* artistId_copy = &music_artist[2];
    int copy_len = strlen(artistId_copy);

    artistId_copy[copy_len-1] = NULL;
    artistId_copy[copy_len-2] = '\0';


    
    // if (artistId_copy == NULL) {
    //     printf("g_strndup falhou");
    //     g_free(artistId_copy);
    //     return NULL;
    // }

    int numMembros = contar_elementos(artistId_copy);
    

    //aloca espaço para os membros mais um para o \0
    char** result_array = malloc((numMembros + 1) * sizeof(char*));
    if (result_array == NULL) {
        printf("malloc falhou");
        g_free(artistId_copy);
        free(result_array);
        return NULL;
    }

    int i = 0;
    char* artist;
    //artist para a ser igual à string até a virgula
    while ((artist = strsep(&artistId_copy, ",")) != NULL && i < numMembros) {
        while (*artist == ' ' || *artist == '\'') artist++;
        int artist_len = strlen(artist);
        while (artist_len > 0 && (artist[artist_len - 1] == '\'' || artist[artist_len - 1] == ' ')) {
            artist[--artist_len] = '\0';
        }

        result_array[i] = (artist);
        if (result_array[i] == NULL) {
            printf("strdup falhou");
            for (int j = 0; j < i; j++) {
                g_free(result_array[j]);
            }
            free(result_array);
            g_free(artistId_copy);
            g_free(artist);

            return NULL;
        }
        i++;
    }

    result_array[i] = NULL; // Finalizar o array com NULL
    g_free(artistId_copy); 
    g_free(artist);
    return result_array;
}




GHashTable* parser_musica(FILE *file) {
    char* line = NULL;  // Ponteiro para a linha, alocado dinamicamente pelo getline
    size_t len = 0;     // Tamanho do buffer usado pelo getline

    char* tokens[TOKEN_SIZE];

    GHashTable* hash_musica = iniciar_hash_musica();

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

        // Aqui os tokens devem corresponder à ordem dos dados no arquivo
        char *music_id = remove_quotes(tokens[0]);
        char *music_title = remove_quotes(tokens[1]);
        char *music_artists = remove_quotes(tokens[2]);
        char *music_duration = remove_quotes(tokens[3]);
        char *music_genre = remove_quotes(tokens[4]);
        char *music_year = remove_quotes(tokens[5]);
        char *music_lyrics = remove_quotes(tokens[6]);

        int num_artistId = contar_elementos(music_artists);
      //  printf("%d\n", num_artistId);
       // printf("%s\n", music_artists);
       // printf("%d\n", num_artistId);

        char** music_artist_id = divideArtists(music_artists);
        if (music_artist_id == NULL && num_artistId > 0) {
                         //   printf("%d\n", num_artistId);

            fprintf(stderr, "Falha ao dividir artistas para music_id: %s\n", music_id);
            // Decida como proceder: pular a inserção, definir artistas como NULL, etc.
            // Aqui, vamos pular a inserção
            free(lineCopy);
            freeCleanerMusics(music_id, music_title, music_artists, music_duration, music_genre, music_year, music_lyrics);
            int k;
            for(k= 0;i < num_artistId; k++){
            free(music_artist_id[k]);
            }
            free(music_artist_id);
            continue;
        }

        // Inserir os dados na hash table
        inserir_musica_na_htable(hash_musica, music_id, music_title, music_artist_id, music_duration, music_genre, music_year, music_lyrics, num_artistId);
        //printf("Número de artistas após: %d\n", num_artistId);

        int j;

        for(j = 0;i < num_artistId; j++){
            free(music_artist_id[j]);
        }
        free(music_artist_id);

        freeCleanerMusics(music_id,music_title,music_artists,music_duration,music_genre,music_year,music_lyrics);

    }  
    // MusicData* looked = lookup_musica(hash_musica,"S0040231");
    // print_musicas(looked);
    //Como imprimir todos os artistas
   //print_all_musics(hash_musica);
    
    // Libera a memória alocada por getline
    free(line);
    return hash_musica;
}