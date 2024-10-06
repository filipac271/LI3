#ifndef UTILIDADES_H
#define UTILIDADES_H


char* remove_quotes(const char* str);
void freeCleanerArtist(char* clean_id,char* clean_name,char* clean_description,char* ganhos, char* clean_country,char* clean_type);
void freeCleanerMusics(char* music_id,char* music_title,char* music_artist_id,char* music_duration,char* music_genre,char* music_year,char* music_lyrics);
void freeCleanerUsers(char* username,char* email,char* nome ,char*  apelido,char* birth_date,char*  country,char* subscription_type);
#endif