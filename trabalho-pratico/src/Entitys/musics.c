#include "Entitys/musics.h" 
#include "utilidades.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


struct music{
  char *music_id;
  char *music_title;
  char **music_artist_id;
  char *music_duration;
  char *music_genre;
  char *music_year;
  char *music_lyrics;
  int num_artistId;
};





Music* new_music(char* music_id, char* music_title, char** music_artist_id, char* music_duration, char* music_genre, char* music_year, char* music_lyrics, int num_artists){
  Music* n_music = malloc(sizeof(Music));
    if (n_music == NULL) {
        fprintf(stderr, "Memory allocation failed for new music\n");
        exit(1);
    }


  n_music->music_id = strdup(music_id);
  n_music->music_title = strdup(music_title);


  n_music->music_artist_id = malloc((num_artists+1)* sizeof(char*));

    for(int i = 0; i < num_artists; i++){
      n_music->music_artist_id[i] = strdup(music_artist_id[i]);
    }
    
   n_music->num_artistId = num_artists;
  n_music->music_duration = strdup(music_duration);
  n_music->music_genre = strdup(music_genre);
  n_music->music_year = strdup(music_year);
  n_music->music_lyrics = (music_lyrics);

  return n_music;

}

void free_musica(Music* musica) {
    if (musica) {

        free(musica->music_id);
        free(musica->music_title);

        int i;

        for(i = 0;i < musica->num_artistId; i++){
            free(musica->music_artist_id[i]);
        }
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
    printf("ID_MUSIC: %s\n", musica->music_id);
    printf("MUSIC_TITLE: %s\n", musica->music_title);

    printf("MUSIC_ARTIST:\n");
    for(int i = 0; i < musica->num_artistId; i++){
      printf("%s\n", musica->music_artist_id[i]);
    }

    printf("MUSIC_DURATION: %s\n", musica->music_duration);
    printf("MUSIC_GENRE: %s\n", musica->music_genre);
    printf("MUSIC_YEAR: %s\n", musica->music_year);
    printf("MUSIC_LYRICS: %s\n", musica->music_lyrics);

  } else{
    printf("N existe esta musica\n");
  }
}


//Getters

char* get_music_id (Music* music){
  return strdup(music->music_id);
}

char* get_music_title (Music* music){
  return strdup(music->music_title);
}

char** get_music_artist_id (Music* music){
  return music->music_artist_id;
}

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

char* get_music_lyrics (Music* music){
  return strdup(music->music_lyrics);

}