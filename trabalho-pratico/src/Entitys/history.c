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
  GArray* genero;
  int nGeneros;
  GArray* album;
  int nAlbuns;
  int* horas;
  GArray* dia;
  int nDias;
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

 printf("Inicio \n");
    printf("ID do utilizador: %d\n", userHistory->id);
    printf("Número de anos registrados: %d\n", userHistory->nAnos);

    for (int i = 0; i < userHistory->nAnos; i++) {
        Ano* ano = &userHistory->anos[i];
        printf("\nAno: %d\n", ano->ano);

        printf("Número de artistas: %d\n", ano->nArtistas);
        for (int j = 0; j < ano->nArtistas; j++) {
            Artistas* artista = ano->artistas;
            printf("  Artista ID: %d, Tempo de audição: %d, Número de músicas: %d\n", 
                   artista[j].artista, artista[j].tempoAudicao, artista[j].nMusicas);
            printf("  Músicas: ");
            for (int k = 0; k < artista[j].nMusicas ;k++) {
                printf("%d ", artista[j].musicas[k]);
            }
            printf("\n");
        }

        printf("\nNúmero de géneros: %d\n", ano->nGeneros);
        Generos* generos =( Generos*) ano->genero->data;
        Generos genero;
        for (int j = 0; j < ano->nGeneros; j++) {
           genero= generos[j];
            printf("  Género: %s, Tempo de audição: %d\n", 
                   genero.genero, genero.tempoAudicao);
        }
            
            Albuns* albums =(Albuns*) ano->album->data;
            Albuns album;
        printf("\nNúmero de álbuns: %d\n", ano->nAlbuns);
        for (int j = 0; j < ano->nAlbuns; j++) {
          album = albums[j];
            printf("  Álbum ID: %d, Tempo de audição: %d\n", 
                   album.album, album.tempoAudicao);
        }

        printf("\nHoras por ano:\n");
        for (int j = 0; j < 24; j++) { // Supondo que o array `horas` tem tamanho 12 para os meses do ano
            printf("  Hora %d: nº :%d \n", j + 1, ano->horas[j]);
        }
         Dia* dias = (Dia*) ano->dia->data;
        Dia dia;
        printf("\nNúmero de dias: %d\n", ano->nDias);
        for (int j = 0; j < ano->nDias; j++) {
           dia=dias[j];
            printf("  Dia: %d/%d, Número de músicas: %d\n", 
                   dia.dia, dia.mes, dia.nMusicas);
        }
    }
    printf("FIM \n");
}

int IdArtista(History* userHistory, int ano, int i)
{
  printf("%d\n",i);
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
  char resultados[256];
  snprintf(resultados,256,"%d %d %d",artistaId,nMusicas ,tempoTotal);

  return strdup(resultados);
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
  char horaMais[3];
  if(hora<10)
  {
    snprintf(horaMais,3,"0%d",hora);
  }
  else
  {
    snprintf(horaMais,3,"%d",hora);
  }
  return strdup(horaMais);
}

int AlbumFavorito(History* userHistory,int anoP, AlbumsData* albumController)
{
  Albuns* albuns=(Albuns*) userHistory->anos[anoP].album->data;
  int N= userHistory->anos[anoP].album->len;
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
  Generos* generos=(Generos*) userHistory->anos[anoP].genero->data;
  int N= userHistory->anos[anoP].genero->len;
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
    char data[13];
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
       snprintf(data,11,"%d/%d/%d",ano,mes,dia);
    }
    return strdup(data);
}


char* DataMaisMusicas(History* userHistory,int anoP)
{
   Dia* dias=(Dia*) userHistory->anos[anoP].dia->data;
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

int procuraAno(History* userHistory, int anos)
{
int anoP=-1;

 for(int i=0; i<userHistory->nAnos ;i++){
 
  if(userHistory->anos[i].ano == anos )
  {
    
        return i;
  }
 }
 return anoP;
}




Ano* insereGenero(char* genero, Ano* ano, int tempo, int nAno, int novo) {
    if (novo == 1) {
        //  GArray para os generos do ano
        ano[nAno].genero = g_array_new(FALSE, FALSE, sizeof(Generos));

        // Adicionando o primeiro gênero
        Generos novoGenero = { .genero = genero, .tempoAudicao = tempo };
        g_array_append_val(ano[nAno].genero, novoGenero);
        ano[nAno].nGeneros=1;

    } else {
        int i;
        Generos* generos = (Generos*) ano[nAno].genero->data;
        int N = ano[nAno].genero->len;
        // Procurando o gênero no array
        for (i = 0; i < N && strcmp(genero, generos[i].genero) != 0; i++) {}

        if (i < N) {
            // Gênero encontrado, atualiza o tempo de audição
            generos[i].tempoAudicao += tempo;
        } else {
            // Gênero não encontrado, adiciona um novo
            Generos novoGenero = { .genero = genero, .tempoAudicao = tempo };
            g_array_append_val(ano[nAno].genero, novoGenero);
            ano[nAno].nGeneros++;
        }
    }
    return ano;
}

Ano* insereAlbum(int albumID, Ano* ano, int tempo, int nAno, int novo) {
    if (novo == 1) {
        // Criando uma nova GArray para os álbuns
        ano[nAno].album = g_array_new(FALSE, FALSE, sizeof(Albuns));

        // Adicionando o primeiro álbum
        Albuns novoAlbum = { .album = albumID, .tempoAudicao = tempo };
        g_array_append_val(ano[nAno].album, novoAlbum);
        ano[nAno].nAlbuns=1;
    } else {
        int i;
        Albuns* albuns = (Albuns*) ano[nAno].album->data;
        int N = ano[nAno].album->len;

        // Procurando o álbum no array
        for (i = 0; i < N && albumID != albuns[i].album; i++) {}

        if (i < N) {
            // Álbum encontrado, atualiza o tempo de audição
            albuns[i].tempoAudicao += tempo;
        } else {
            // Álbum não encontrado, adiciona um novo
            Albuns novoAlbum = { .album = albumID, .tempoAudicao = tempo };
            g_array_append_val(ano[nAno].album, novoAlbum);
            ano[nAno].nAlbuns++;
        }
    }
    return ano;
}



Ano* insereDia(int mes, int dia, Ano* ano, int nAno, int novo) {
    if (novo == 1) {
        // Criando uma nova GArray para os dias
        ano[nAno].dia = g_array_new(FALSE, FALSE, sizeof(Dia));
      
        // Adicionando o primeiro dia
        Dia novoDia = { .dia = dia, .mes = mes, .nMusicas = 1 };
        g_array_append_val(ano[nAno].dia, novoDia);
        ano[nAno].nDias=1;

    } else {
        int i;
        Dia* dias = (Dia*) ano[nAno].dia->data;
        int N = (int) ano[nAno].dia->len;

        // Procurando o dia no array
        for (i = 0; i < N && (dia != dias[i].dia || mes != dias[i].mes); i++) {}

        if (i < N) {
            // Dia encontrado, incrementa o número de músicas
            dias[i].nMusicas++;
        } else {
            // Dia não encontrado, adiciona um novo
            Dia novoDia = { .dia = dia, .mes = mes, .nMusicas = 1 };
            g_array_append_val(ano[nAno].dia, novoDia);
            ano[nAno].nDias++;
        }
    }
    return ano;
}


int procura_Artista(Artistas* artistas,int N, int artistId)
{
  int i;
  for(i=0;i<N;i++)
  {
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
           
              ANO[nAno].artistas=realloc( ANO[nAno].artistas,(2+ANO[nAno].tamanhoArtistas) * sizeof(Artistas));
              ANO[nAno].tamanhoArtistas+=2;

          } 

          ANO[nAno].artistas= novoArtista(ANO[nAno].artistas, artistId[i], musicId,duracao,ANO[nAno].nArtistas);
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
    anos[nAno].horas=(int*)calloc(24,sizeof(int));
    if (anos[nAno].horas == NULL) {
          printf("Erro ao alocar memória.\n");
        
      }
  }


  int numartistas=get_numArtists(musicController ,musicId);
  int* artistId=getArtistIdMusic(musicController ,musicId); 
 
  anos=adicionaArtista(anos,artistId, numartistas,duracao, musicId, nAno,novo);
  free(artistId);
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
 userHistory->anos=calloc(20 , sizeof(Ano));
  userHistory->id=userId; 
  userHistory->nAnos=1;
  userHistory->tamanhoArray=20;   
  userHistory->anos= adicionarAno(musicData , userHistory->anos,  musicId,  ano,mes, dia, hora, duration,0,1);
  
  // if(userHistory->id==69463){
  //          printf("1 \n");
  //         printUserHistory(userHistory);
         
  //        } 
  return userHistory;

}


void adicionaUserHistory(History* userHistory,MusicData* musicData,int musicId,int ano,int dia,int mes, int hora,int duration)
{ 

   if(userHistory->anos == NULL)
    { 
        userHistory->anos=adicionarAno(musicData,userHistory->anos, musicId,ano,mes,dia,hora , duration,0,1);
         userHistory->nAnos=1;
        //  if(userHistory->id==69463)  {
        //    // printf("34\n");
        //    // printUserHistory(userHistory);
         
        //  } 
    }
    else
    { 
      
        int anoPosicao=procuraAno(userHistory, ano); 
      //  if(anoPosicao == 1) printf("AnoP %d \n",anoPosicao); 
      //   if(userHistory->id == 69463) 
      //   {
      //     printf(" AnoP%d \n",anoPosicao); 
      //   }
         int tamanhoArray= userHistory->tamanhoArray;
         int nAnos=userHistory->nAnos; 
      
        if(nAnos>=tamanhoArray && anoPosicao==-1)
        { printf("Realloc\n");
          int newSize=  userHistory->tamanhoArray+2;
          userHistory->anos= realloc(userHistory->anos, newSize* sizeof(Ano));
           userHistory->tamanhoArray+=2;
        }
       
         if(userHistory->id==69463) printf(" Ano Posicao: %d\n",anoPosicao); 
        if(anoPosicao==-1)
        {
       
           userHistory->anos=adicionarAno(musicData ,userHistory->anos,  musicId,ano,mes,dia,hora , duration,nAnos,1);
           userHistory->nAnos++;
        //  if(userHistory->id==69463) 
        //   {   
        //     printf("2\n");
        //       printUserHistory(userHistory);
        //   } 

       }
        else
        {
          // printf("%d \n", userHistory->id);
          // printf("%d \n", userHistory->nAnos);
            userHistory->anos=adicionarAno(musicData ,userHistory->anos,  musicId,ano,mes,dia,hora , duration,anoPosicao,0);
             
            //  if(userHistory->id==69463) 
            //  {
            //     printf("3 \n");
            //     printUserHistory(userHistory);
            // } 
           
        }
            
       
    }
    
    }

void freeUserHistory(History* history)
{
  for(int i=0;i<history->nAnos;i++)
  {


    for (int j = 0; j < history->anos[i].nArtistas; j++) {
            if (history->anos[i].artistas[j].musicas) {
                free(history->anos[i].artistas[j].musicas);
            }
    }

    free(history->anos[i].artistas);

    if(history->anos[i].album)free(history->anos[i].album);
  
    if (history->anos[i].genero) {
            Generos* generos = (Generos*) history->anos[i].genero->data;
            for (guint j = 0; j < history->anos[i].genero->len; j++) {
                free(generos[j].genero); // Liberar a string (se foi alocada dinamicamente)
            }
            g_array_free(history->anos[i].genero, TRUE);
        }

   if (history->anos[i].album) {
            g_array_free(history->anos[i].album, TRUE);
        }

        // Liberar os dias
        if (history->anos[i].dia) {
            g_array_free(history->anos[i].dia, TRUE);
        }
    if(history->anos[i].horas)free(history->anos[i].horas);

  }

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
