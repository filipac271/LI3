#ifndef UTILIDADES_H
#define UTILIDADES_H

#include<stdlib.h>
#include<stdio.h>
#include"Entitys/users.h"






int calcular_idade(const char* data_nascimento_str);
char* remove_quotes(const char* str);
void freeCleanerArtist(char* clean_id,char* clean_name,char* clean_description,char* ganhos, char* clean_country,char* clean_type);
void freeCleanerMusics(char* music_id,char* music_title,char* music_artist_id,char* music_duration,char* music_genre,char* music_year,char* music_lyrics);
void freeCleanerUsers(char* username,char* email,char* nome ,char*  apelido,char* birth_date,char*  country,char* subscription_type);
int validaData(char* date);
int validaEmail (char* email);

int validaDuraçao (char* duracao);
char* pegaLinha(FILE* ficheiro, size_t* len, char** line);
void parser(char* linha,char* tokens[]);

char** divideGroup(char* group, int numMembros);
char** divideArtists(char* music_artist);
int contar_elementos(char *str);
char** likedSongs(char* songs, int numberS);


#endif