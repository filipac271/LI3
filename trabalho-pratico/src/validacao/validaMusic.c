#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <glib.h>

#include "utilidades.h"
#include "controler/artistsController.h"
#include "IOManager.h"

int validaMusic(char* duracao, char** artistsId,ArtistsData* artistsController,int numArtistsId,char* music_artist, Output* Erros, char* linha) {
    int d;
    int pertence = 1;  // Assumir que todos os artistas pertencem
    int tembarra = 1;

    d = validaDuraçao(duracao);
    int tamanho = strlen(music_artist);   
    if (music_artist[1] != '[' || music_artist[tamanho-2] != ']'){tembarra = 0;    }




    for (int i = 0; i < numArtistsId; i++) {
    if (artistsId[i] == NULL) {
        printf("Erro: artistsId[%d] é NULL\n", i);
        pertence = 0;
        break;
    }

    

    if (lookup_artist(artistsController,artistsId[i]) == NULL) {
        //printf("Artista %s não encontrado na hash table\n", artistsId[i]);
        pertence = 0;
        break;
    }
}

  if((d & pertence & tembarra)==0)
  {
    outputErros(Erros,linha);
    
  }
    return (d & pertence & tembarra);  // Combinação bitwise dos resultados de duração e artistas
}
