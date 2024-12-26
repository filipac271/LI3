#include "Entitys/musics.h" 
#include "utilidades.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>


struct music{
  int music_id;
  char *music_title;
  int* music_artist_id;
  int albumId;
  char *music_duration;
  char *music_genre;
  char *music_year;
  //char *music_lyrics;
  int num_artistId;
};

 

Music* new_music(char** tokens){
  Music* n_music = malloc(sizeof(Music));
    if (n_music == NULL) {
        fprintf(stderr, "Memory allocation failed for new music\n");
        exit(1);
    } 
  
  //O remove quotes já manda uma cópia
  int num_artists = calculate_num_members(tokens[2]);
  int* music_artist_id = divideArray(tokens[2],num_artists);

  n_music->music_id =transformaIds(tokens[0]);

  n_music->music_title = remove_quotes(tokens[1]);
  n_music->music_artist_id = malloc((num_artists)* sizeof(int));
  for(int i = 0; i < num_artists; i++){
    n_music->music_artist_id[i] = music_artist_id[i];
  }
  
  n_music->albumId = transformaIds(tokens[3]);
  n_music->num_artistId = num_artists;
  n_music->music_duration = remove_quotes(tokens[4]);
  n_music->music_genre = remove_quotes(tokens[5]);
  n_music->music_year = remove_quotes(tokens[6]);
  //n_music->music_lyrics = remove_quotes(tokens[6]);

  freeArray(music_artist_id);
  
  return n_music;

}

void free_musica(Music* musica) {
    if (musica) {

        free(musica->music_title);
        free(musica->music_artist_id);

        free(musica->music_duration);
        free(musica->music_genre);
        free(musica->music_year);
        //free(musica->music_lyrics);

        free(musica);
    }
}

void print_musicas(Music * musica){
  if(musica){
    printf("ID_MUSIC: %d\n", musica->music_id);
    printf("MUSIC_TITLE: %s\n", musica->music_title);

    printf("MUSIC_ARTIST:\n");
    for(int i = 0; i < musica->num_artistId; i++){
      printf("%d\n", musica->music_artist_id[i]);
    }
    printf("MUSIC_ALBUM: %d\n",musica->albumId);
    printf("MUSIC_DURATION: %s\n", musica->music_duration);
    printf("MUSIC_GENRE: %s\n", musica->music_genre);
    printf("MUSIC_YEAR: %s\n", musica->music_year);
    printf("Numero de artistas: %d\n", musica->num_artistId);
    //printf("MUSIC_LYRICS: %s\n", musica->music_lyrics);

  } else{
    printf("N existe esta musica\n");
  }
}


//Getters

int get_music_id (Music* music){
  return (music->music_id);
}

char* get_music_title (Music* music){
  return strdup(music->music_title);
}

// char** get_music_artist_id (Music* music){
//   return music->music_artist_id;
// }

char* get_music_duration (Music* music){
  return strdup(music->music_duration);
}


int duration_to_seconds(char* music_duration) {
    int hours, minutes, seconds;

    sscanf(music_duration, "%d:%d:%d", &hours, &minutes, &seconds);

    return hours * 3600 + minutes * 60 + seconds;
}

//getter que dá a duraçao em segundos
int get_music_duration_seconds (Music* musica){
  return (duration_to_seconds(get_music_duration(musica)));
}

char* get_music_genre (Music* music){
  return strdup(music->music_genre);
}

char* get_music_year (Music* music){
  return strdup(music->music_year);
}

int get_numArtistsId (Music* music){
  return (music->num_artistId);
}


// int get_artistID_at_index(Music* song, int index) {
//     if (!song || index < 0 || index >= song->num_artistId) {
//         return -1; // Retorna um valor inválido se o índice for inválido
//     }
//     return song->music_artist_id[index];
// }

//É PRECISO DAR FREEEEEE
int* getArtistIDfromMuiscID(Music* music,int num_artists){


  //acho que funciona, mas caso não funcionar usar um malloc e depois dar free
    int* novoarray = malloc(num_artists * sizeof(int));
    if (!novoarray) {
        return NULL; // Falha na alocação de memória
    }


  if(num_artists > 0){
    int i;
    for(i = 0; i < num_artists; i++){
      novoarray[i] = music->music_artist_id[i];
    }
  }

  return novoarray;
}



// char* get_music_lyrics (Music* music){
//   return strdup(music->music_lyrics);

// }