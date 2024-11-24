#ifndef UTILIDADES_H
#define UTILIDADES_H

#include<stdlib.h>
#include<stdio.h>
#include <glib.h>
#include"Entitys/users.h"



int calcular_idade( char* data_nascimento_str);

guint get_garray_length(GArray *array);

char* seconds_to_hhmmss(int total_seconds);

char* remove_quotes(char* str);

int validaData(char* date);

int validaEmail (char* email);

int validaDuraçao (char* duracao);

int calculate_num_members( char* grupo);

void freeArray(int* array) ;

int* divideGroup(char* group, int numMembros);

int* divideArray(char* arrayString, int numElements);

int transformaIds (char* idString);

int compararFicheirosPorLinha(char *file1,char *file2, int *ocorrenciasCorretas);

#endif