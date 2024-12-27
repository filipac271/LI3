
#include "utilidades.h"
#include "controler/musicsController.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <glib.h>
#include <unistd.h>
#include "Output.h"

int validaUser(char* email, char* date, char* type,MusicData* musicsController,char* songs,int numSongs, Output* Erros, char* linha){



    if (songs[1] != '[') {
        outputErros(Erros,linha);
        return 0;
    }
    

    if (!(strcmp(type, "\"premium\"") == 0 || strcmp(type, "\"normal\"") == 0)){
        outputErros(Erros,linha);
        return 0;
    }

    if(!(validaData(date))){
        outputErros(Erros,linha);
        return 0;
    }


    if(!(validaEmail(email))){
        outputErros(Erros,linha);
        return 0;
    }

    int* liked_songs_id = divideArray(songs,numSongs);

    for (int i = 0; i < numSongs; i++) {
       
        if (lookup_musica(musicsController,liked_songs_id[i]) == NULL) {
            outputErros(Erros,linha);
            freeArray(liked_songs_id);
            return 0;
        }
    }





freeArray(liked_songs_id);
    
return 1;

}