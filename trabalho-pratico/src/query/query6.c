#include "controler/historyController.h" 
#include "Entities/history.h"
#include "utilidades.h"
#include "Output.h"
#include <stdio.h>
#include <string.h>



void normalizaId(int id, char *resultado, char c) {
    if(c=='a')
    {
       sprintf(resultado, "AL%06d", id);
    }
    else if( c=='A')
    {
        sprintf(resultado, "A%07d", id);
    }

}

void query6(int i, char * line, HistoryData* historyController, MusicData* musicController, AlbumsData* albumController)
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
        char* albumGenero= getAlbumGenero(historyController,musicController,albumController, userId, posicaoAno); 
        char genero[20];int album;
        sscanf(albumGenero,"%d%[^0-9]", &album, genero);
        char albumfav[9];
        normalizaId(album, albumfav,'a');
        char* hora= getHora(historyController,userId, posicaoAno);
        char** resultados= getNartistasMaisOuvidos(historyController, musicController,userId, posicaoAno,0);
        int artistId, nMusicas, tempoAudicao;
        sscanf(resultados[0],"%d %d %d",&artistId, &nMusicas, &tempoAudicao);
        char artista[10];
        normalizaId(artistId,artista, 'A');
        char* data=getDia(historyController,userId, posicaoAno);
        char* tempo= seconds_to_hhmmss(tempoAudicao); 
        free(resultados[0]);
        free(resultados);
        output6(line[1],output,tempo,nMusicas,artista, data, genero, albumfav,hora, 0); 

        // Caso for pedido os N artistas mais ouvidos
        if( count==3)
        { 
            char** resultadosN=getNartistasMaisOuvidos(historyController, musicController, userId, posicaoAno, N);
            int artistId, nMusicas, tempoAudicao;
            int j=0;
            for(;resultadosN[j]!=NULL;j++)
            {    
                sscanf(resultadosN[j],"%d %d %d",&artistId, &nMusicas, &tempoAudicao);
                normalizaId(artistId,artista, 'A'); 
                char* tempo= seconds_to_hhmmss(tempoAudicao);  
                output6(line[1],output,tempo,nMusicas,artista, NULL,NULL, NULL,NULL,1);
                free(tempo); 
                free(resultadosN[j]);
            }
            free(resultadosN[j]);
            free(resultadosN);
        }
            free(albumGenero);
            free(hora);
            free(data);
            free(tempo);
    }
    
   freeOutput(output);
        free(filename);
}