#include "controler/historyController.h" 
#include "Entitys/history.h"
#include "utilidades.h"
#include "Output.h"
#include <stdio.h>
#include <string.h>

char* normalizaId(int id, char c)
{
    //Calcula quantos digitos tem o id
    int nDigitos = snprintf(NULL, 0, "%d", id);
    //Calcula quantos zeros sao precisos
    int nZeros =7 - nDigitos;  
    char* normalizado=NULL;
    if(c=='a')
    {
        sprintf(normalizado, "AL%0*d", nZeros + nDigitos, id);
    }
    else if( c=='A')
    {
        sprintf(normalizado, "A%0*d", nZeros + nDigitos, id);
    }
    return normalizado;
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
    {printf(" COMECA  %d\n",i+1);
        char* data=getDia(historyController,userId, ano);
       printf("%s\n",data);
        char* genero= getGeneroMaisOuvido(historyController,userId, ano);
        int album=getAlbumFavorito(historyController,userId, ano,albumController);
        char* albumfav=normalizaId(album,'a');
        char* hora= getHora(historyController,userId, ano);
        char* resultados= getArtistaMaisOuvido(historyController,userId, ano);
        int artistId, nMusicas, tempoAudicao;
        sscanf(resultados,"%d %d %d",&artistId, &nMusicas, &tempoAudicao);
        char* artista=normalizaId(artistId, 'A');
        char* tempo= seconds_to_hhmmss(tempoAudicao);  
        printf("Holaaaaaaaaaaaaaa\n");
        output6(line[1],output,tempo,nMusicas,artista, data,genero, albumfav,hora, 0); 

        if( count==3)
      {
            int* artistas=getNartistasMaisOuvidos(historyController,userId, ano, N);
            int tempoAudicao, nMusicas;
            
            for(int j=0;j<N;j++)
            {
                artistId=getIdArtista(historyController,userId, ano,artistas[j]);
                artista=normalizaId(artistId, 'A');
                tempoAudicao=getTempoArtista(historyController,userId, ano,artistas[j]);
                nMusicas=getnMusicasArtista(historyController,userId, ano,artistas[j]);
                artista=normalizaId(artistId,'A');
                char* tempo= seconds_to_hhmmss(tempoAudicao);
                char* artista=normalizaId(artistId,'A');

                output6(line[1],output,tempo,nMusicas,artista, NULL,NULL, NULL,NULL,1);
            }
            
            free(artistas);
       }
    }
    
   freeOutput(output);
        free(filename);
}