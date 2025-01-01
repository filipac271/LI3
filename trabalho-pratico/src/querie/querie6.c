#include "controler/historyController.h" 
#include "Entitys/history.h"
#include "utilidades.h"
#include "Output.h"
#include <stdio.h>
#include <string.h>



void normalizaId(int id, char *resultado, char c) {
    if(c=='a')
    {
       sprintf(resultado, "AL%07d", id);
    }
    else if( c=='A')
    {
        sprintf(resultado, "A%07d", id);
    }

}

void querie6(int i, char * line, HistoryData* historyController,AlbumsData* albumController)
{
      char* filename = malloc(sizeof(char) * 256);
    if (filename == NULL) {
        printf("Erro ao alocar memória para o nome do ficheiro.\n");
        return;
    }

    sprintf(filename, "resultados/command%d_output.txt", i + 1);
    Output* output = iniciaOutput(filename);

    int  ano, N; char user_id[9];
    int count = sscanf(line, " %*[^ ] %s %d %d", user_id, &ano, &N);
    int userId=transformaIds(user_id);
    int posicaoAno=getPosicaoAno(historyController,userId, ano);
 
    if(posicaoAno==-1)
    {
        outputNULL(output);
        freeOutput(output);
        free(filename);
        return;
    }
    else
    {
        char* data=getDia(historyController,userId, posicaoAno);
       printf("%s \n",data);
        char* genero= getGeneroMaisOuvido(historyController,userId, posicaoAno);
        int album=getAlbumFavorito(historyController,userId, posicaoAno,albumController);
        char albumfav[10];
        normalizaId(album, albumfav,'a');
        char* hora= getHora(historyController,userId, posicaoAno);
        char* resultados= getArtistaMaisOuvido(historyController,userId, posicaoAno);
        int artistId, nMusicas, tempoAudicao;
        sscanf(resultados,"%d %d %d",&artistId, &nMusicas, &tempoAudicao);
        char artista[10];
        normalizaId(artistId,artista, 'A');
        char* tempo= seconds_to_hhmmss(tempoAudicao); 
        printf("dasdsadasda%s\n",data);
         
        output6(line[1],output,tempo,nMusicas,artista, data,genero, albumfav,hora, 0); 

        if( count==3)
      {
            int* artistas=getNartistasMaisOuvidos(historyController,userId, ano, N);
            int tempoAudicao, nMusicas;
            
            for(int j=0;j<N;j++)
            {
                artistId=getIdArtista(historyController,userId, posicaoAno,artistas[j]);
                normalizaId(artistId,artista, 'A');
                tempoAudicao=getTempoArtista(historyController,userId, posicaoAno,artistas[j]);
                nMusicas=getnMusicasArtista(historyController,userId, posicaoAno,artistas[j]);
                char* tempo= seconds_to_hhmmss(tempoAudicao);

                output6(line[1],output,tempo,nMusicas,artista, NULL,NULL, NULL,NULL,1);
            }
            
            free(artistas);
       }
    }
    
   freeOutput(output);
        free(filename);
}