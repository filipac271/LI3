#include "Entitys/musics.h" 
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <glib.h>


struct music{
  char *music_id;
  char *music_title;
  char **music_artist_id;
  char *music_duration;
  char *music_genre;
  char *music_year;
  int num_artistId;
};

Music* new_music(char* music_id, char* music_title, char** music_artist_id, char* music_duration, char* music_genre, char* music_year, int num_artists){
  Music* n_music = malloc(sizeof(Music));
    if (n_music == NULL) {
        fprintf(stderr, "Memory allocation failed for new music\n");
        exit(1);
    }
      //printf("%d\n", num_artists);


  n_music->music_id = strdup(music_id);
  n_music->music_title = strdup(music_title);


  //printf("%d\n", num_artists);
  n_music->music_artist_id = malloc((num_artists+1)* sizeof(char*));

    for(int i = 0; i < num_artists; i++){
      n_music->music_artist_id[i] = strdup(music_artist_id[i]);
    }
    
  n_music->num_artistId = num_artists;
  n_music->music_duration = strdup(music_duration);
  n_music->music_genre = strdup(music_genre);
  n_music->music_year = strdup(music_year);

  if (!n_music->music_id || !n_music->music_title || !n_music->music_artist_id || !n_music->music_duration || !n_music->music_genre) {
        printf("Memory allocation failed for one or more fields in new_music\n");
        free_musica(n_music);
        exit(1);
    }

  return n_music;

}

//alterada
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

        free(musica);
    }
}

//alterada
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

  } else{
    printf("N existe esta musica\n");
  }
}


//Getters

char* get_music_id (Music* music){
  return music->music_id;
}

char* get_music_title (Music* music){
  return music->music_title;
}

char** get_music_artist_id (Music* music){
  return music->music_artist_id;
}

char* get_music_duration (Music* music){
  return music->music_duration;
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
  return music->music_genre;
}

char* get_music_year (Music* music){
  return music->music_year;
}

//COISAS TIRADAS DO .H SOBRE DINFO, VER DEPOIS SE É REALMENTE PARA APAGAR
//typedef struct discography_info Info_M;

// Info_M* new_dinfo (char* artist_id, int s_discography, char* artist_country);

// void free_dinfo (Info_M* dinfo);

// void print_dinfo(Info_M* dinfo);

// int get_dinfo_discography (Info_M* dinfo);

// void set_dinfo_discography (Info_M* dinfo, int new_discography);

// void set_dinfo_new_discography (Info_M* dinfo, int new_discography);

// char* get_dinfo_country (Info_M* dinfo);

// char* get_dinfo_id (Info_M* dinfo);

// struct discography_info{
//   char *artist_id; //array
//   int discography; 
//   char* artist_country;
// };


// //Nota: quando o artist id for um array fazer um for para apenas ter um unico artista em todos e tal
// Info_M* new_dinfo (char* artist_id, int s_discography, char* artist_country){
//   Info_M* n_dinfo = malloc(sizeof(Info_M));
//     if(n_dinfo == NULL){
//       fprintf(stderr, "Memory allocation failed for new dinfo\n");
//       exit(1);
//     }

//     n_dinfo->artist_id = strdup(artist_id);
//     n_dinfo->discography  = s_discography; //acho que isto deve funcionar, mas iremos descobrir
//     n_dinfo->artist_country = strdup(artist_country);

//     return n_dinfo;
// }


// void free_dinfo (Info_M* dinfo){
//   if(dinfo){
//     free(dinfo->artist_id);
//     free(dinfo->artist_country);

//     free(dinfo);
//   }
// }

// void print_dinfo(Info_M* dinfo){
//   if(dinfo){
//     printf("ARTIST_ID: %s\n", dinfo->artist_id);
//     printf("DISCOGRAPHY: %d \n", dinfo->discography);
//     printf("ARTIST_COUNTRY: %s\n", dinfo->artist_country);
//   } else{
//     printf("Nao existe Dinfo!\n");
//   }
// }


//GETTER E SETTERS DINFO VER DEPOIS SE É RALMENTE PARA APGAR
// int get_dinfo_discography (Info_M* dinfo){
//   return dinfo->discography;
// }

// void set_dinfo_discography (Info_M* dinfo, int new_discography){
//   dinfo->discography = new_discography;
// }

// //tentative de setter que ja junta a discografia
// void set_dinfo_new_discography (Info_M* dinfo, int new_discography){
//   dinfo->discography += new_discography;
// }

// char* get_dinfo_country (Info_M* dinfo){
//   return dinfo->artist_country;
// }

// char* get_dinfo_id (Info_M* dinfo){
//   return dinfo->artist_id;
// }