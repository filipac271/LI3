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

int validaUser(char* email, char* date, char* type,MusicData* musicsController,char** likedSongs,int numSongs, Output* Erros, char* linha){
    int t = 1;
    int d = 1;
    int e = 1;
    int existMusic = 1;

    if (!(strcmp(type, "premium") == 0 || strcmp(type, "normal") == 0)) t = 0;

    d = validaData(date);

    e = validaEmail(email);

    for (int i = 0; i < numSongs; i++) {
       
    if (likedSongs[i] == NULL) {
        printf("Erro: artistsId[%d] é NULL\n", i);
        existMusic = 0;
        break;
    }


        
    if (lookup_musica(musicsController,likedSongs[i]) == NULL) {
        //printf("Artista %s não encontrado na hash table\n", artistsId[i]);
        existMusic = 0;
        
        break;
    }
}

if((t & d & e & existMusic)==0)
{
    outputErros(Erros,linha);
    free(linha);
}




    
return (t & d & e & existMusic);

}
