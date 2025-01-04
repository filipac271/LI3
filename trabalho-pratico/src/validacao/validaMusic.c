#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <glib.h>

#include "utilidades.h"
#include "controler/artistsController.h"
#include "controler/albumsController.h"
#include "Output.h"

int validaMusic(char *duracaoAspas, char *music_artists, ArtistsData *artistsController, Output *Erros, char *linha, AlbumsData *albumController, char *albumId)
{

  if (!(validaDuracao(duracaoAspas)))
  {
    outputErros(Erros, linha);
    return 0;
  }

  if (music_artists[1] != '[')
  {
    outputErros(Erros, linha);
    return 0;
  }

  int numArtistsId = calculate_num_members(music_artists);
  int *artistsId = divideArray(music_artists, numArtistsId);

  for (int i = 0; i < numArtistsId; i++)
  {

    if (lookup_artist(artistsController, artistsId[i]) == NULL)
    {
      freeArray(artistsId);
      outputErros(Erros, linha);
      return 0;
    }
  }

  if (lookup_album(albumController, transformaIds(albumId)) == NULL)
  {
    freeArray(artistsId);
    outputErros(Erros, linha);
    return 0;
  }

  freeArray(artistsId);

  return 1;
}