#include "validacao/validaUser.h"
#include "utilidades.h"
#include "controler/musicsController.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <glib.h>
#include <unistd.h>
#include "IOManager.h"

int validaUser(char* email, char* date, char* type,MusicData* musicsController,char* songs,int numSongs, Output* Erros, char* linha){
    int t = 1;
    int d = 1;
    int e = 1;
    int existMusic = 1;
    int tembarra = 1;

    int* liked_songs_id = likedSongs(songs,numSongs);

    if (songs[1] != '[') tembarra = 0;
    
    if (!(strcmp(type, "\"premium\"") == 0 || strcmp(type, "\"normal\"") == 0)) t = 0;

    d = validaData(date);

    e = validaEmail(email);

    for (int i = 0; i < numSongs; i++) {
       
    if (liked_songs_id[i] == -1) {
        printf("Erro: artistsId[%d] é NULL\n", i);
        existMusic = 0;
        break;
    }


        
    if (lookup_musica(musicsController,liked_songs_id[i]) == NULL) {
        // printf("Artista %d não encontrado na hash table\n", liked_songs_id[i]);
        // sleep(1);
        existMusic = 0;
        
        break;
    }
}



if((t & d & e & existMusic & tembarra)==0)
{
    outputErros(Erros,linha);
}

freeArray(liked_songs_id);
    
return (t & d & e & existMusic);

}