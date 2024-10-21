#ifndef MUSICS_H
#define MUSICS_H

typedef struct music Music;

typedef struct discography_info Info_M;




Music* new_music(char* music_id, char* music_title, char** music_artist_id, char* music_duration, char* music_genre, char* music_year, char* music_lyrics, int num_artists);

void free_musica(Music* musica);

void print_musicas(Music * musica);



Info_M* new_dinfo (char* artist_id, int s_discography, char* artist_country);

void free_dinfo (Info_M* dinfo);

void print_dinfo(Info_M* dinfo);




char* get_music_id (Music* music);

char* get_music_title (Music* music);

char** get_music_artist_id (Music* music);

char* get_music_duration (Music* music);

int duration_to_seconds(char* music_duration);

int get_music_duration_seconds (Music* musica);

char* get_music_genre (Music* music);

char* get_music_year (Music* music);

char* get_music_lyrics (Music* music);


int get_dinfo_discography (Info_M* dinfo);

void set_dinfo_discography (Info_M* dinfo, int new_discography);

void set_dinfo_new_discography (Info_M* dinfo, int new_discography);

char* get_dinfo_country (Info_M* dinfo);

char* get_dinfo_id (Info_M* dinfo);

#endif