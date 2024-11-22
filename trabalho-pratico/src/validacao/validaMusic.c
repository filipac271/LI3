#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <glib.h>

#include "utilidades.h"
#include "controler/artistsController.h"
#include "IOManager.h"

int validaMusic(char* duracaoAspas, char* music_artists,ArtistsData* artistsController, Output* Erros, char* linha) {
    char *duracao = remove_quotes(duracaoAspas);

    int d;
    int pertence = 1;  // Assumir que todos os artistas pertencem
    int tembarra = 1;

    d = validaDuraçao(duracao);
    int tamanho = strlen(music_artists);   
    if (music_artists[1] != '[' || music_artists[tamanho-2] != ']'){tembarra = 0;}

    char* music_artistsClean = remove_quotes(music_artists);
    char** artistsId = divideArtists(music_artistsClean);

    int numArtistsId = contar_elementos(music_artists);

    for (int i = 0; i < numArtistsId; i++) {
    if (artistsId[i] == NULL) {
        printf("Erro: artistsId[%d] é NULL\n", i);
        pertence = 0;
        break;
    }

    

    if (lookup_artist(artistsController,artistsId[i]) == NULL) {
        pertence = 0;
        break;
    }
}

  if((d & pertence & tembarra)==0)
  {
    outputErros(Erros,linha);
    
  }

  free(duracao);
  free(music_artistsClean);
  free(artistsId);

  return (d & pertence & tembarra);  // Combinação bitwise dos resultados de duração e artistas
}