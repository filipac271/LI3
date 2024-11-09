#ifndef MUSICS_H
#define MUSICS_H

typedef struct music Music;





Music* new_music(char* music_id, char* music_title, char** music_artist_id, char* music_duration, char* music_genre, char* music_year, int num_artists);

void free_musica(Music* musica);

void print_musicas(Music * musica);


char* get_music_id (Music* music);

char* get_music_title (Music* music);

char** get_music_artist_id (Music* music);

char* get_music_duration (Music* music);

int duration_to_seconds(char* music_duration);

int get_music_duration_seconds (Music* musica);

char* get_music_genre (Music* music);

char* get_music_year (Music* music);

// char* get_music_lyrics (Music* music);


#endif