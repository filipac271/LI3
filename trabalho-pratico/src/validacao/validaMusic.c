#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <glib.h>

#include "utilidades.h"
#include "controler/artistsController.h"
#include "controler/albumsController.h"
#include "Output.h"

int validaMusic(char* duracaoAspas, char* music_artists,ArtistsData* artistsController, Output* Erros, char* linha, AlbumsData* albumController,char* albumId) {

    int d;
    int pertence = 1;  // Assumir que todos os artistas pertencem
    int tembarra = 1;
    int existeAlbum = 1;

    d = validaDuracao(duracaoAspas);

    if (music_artists[1] != '[' ){
      outputErros(Erros,linha);
      return 0;
    }


    int numArtistsId = calculate_num_members(music_artists);
    int* artistsId = divideArray(music_artists,numArtistsId);


    for (int i = 0; i < numArtistsId; i++) {

      if (lookup_artist(artistsController,artistsId[i]) == NULL) {
          pertence = 0;
          break;
      }
}

  if(lookup_album(albumController,transformaIds(albumId)) == NULL){
    existeAlbum = 0;
  }

  if((d & pertence & tembarra & existeAlbum)==0)
  {

    outputErros(Erros,linha);
    
  }

  freeArray(artistsId);
  
  return (d & pertence & tembarra & existeAlbum);  // Combinação bitwise dos resultados de duração e artistas
}