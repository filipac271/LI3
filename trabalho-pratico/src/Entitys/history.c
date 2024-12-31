#include "Entitys/musics.h" 
#include "controler/musicsController.h"
#include "utilidades.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "Entitys/history.h"
#include "Entitys/artists.h"
#include "controler/historyController.h"


/* Ideia principal do historico (para ficar aqui registado)

Para a query 4 teremos uma hashtable em que a key é a data de domigno(inicio da semana) 
nessa semana cada espacinho é uma strcut com artista e tempo total desse artista na semana
IMPORTANTE se for uma banda é preciso ver os seis constituintes e adicionar a esses artistas 
e não à banda em si.

Comando
4 [begin_date end_date]
Output
name;type;count_top_10


//FALAR COM A CAROL DEPOIS
Para a query 6 teremos uma hashtable em que a key é o userid e dentro teremos uma struct com 
o artista o total de temppo desse ano
pensar em algo para o #musica.???
genero????

struct ano{
  char* user_id;
  Ghashtable
}


Comando
6 <user_id> <year> [N]
Output
listening time;#musics;artist;day;genre;favorite_album;hour
[artista_preferido_1;#musicas;listening_time]
[artista_preferido_2;#musicas;listening_time]
[…]

HISTORICO
- id – identificador único do registo;
– user_id – identificador único do utilizador a que o registo se refere;
– music_id – identificador único da música a que o registo se refere;
– timestamp – data e hora em que a música foi ouvida pelo utilizador;
– duration – tempo de duração da audição da música. E.g., um utilizador pode ter ouvido
apenas 30 segundos de uma música;
– platform – plataforma em que a música foi reproduzida. I.e., computador ou disposi-
tivo móvel.

*/

struct artistahistory{
  int artist_id;
  int totalsemanalsegundos; //passar a duration de hh:mm:ss (funcao defenida nas utilities) 
};

struct domingo{
  char* data ;
  GHashTable* artistahistory;
};


struct genero {
    char* genero;    
    int tempoAudicao;   
};

struct album {
    int album; 
    int tempoAudicao; 
};

struct dia{
  int dia;
  int mes;
  int nMusicas;
};

struct artista{
  int artista;
  int* musicas;
  int tamanhoArray;
  int nMusicas;
  int tempoAudicao;
  
};
struct ano
{
  int ano;
  Artistas* artistas; 
  int tamanhoArtistas;
  int nArtistas;
  Generos* genero;
  int tamanhoG;
  int nGeneros;
  Albuns* album;
  int nAlbuns;
  int tamanhoA;
  int* horas;
  Dia* dia;
  int nDias;
  int tamanhoD;
};

struct userHistory
{
  int id;
  Ano* anos;
  int nAnos;
  int tamanhoArray;

};


void printUserHistory(History* userHistory) {
    if (userHistory == NULL) {
        printf("Histórico de utilizador não encontrado.\n");
        return;
    }

    printf("ID do utilizador: %d\n", userHistory->id);
    printf("Número de anos registrados: %d\n", userHistory->nAnos);

    for (int i = 0; i < userHistory->nAnos; i++) {
        Ano* ano = &userHistory->anos[i];
        printf("\nAno: %d\n", ano->ano);

        printf("Número de artistas: %d\n", ano->nArtistas);
        for (int j = 0; j < ano->nArtistas; j++) {
            Artistas* artista = &ano->artistas[j];
            printf("  Artista ID: %d, Tempo de audição: %d, Número de músicas: %d\n", 
                   artista->artista, artista->tempoAudicao, artista->nMusicas);
            printf("  Músicas: ");
            for (int k = 0; k < artista->tamanhoArray; k++) {
                printf("%d ", artista->musicas[k]);
            }
            printf("\n");
        }

        printf("\nNúmero de géneros: %d\n", ano->nGeneros);
        for (int j = 0; j < ano->nGeneros; j++) {
            Generos* genero = &ano->genero[j];
            printf("  Género: %s, Tempo de audição: %d\n", 
                   genero->genero, genero->tempoAudicao);
        }

        printf("\nNúmero de álbuns: %d\n", ano->nAlbuns);
        for (int j = 0; j < ano->nAlbuns; j++) {
            Albuns* album = &ano->album[j];
            printf("  Álbum ID: %d, Tempo de audição: %d\n", 
                   album->album, album->tempoAudicao);
        }

        printf("\nHoras por ano:\n");
        for (int j = 0; j < 12; j++) { // Supondo que o array `horas` tem tamanho 12 para os meses do ano
            printf("  Mês %d: %d horas\n", j + 1, ano->horas[j]);
        }

        printf("\nNúmero de dias: %d\n", ano->nDias);
        for (int j = 0; j < ano->nDias; j++) {
            Dia* dia = &ano->dia[j];
            printf("  Dia: %d/%d, Número de músicas: %d\n", 
                   dia->dia, dia->mes, dia->nMusicas);
        }
    }
}

int IdArtista(History* userHistory, int ano, int i)
{
    return userHistory->anos[ano].artistas[i].artista;
}

int TempoArtista(History* userHistory, int ano, int i)
{
  return userHistory->anos[ano].artistas[i].tempoAudicao;
}

int nMusicasArtista(History* userHistory, int ano, int i)
{
  return userHistory->anos[ano].artistas[i].nMusicas;
}


void sort(int* artistas, Artistas* artista, int N)
{
  for (int i = 0; i < N; i++) {
        artistas[i] = i;
    }
    int tempo1,tempo2,id1,id2,temp;

  for (int i = 0; i < N - 1; i++)
   {    
     for (int j = i + 1; j < N; j++) 
     {
        tempo1=artista[artistas[i]].tempoAudicao ;
        tempo2=artista[artistas[j]].tempoAudicao ;
        id1=artista[artistas[i]].artista;
        id2=artista[artistas[j]].artista;
        if (tempo1<tempo2 ||(tempo1==tempo2 && id1>id2) )
         {
                temp = artistas[i];
                artistas[i] = artistas[j];
                artistas[j] = temp;
        }
      }
    }

}

int* NartistasMaisOuvidos(History* userHistory,int pAno, int N)
{
  Artistas* artista= userHistory->anos[pAno].artistas;  
 int nArtistas=userHistory->anos[pAno].nArtistas;
 int* artistas= calloc(N, sizeof(int)); 
  if(N>nArtistas)
  { 
     sort(artistas, artista,nArtistas);
  }
  else
  {
     sort( artistas,artista, N);
  }
 
  return artistas; 
}

char* ArtistaMaisOuvido(History* userHistory,int anoP)
{
  Artistas* artistas= userHistory->anos[anoP].artistas;
  int N= userHistory->anos[anoP].nArtistas;
  int max=artistas[0].tempoAudicao;
  int artistaId=artistas[0].artista;
  int tempoTotal=max;
  int nMusicas=artistas[0].nMusicas;
  for(int i=1;i<N;i++)
  {
    if(max<artistas[i].tempoAudicao|| (max==artistas[i].tempoAudicao && artistaId>artistas[i].artista))
    {
      max=artistas[i].tempoAudicao;
      artistaId=artistas[i].artista;
    }
     tempoTotal+=artistas[i].tempoAudicao;
     nMusicas+=artistas[i].nMusicas;
  }
  char* resultados=NULL;
  sprintf(resultados,"%d %d %d",artistaId,nMusicas ,tempoTotal);

  return resultados;
}

char* HoraMaisAudicoes(History* userHistory,int anoP)
{
  int* horas=userHistory->anos[anoP].horas;
  int max=horas[0];
  int hora=0;
  for(int i=1;i<24;i++)
  {
    if(horas[i]>max )
    {
      max=horas[i];
      hora=i;
    }
  }
  char* horaMais=NULL;
  if(hora<10)
  {
    sprintf(horaMais,"0%d",hora);
  }
  else
  {
     sprintf(horaMais,"%d",hora);
  }
  return horaMais;
}

int AlbumFavorito(History* userHistory,int anoP, AlbumsData* albumController)
{
  Albuns* albuns= userHistory->anos[anoP].album;
  int N= userHistory->anos[anoP].nAlbuns;
  int max=albuns[0].tempoAudicao;
  Album* albumfav= lookup_album(albumController,albuns[0].album );
  char* albumFavNome=getAlbumName(albumfav);
  int albumId=albuns[0].album;

  for(int i=1;i<N;i++)
  {
    Album* album= lookup_album(albumController,albuns[i].album );
    char* albumNome=getAlbumName(album);

    if(max<albuns[i].tempoAudicao|| (max==albuns[i].tempoAudicao && strcmp(albumFavNome,albumNome)>0))
    {
      max=albuns[i].tempoAudicao;
      albumFavNome=albumNome;
      albumId=albuns[i].album;
    }
  }
  return albumId;
}

char* GeneroMaisOuvido(History* userHistory, int anoP)
{
  Generos* generos= userHistory->anos[anoP].genero;
  int N= userHistory->anos[anoP].nGeneros;
  int max=generos[0].tempoAudicao;
  char* generofav=generos[0].genero;
  for(int i=1;i<N;i++)
  {
    if(max<generos[i].tempoAudicao|| (max==generos[i].tempoAudicao && strcmp(generofav,generos[i].genero)>0))
    {
      max=generos[i].tempoAudicao;
      generofav=generos[i].genero;
    }
  }
  return generofav;
}

char* DataParaChar(int ano,int mes,int dia)
{
     char* data=NULL;
    if(dia<10 && mes>10)
    { 
      sprintf(data,"%d/%d/0%d",ano,mes,dia); 
    }
    else if(dia>=10 && mes<10)
    {
      sprintf(data,"%d/0%d/%d",ano,mes,dia); 
    }
    else if( dia<10 && mes<10)
    {
       sprintf(data,"%d/0%d/0%d",ano,mes,dia); 
    }
    else if( dia>=10 && mes>=10)
    {
       sprintf(data,"%d/%d/%d",ano,mes,dia); 
    }
    return data;
}

char* DataMaisMusicas(History* userHistory,int anoP)
{
  Dia* dias= userHistory->anos[anoP].dia;
  int maior=dias[0].nMusicas;
  int dia=dias[0].dia;
  int mes= dias[0].mes;
    for(int i=1;i<userHistory->anos[anoP].nDias;i++)
    {
      if(maior<dias[i].nMusicas || (maior==dias[i].nMusicas && (mes<dias[i].mes ||  (mes==dias[i].mes && dia<dias[i].dia )) ))
      {
        dia=dias[i].dia;
        mes=dias[i].mes;
      }
    }
    char* data = DataParaChar(userHistory->anos[anoP].ano,mes,dia);
   
    return data;
}

int procuraAno(History* userHistory, int ano)
{
int anoP=-1;
 for(int i=0; i<userHistory->nAnos && ano==-1;i++){
  if(userHistory->anos[i].ano==ano )
  {
    anoP=i;
  }
 }
 return anoP;
}




Ano* insereGenero(char* genero,Ano* ano ,int tempo, int nAno, int novo)
{
  if(novo==1)
  {
      ano[nAno].genero=calloc(5,sizeof(Generos));
      ano[nAno].genero[0].genero=genero;
      ano[nAno].genero[0].tempoAudicao=tempo;
      ano[nAno].nGeneros=1;
      ano[nAno].tamanhoG=5;
  }
  else
  {
    
    int i, N=ano[nAno].nGeneros;printf("%d\n",N);
    Generos* generos=ano[nAno].genero;

     for( i=0;i<N && strcmp(genero,generos[i].genero)!=0;i++){}
     if(i<N)
     {
      generos[i].tempoAudicao+=tempo;
     }  
     else
     {
      if(ano[nAno].tamanhoG<= N)
      {
        int newSize=ano[nAno].tamanhoG*2;
        ano[nAno].genero=realloc(ano[nAno].genero, newSize*  sizeof(Generos));
        ano[nAno].tamanhoG*=2;
      }
        generos[i].genero=genero;
        generos[i].tempoAudicao+=tempo;
        ano[nAno].nGeneros++;
     }
     ano[nAno].genero=generos;
}
return ano;
}

Ano* insereAlbum(int albumID,Ano* ano ,int tempo, int nAno, int novo)
{
  if(novo==1)
  {
    Albuns* album=calloc(4,sizeof(Generos));
    album[0].album=albumID;
    album[0].tempoAudicao=tempo;
     ano[nAno].album=album;
     ano[nAno].nAlbuns=1;
  }
  else
  {
    int i, N=ano[nAno].nAlbuns;
     Albuns* album=ano[nAno].album;

     for( i=0;i<N && albumID!=album[i].album;i++){}
     if(i<N)
     {
      album[i].tempoAudicao+=tempo;
     }  
     else
     {
       if(ano[nAno].tamanhoA<=N)
      {
        int newSize=ano[nAno].tamanhoA*2;
        ano[nAno].album= realloc( ano[nAno].album , newSize*  sizeof(Albuns));
        ano[nAno].tamanhoA*=2;
      }
       album[i].album=albumID;
       album[i].tempoAudicao+=tempo;
        ano[nAno].nAlbuns++;
     }
     ano[nAno].album=album;
}
return ano;
}


Ano* insereDia(int mes, int dia, Ano* ano, int nAno, int novo)
{
  if(novo==1)
  {
    Dia* dias=malloc(4* sizeof(Dia));
    dias[0].dia=dia;
    dias[0].mes=mes;
    dias[0].nMusicas=1;
    ano[nAno].dia=dias;
    ano[nAno].nDias=1;
    
  }
  else
  {
    int i, N=ano[nAno].nDias;
    Dia* dias=ano[nAno].dia;
    for( i=0;i<N && (dia!=dias[i].dia || mes!=dias[i].mes);i++){}
    if(i<N)
    {
      dias->nMusicas++;
      ano[nAno].dia=dias;
      
    }
    else
    {
      if(ano[nAno].tamanhoD<=N)
      {
        int newSize=ano[nAno].tamanhoD*2;
        ano[nAno].dia = realloc(ano[nAno].dia , newSize* sizeof(Dia*));
        ano[nAno].tamanhoD*=2;
      }
      ano[nAno].dia[i].dia=dia;
      ano[nAno].dia[i].mes=mes;
       ano[nAno].dia[0].nMusicas=1;
    }
  }
  return ano;
}

int procura_Artista(Artistas* artistas,int N, int artistId)
{
  int i;
  for(i=0;i<N;i++)
  {
    printf("%d\n",i);
    if(artistas[i].artista==artistId)
    {
      return i;
    }
  }
  return -1;
}



Artistas* adicionarMusica(Artistas* artista ,int musicId,int aP,int duracao)
{
    int i;
    for( i=0;i<artista[aP].nMusicas && artista[aP].musicas[i]!=musicId;i++){}
    
    if(i>artista[aP].nMusicas && artista[aP].tamanhoArray>artista[aP].nMusicas)
    {
      artista[aP].musicas[i]=musicId;
      artista[aP].nMusicas++;
      artista[aP].tempoAudicao+=duracao;
    }
   else if (i>artista[aP].nMusicas && artista[aP].tamanhoArray<=artista[aP].nMusicas)
    {
      artista[aP].musicas=resize(artista[aP].musicas,artista[aP].tamanhoArray,'i');
      artista[aP].tamanhoArray*=2;
      artista[aP].musicas[i]=musicId;
      artista[aP].nMusicas++;
      artista[aP].tempoAudicao+=duracao;
    }
    else
    {
       artista[aP].tempoAudicao+=duracao;
    }
    return artista;
}

Artistas* novoArtista(Artistas* artista, int artistId, int musicId,int duracao,int p)
{
  //artista[p]=malloc(sizeof(Artistas));
  artista[p].artista=artistId;
  artista[p].musicas=malloc(2*sizeof(int*));
  artista[p].musicas[0]=musicId;
  artista[p].nMusicas=1;
  artista[p].tempoAudicao=duracao;

  return artista;
}



Ano* adicionaArtista(Ano* ANO, int* artistId,int numArtistas, int duracao,int musicId,int nAno, int novo)
{
 
  if(novo==1)
  { 
     ANO[nAno].artistas = calloc((numArtistas+2),sizeof(Artistas));
      ANO[nAno].tamanhoArtistas=numArtistas+2;

      for(int i=0;i<numArtistas;i++)
     {    
          ANO[nAno].artistas=novoArtista(ANO[nAno].artistas, artistId[i], musicId,duracao,i);
      }

      ANO[nAno].nArtistas=numArtistas;
      
  }
  else
  {
    for (int i=0;i<numArtistas;i++)
    {
      
      int artistaP=procura_Artista(ANO[nAno].artistas,ANO[nAno].nArtistas ,artistId[i]);
      
      if(artistaP==-1)
      {
          
          if(ANO[nAno].nArtistas>=ANO[nAno].tamanhoArtistas)
          {
           
              ANO[nAno].artistas=realloc( ANO[nAno].artistas,(2*ANO[nAno].tamanhoArtistas) * sizeof(Artistas));
              ANO[nAno].tamanhoArtistas*=2;

          }

          ANO[nAno].artistas= novoArtista(ANO[nAno].artistas, artistId[i], musicId,duracao,artistaP);
          ANO[nAno].nArtistas++;

      }
      else
      {
         ANO[nAno].artistas=adicionarMusica(ANO[nAno].artistas,musicId, artistaP,duracao) ;
       
      }
    }
  } 
  return ANO;
}

Ano* adicionarAno(MusicData* musicController ,Ano* anos, int musicId, int ano,int mes,int dia,int hora,int duracao,int nAno, int novo )
{

  if(novo==1)
  {
    anos[nAno].ano=ano;
    anos[nAno].artistas= (Artistas*)calloc(4,sizeof(Artistas));
    anos[nAno].horas=(int*)calloc(24,sizeof(int));
    anos[nAno].tamanhoArtistas=4;
    if (anos[nAno].horas == NULL) {
          printf("Erro ao alocar memória.\n");
        
      }
  }


  int numartistas=get_numArtists(musicController ,musicId);
  int* artistId=getArtistIdMusic(musicController ,musicId); 

  anos=adicionaArtista(anos,artistId, numartistas,duracao, musicId, nAno,novo);
  
  char* genero= get_musicGenre(musicController ,musicId);
  anos=insereGenero(genero,anos,duracao,nAno,novo);
  int albumId= get_musicAlbum(musicController ,musicId);
  anos=insereAlbum(albumId,anos,duracao,nAno,novo);
  anos[nAno].horas[hora]+=1; 
  anos=insereDia(mes,dia,anos ,nAno,novo);
  return anos;


}

History* inicializaUserHistory(int userId,MusicData* musicData,int musicId,int ano,int mes,int dia,int hora,int duration)
{
  
  History* userHistory= malloc(sizeof(History));
  userHistory->anos=calloc(4 , sizeof(Ano));
  userHistory->id=userId; 
  userHistory->nAnos=1;
  userHistory->tamanhoArray=4;   
  userHistory->anos= adicionarAno(musicData , userHistory->anos,  musicId,  ano,mes, dia, hora, duration,0,1);
 
  return userHistory;

}


void adicionaUserHistory(History* userHistory,MusicData* musicData,int musicId,int ano,int dia,int mes, int hora,int duration)
{ 

   if(userHistory->anos == NULL)
    { 
        userHistory->anos=adicionarAno(musicData,userHistory->anos, musicId,ano,mes,dia,hora , duration,0,1);
         
    }
    else
    { 
      
        int anoPosicao=procuraAno(userHistory, ano); 
         int tamanhoArray= userHistory->tamanhoArray;
         int nAnos=userHistory->nAnos; 
      
        if(nAnos>=tamanhoArray && anoPosicao==-1)
        { 
          int newSize=  userHistory->tamanhoArray*2;
          userHistory->anos= realloc(userHistory->anos, newSize* sizeof(Ano));
           userHistory->tamanhoArray*=2;
        }

        if(anoPosicao==-1)
        {
       
           userHistory->anos=adicionarAno(musicData ,userHistory->anos,  musicId,ano,mes,dia,hora , duration,nAnos,1);
           userHistory->nAnos++;

        }
        else
        {
         
            userHistory->anos=adicionarAno(musicData ,userHistory->anos,  musicId,ano,mes,dia,hora , duration,anoPosicao,0);
            
        }
            
       
    }
    
    }

void freeUserHistory(History* history)
{
  for(int i=0;i<history->nAnos;i++)
  {

printf("freeing ");
    for (int j = 0; j < history->anos[i].nArtistas; j++) {
            if (history->anos[i].artistas[j].musicas) {
                free(history->anos[i].artistas[j].musicas);
            }
    }

    free(history->anos[i].artistas);

    if(history->anos[i].album)free(history->anos[i].album);
  
    for (int j = 0; j < history->anos[i].nGeneros; j++) {
    
        if (history->anos[i].genero[j].genero) {
            free(history->anos[i].genero[j].genero);
        }
    }   

    if(history->anos[i].genero)free(history->anos[i].genero);
    if(history->anos[i].dia)free(history->anos[i].dia);
    if(history->anos[i].horas)free(history->anos[i].horas);

  }
  //printf("freed\n");
  if(history->anos)free(history->anos);
  free(history);
}

void freeArtistas( Artistas* artista)
{
    free(artista->musicas);
    free(artista);
}

void freeUmArtista (UmArtista* artista){
  if(artista == NULL){
    return;
  } 
  free(artista);
}


void freeDomingo(Domingo* domingo) {
    free(domingo->data);  
        
        g_hash_table_destroy(domingo->artistahistory); 

    free(domingo);
}


void destroy_history(Domingo* domingo) {
  
        free(domingo->data);  
        
        g_hash_table_destroy(domingo->artistahistory); 
    
}






Domingo* newDomingo(char* data){
   // Aloca memória para a estrutura
    Domingo* novo_domingo = malloc(sizeof(Domingo));
    if (!novo_domingo) {
        fprintf(stderr, "Erro ao alocar memória para Domingo\n");
        return NULL;
    }

    //Ver se é realmente preciso um strdup
    novo_domingo->data = strdup(data); // Duplica a string passada como parâmetro
  //GHashTable* Domingo =g_hash_table_new_full(g_int_hash, g_int_equal, free, (GDestroyNotify)freeUser);

    // Cria a hash table para armazenar o histórico dos artistas
    novo_domingo->artistahistory = g_hash_table_new_full(g_int_hash, g_int_equal, free, (GDestroyNotify)freeUmArtista);

    return novo_domingo;
}

/* Tokens:
TOken[0] = history_id
token[1] = user_id
token[2] = music_id
token[3] = timestramp
token[4] = duration hh:mm:ss
token[5] = platafomra
*/

UmArtista* new_umArtista (int artist_id, int segundos){
  UmArtista* n_umart = malloc(sizeof(UmArtista));
  
  if (n_umart == NULL) {
        fprintf(stderr, "Memory allocation failed for novo UMArtista\n");
        exit(1);
    }

          // Artista ainda não existe na tabela, crie um novo registro
  n_umart->artist_id = artist_id;
  n_umart->totalsemanalsegundos = segundos; // Inicialize o valor

  return n_umart;  
}


void inserir_umartista_na_semana(GHashTable* artisthistory, UmArtista* novo_artista, int artist_id){
   // printf("INSERIR ARTISTA NA SEMANA!");
    
    
    int* key = malloc(sizeof(int));  // Aloca memória para a chave
    *key = artist_id;

    g_hash_table_insert(artisthistory, key, novo_artista);

}

GHashTable* get_artisthistorido_dedomingo (Domingo* domingo){
  return domingo->artistahistory;
}


UmArtista* lookup_artista_historico(GHashTable* Artista, int artist_id){
  return g_hash_table_lookup(Artista, &artist_id);

}


// Função para adicionar um artista ao Domingo
void new_or_add(Domingo* domingo, char** tokens, MusicData* musicController) {
  //transforma o char music_id em int para conseguir encontrar a estrutura Music 
    int music_id = transformaIds(tokens[2]);

    Music* musicadoartista = lookup_musica(musicController, music_id);

    int numartistas = get_numArtistsId(musicadoartista);

    //array de artistas que constituem essa musica
    int* arrayartistas = getArtistIDfromMuiscID(musicadoartista);
    

    GHashTable* artistahistory = domingo->artistahistory;
    if (!artistahistory) {
        fprintf(stderr, "Erro: artistahistory é NULL.\n");
        return;
    }

    char* segundosparaadicionar = remove_quotes(tokens[4]);
  

    int segundos = duration_to_seconds(segundosparaadicionar);

    //É PRECISO ALTERAR PARA QUANDO O NUMARTISTA É 0 ISTO É QUANDO NAO É UM GRUPO
    if(numartistas > 0){
    for (int i = 0; i < numartistas; i++) {
        int artist_id = arrayartistas[i];

        UmArtista* artist_data = lookup_artista_historico(artistahistory, artist_id);

        if (!artist_data) {

            UmArtista* novo_artista = new_umArtista(artist_id, segundos);
            inserir_umartista_na_semana(artistahistory, novo_artista, artist_id);
        } else {

            artist_data->totalsemanalsegundos += segundos;
        }
    }

    }
    free(arrayartistas);
    free(segundosparaadicionar);
}




GHashTable* getArtistHistory(Domingo* domingo){
  return(domingo->artistahistory);
}








//FUNCOES PRINTS QUE NAO FUNCIONAM
void print_artisthistory (UmArtista* artista) {
    if (artista) {
        printf("ARTIST_ID: %d\n", artista->artist_id);
        printf("TOTAL_SEGUNDOS: %d\n", artista->totalsemanalsegundos);
    } else {
        fprintf(stderr, "Erro: ESTE UMARTISTA NAO EXISTE\n");
    }
}


void printf_domingo (Domingo* domingo) {
    if (domingo) {
        if (domingo->data) {
            printf("DATA: %s\n", domingo->data);
        } else {
            fprintf(stderr, "Erro: DATA do Domingo é NULL\n");
        }
    } else {
        fprintf(stderr, "Erro: ESTA DOMINGO NAO EXISTE\n");
    }
}


void print_artisthistory_entry(gpointer key, gpointer value, gpointer user_data) {
    if (key == NULL || value == NULL) {
        fprintf(stderr, "Erro: Chave ou valor nulo encontrado.\n");
        return;
    }

    (void)user_data; // Ignora user_data, se não for usado

    printf("Processando artista com chave: %p\n", key); // Log da chave
    UmArtista* artista = (UmArtista*)value;

    print_artisthistory(artista);
}


void print_semana_completa(Domingo* domingo) {
    if (domingo == NULL) {
        fprintf(stderr, "Erro: Domingo é NULL.\n");
        return;
    }

    if (get_artisthistorido_dedomingo(domingo)== NULL) {
        fprintf(stderr, "Erro: Hash Table artistahistory é NULL.\n");
        return;
    }


    printf("----- Hash Table DOMINGO da semana %s -----\n", domingo->data);

    g_hash_table_foreach(get_artisthistorido_dedomingo(domingo), print_artisthistory_entry, NULL);

    printf("----- Fim da Hash Table DOMINGO da semana %s -----\n", domingo->data);
}
