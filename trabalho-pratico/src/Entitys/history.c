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

struct artistahistory
{
  int artist_id;
  int totalsemanalsegundos; // passar a duration de hh:mm:ss (funcao defenida nas utilities)
};

struct domingo
{
  char *data;
  GHashTable *artistahistory;
};

struct artista
{
  int artista;
  int *musicas;
  int nMusicas;
  int tamanho;
  int tempoAudicao;
};

struct genero
{
  char *genero;
  int tempoAudicao;
};

struct album
{
  int album;
  char* albumName;
  int tempoAudicao;
};
struct hora
{
  int hora;
  int tempoAudicao;
};
struct dia
{
  int dia;
  int mes;
  int nMusicas;
};

struct musica
{
  int musicId;
  int tempoAudicao;
};
struct ano
{
  int ano;
  GArray *artistas;
  GArray* musicas;
  GArray *horas;
  GArray *dia;
};

struct userHistory
{
  int id;
  GArray *anos;
};

// void printUserHistory(History *userHistory)
// {
//   if (userHistory == NULL)
//   {
//     printf("Histórico de utilizador não encontrado.\n");
//     return;
//   }

//   printf("Inicio \n");
//   printf("ID do utilizador: %d\n", userHistory->id);
//   printf("Número de anos registrados: %d\n", userHistory->anos->len);

//   for (int i = 0; i <(int) userHistory->anos->len; i++)
//   {
//     Ano* ano=&g_array_index(userHistory->anos,Ano,i);
//     printf("\nAno: %d\n", ano->ano);

//     printf("Número de artistas: %d\n", ano->artistas->len);
//     for (int j = 0; j <(int) ano->artistas->len; j++)
//     {
//       Artistas* artista =&g_array_index(ano->artistas, Artistas,j) ;
//       printf("  Artista ID: %d, Tempo de audição: %d, Número de músicas: %d\n",
//              artista->artista, artista->tempoAudicao, artista->musicas->len);
//       printf("  Músicas: ");
//       int* musicas= (int*)artista->musicas->data;
//       for (int k = 0; k < (int)artista->musicas->len; k++)
//       {
//         printf("%d ", musicas[k]);
//       }
//       printf("\n");
//     }

//     printf("\nNúmero de géneros: %d\n", ano->genero->len);
//     Generos *generos = (Generos *)ano->genero->data;
//     Generos genero;
//     for (int j = 0; j < (int) ano->genero->len; j++)
//     {
//       genero = generos[j];
//       printf("  Género: %s, Tempo de audição: %d\n",
//              genero.genero, genero.tempoAudicao);
//     }

//     Albuns *albums = (Albuns *)ano->album->data;
//     Albuns album;
//     printf("\nNúmero de álbuns: %d\n", ano->album->len);
//     for (int j = 0; j <(int) ano->album->len; j++)
//     {
//       album = albums[j];
//       printf("  Álbum ID: %d, Tempo de audição: %d\n",
//              album.album, album.tempoAudicao);
//     }

//     printf("\nHoras:\n");
//     Hora* hour = (Hora*)ano->horas->data;
//     for (int j = 0; j < (int)ano->horas->len; j++)
//     { // Supondo que o array `horas` tem tamanho 12 para os meses do ano
//       printf("  Hora %d: nº Musicas :%d \n",hour[j].hora,hour[j].nMusicas);
//     }
//     Dia *dias = (Dia *)ano->dia->data;
//     Dia dia;
//     printf("\nNúmero de dias: %d\n", ano->dia->len);
//     for (int j = 0; j < (int)ano->dia->len ; j++)
//     {
//       dia = dias[j];
//       printf("  Dia: %d/%d, Número de músicas: %d\n",
//              dia.dia, dia.mes, dia.nMusicas);
//     }
//   }
//   printf("FIM \n");
// }

int NumArtistas(History *userHistory, int posicaoAno)
{
  Ano *ano = (Ano *)userHistory->anos->data;
  int numartistas = ano[posicaoAno].artistas->len;
  return numartistas;
}

int IdArtista(History *userHistory, int ano, int i)
{
  Ano *anos = (Ano *)userHistory->anos->data;
  Artistas *artista = (Artistas *)anos[ano].artistas->data;
  return artista[i].artista;
}

int TempoArtista(History *userHistory, int ano, int i)
{
  Ano *anos = (Ano *)userHistory->anos->data;
  Artistas *artista = (Artistas *)anos[ano].artistas->data;
  return artista[i].tempoAudicao;
}

int nMusicasArtista(History *userHistory, int ano, int i)
{
  Ano *anos = (Ano *)userHistory->anos->data;
  Artistas *artista = (Artistas *)anos[ano].artistas->data;
  int nMusicas = artista[i].nMusicas;
  return nMusicas;
}

void sort(int *artistas, Artistas *artista, int N)
{
  for (int i = 0; i < N; i++)
  {
    artistas[i] = i;
  }
  int tempo1, tempo2, id1, id2, temp;

  for (int i = 0; i < N - 1; i++)
  {
    for (int j = i + 1; j < N; j++)
    {
      tempo1 = artista[artistas[i]].tempoAudicao;
      tempo2 = artista[artistas[j]].tempoAudicao;
      id1 = artista[artistas[i]].artista;
      id2 = artista[artistas[j]].artista;

      if (tempo1 < tempo2 || (tempo1 == tempo2 && id1 > id2))
      {
        temp = artistas[i];
        artistas[i] = artistas[j];
        artistas[j] = temp;
      }
    }
  }
}

int *NartistasMaisOuvidos(History *userHistory, int pAno, int N)
{
  Ano *ano = (Ano *)userHistory->anos->data;
  Artistas *artista = (Artistas *)ano[pAno].artistas->data;
  int nArtistas = (int)ano[pAno].artistas->len;
  int *artistas = calloc(N, sizeof(int));
  if (N > nArtistas)
  {
    sort(artistas, artista, nArtistas);
  }
  else
  {
    sort(artistas, artista, N);
  }

  return artistas;
}

char *ArtistaMaisOuvido(History *userHistory, int anoP)
{
  Ano *ano = (Ano *)userHistory->anos->data;
  Artistas *artista = (Artistas *)ano[anoP].artistas->data;
  int N = (int)ano[anoP].artistas->len;
  int max = artista[0].tempoAudicao;
  int artistaId = artista[0].artista;
  int tempoTotal = max;
  int nMusicas = artista->nMusicas;

  for (int i = 1; i < N; i++)
  {
    if (max < artista[i].tempoAudicao || (max == artista[i].tempoAudicao && artistaId > artista[i].artista))
    {
      max = artista[i].tempoAudicao;
      artistaId = artista[i].artista;
    }
    tempoTotal += artista[i].tempoAudicao;
    nMusicas += artista->nMusicas;
  }
  char resultados[256];
  snprintf(resultados, 256, "%d %d %d", artistaId, nMusicas, tempoTotal);

  return strdup(resultados);
}

char* HoraMaisAudicoes(History *userHistory, int anoP)
{
  Ano *ano = (Ano *)userHistory->anos->data;
  Hora *horas = (Hora*) ano[anoP].horas->data;
  int max = horas[0].tempoAudicao;
  int hour = horas[0].hora;
  int N=ano[anoP].horas->len;
  for (int i = 1; i <N ; i++)
  {
    if (horas[i].tempoAudicao > max || (horas[i].tempoAudicao== max && hour>horas[i].hora ))
    {
      max = horas[i].tempoAudicao;
      hour = horas[i].hora;
    }
  }
  char horaMais[3];
  if (hour < 10)
  {
    snprintf(horaMais, 3, "0%d", hour);
  }
  else
  {
    snprintf(horaMais, 3, "%d", hour);
  }
  return strdup(horaMais);
}


int comparaGeneros(const void *a, const void *b)
{
  Generos* gA= (Generos*) a;
  Generos* gB= (Generos*) b;
  int tempoA=gA->tempoAudicao;
  int tempoB=gB->tempoAudicao;
  if(tempoA > tempoB || (tempoA== tempoB &&  strcmp(gA->genero, gB->genero)<0) )
  {
     return -1;
  }
  else
  {
    return 1;
  }
}

int comparaAlbuns(const void *a, const void *b)
{
  Albuns* A= (Albuns*) a;
  Albuns* B= (Albuns*) b;
  int tempoA=A->tempoAudicao;
  int tempoB=B->tempoAudicao;
  if(tempoA > tempoB || (tempoA== tempoB &&  strcmp(A->albumName, B->albumName)<0) )
  {
     return -1;
  }
  else
  {
    return 1;
  }
}

char * AlbumGenero(MusicData* musicController,History* userHistory,AlbumsData*albumController, int posicaoAno)
{
     Ano *ano = (Ano *)userHistory->anos->data;
     Musica * musicas= (Musica*) ano[posicaoAno].musicas->data;
     Generos* generos=malloc( 10*sizeof(Generos));
     Albuns* albuns=malloc( 8* sizeof(Albuns));
     int existeG;
     int existeA;
     int GInseridos=0;
     int AInseridos=0;

    for(int i=0;i<(int) ano->musicas->len;i++)
    { 
      existeG=0;
      existeA=0;
      printf("%d \n", musicas[i+2].musicId);
      char* genero=get_musicGenre(musicController, musicas[i].musicId);
      int albumID= get_musicAlbum(musicController,musicas[i].musicId);
      Album *album = lookup_album(albumController, albumID);
      char* albumNome= getAlbumName(album);
    
       for(int j=0;j< GInseridos && !existeG ;j++)
       {
        
         if(strcmp(generos[j].genero,genero)==0 && !existeG)
         {
            generos[j].tempoAudicao+= musicas[i].tempoAudicao;
            existeG=1;
         }
       } 

       for(int j=0;j<AInseridos && !existeA;j++)
       {
          if(albumID==albuns[j].album)
        {
          albuns[j].tempoAudicao+= musicas[i].tempoAudicao;
          existeA=1;
        }
       }  
       if(!existeG)
       {
         generos[GInseridos].tempoAudicao=musicas[i].tempoAudicao;
         generos[GInseridos].genero= strdup(genero);
         GInseridos+=1;
       }
       if(!existeA)
       {
         albuns[AInseridos].tempoAudicao=musicas[i].tempoAudicao;
         albuns[AInseridos].album= albumID;
         albuns[AInseridos].albumName= strdup(albumNome);
         AInseridos+=1;
       }
      free(genero);
       free(albumNome);
    }
      
    qsort(generos,GInseridos, sizeof(Generos), comparaGeneros);
    qsort(albuns, AInseridos, sizeof(Albuns),comparaAlbuns);

    char resultados[256];
    snprintf(resultados, 256, "%s%d", generos[0].genero, albuns[0].album);

      for (int i = 0; i < GInseridos; i++) {
        free(generos[i].genero);  // Liberar o campo 'genero' de cada struct
    }

    for (int i = 0; i < AInseridos; i++) {
        free(albuns[i].albumName);  // Liberar o campo 'albumName' de cada struct
    }

    // Liberar memória alocada para os arrays de structs
    free(generos);
    free(albuns);
    return strdup(resultados);
}



char *DataParaChar(int ano, int mes, int dia)
{
  char data[13];
  if (dia < 10 && mes > 10)
  {
    sprintf(data, "%d/%d/0%d", ano, mes, dia);
  }
  else if (dia >= 10 && mes < 10)
  {
    sprintf(data, "%d/0%d/%d", ano, mes, dia);
  }
  else if (dia < 10 && mes < 10)
  {
    sprintf(data, "%d/0%d/0%d", ano, mes, dia);
  }
  else if (dia >= 10 && mes >= 10)
  {
    snprintf(data, 11, "%d/%d/%d", ano, mes, dia);
  }
  return strdup(data);
}

char *DataMaisMusicas(History *userHistory, int anoP)
{
  Ano *ano = (Ano *)userHistory->anos->data;
  Dia *dias = (Dia *)ano[anoP].dia->data;
  int maior = dias[0].nMusicas;
  int dia = dias[0].dia;
  int mes = dias[0].mes;

  for (int i = 1; i < (int)ano[anoP].dia->len; i++)
  {
    if (maior < dias[i].nMusicas || (maior == dias[i].nMusicas && (mes < dias[i].mes || (mes == dias[i].mes && dia < dias[i].dia))))
    {
      dia = dias[i].dia;
      mes = dias[i].mes;
    }
  }
  char *data = DataParaChar(ano[anoP].ano, mes, dia);

  return data;
}

int procuraAno(History* history, int ano)
{
  int anoP = -1;;
  for (int i = 0; i < (int)history->anos->len; i++)
  {
    Ano* anos=&g_array_index(history->anos,Ano,i);
    if (anos->ano == ano)
    {
      return i;
    }
  }
  return anoP;
}



void insereDia(int mes, int dia, GArray* Dias, int novo)
{
  if (novo == 1)
  {
    // Adicionando o primeiro dia
    Dia novoDia = {.dia = dia, .mes = mes, .nMusicas = 1};
    g_array_append_val(Dias, novoDia);
  }
  else
  {
    int i;
    int N = (int)Dias->len;

    // Procurando o dia no array
    for (i = 0; i < N ; i++)
    {
      Dia* dias= &g_array_index(Dias,Dia,i);
      if(dia == dias->dia && mes == dias->mes)
      {
        dias->nMusicas++;
      }
    }

    if (i >= N)
    {
      // Dia não encontrado, adiciona um novo
      Dia novoDia = {.dia = dia, .mes = mes, .nMusicas = 1};
      g_array_append_val(Dias, novoDia);
    }
  }
}

int procura_Artista(Artistas *artistas, int N, int artistId)
{
  int i;
  for (i = 0; i < N; i++)
  {
    if (artistas[i].artista == artistId)
    {
      return i;
    }
  }
  return -1;
}

void adicionarMusica(Artistas *artista, int musicId, int duracao)
{
  int i;
  int nMusicas = artista->nMusicas;
  int * musicas=artista->musicas;
  int existe=0;

  for (i = 0; i < nMusicas && !existe; i++)
  {
    if(musicas[i] == musicId)
    {
      artista->tempoAudicao += duracao;
      existe=1;
    }
  }

  if (!existe)
  {

    artista->tempoAudicao += duracao;

    if(artista->tamanho<=artista->nMusicas)
    {
     artista->musicas= resize(artista->musicas,artista->tamanho,'i');
     artista->tamanho*=2;
    }
    artista->musicas[artista->nMusicas]=musicId;
    artista->nMusicas++;
  }
}


void novoArtista(GArray* artistas, int artistId, int musicId, int duracao)
{
  Artistas novoArtista = {.artista = artistId, .tempoAudicao = duracao};
  novoArtista.musicas=malloc(2*sizeof(int));
  novoArtista.musicas[0]=musicId;
  novoArtista.nMusicas=1;
  novoArtista.tamanho=2;
  g_array_append_val(artistas, novoArtista);
}

void adicionaArtista(GArray* artista, int *artistId, int numArtistas, int duracao, int musicId,  int novo)
{

  if (novo == 1)
  {
    for (int i = 0; i < numArtistas; i++)
    {
      novoArtista(artista, artistId[i], musicId, duracao);
    }

  }
  else
  {
    for (int i = 0; i < numArtistas; i++)
    {

      int N = (int)artista->len;
      int existe=0;
      for (int j = 0; j < N && !existe; j++)
      {
         Artistas *artistas = &g_array_index(artista, Artistas, j);
         if (artistas->artista == artistId[i])
         {
            adicionarMusica(artistas, musicId, duracao);
            existe=1;
         }
      }

      if (existe==0)
      {
        novoArtista(artista, artistId[i], musicId, duracao);
      }
     
    }
  }
}


void insereHora(GArray* horas,int hour,int duracao,int novo)
{
    if (novo == 1)
  {
    Hora h= {.hora = hour, .tempoAudicao = duracao};
    g_array_append_val(horas, h);
  }
  else
  {
    int i;
    int N =(int) horas->len;
    int existe=0;
    // Procurando o álbum no array
    for (i = 0; i < N && existe==0 ; i++)
    {
      Hora* h= &g_array_index(horas, Hora, i);
      if( hour == h->hora)
      {
        h->tempoAudicao+=duracao;
        existe=1;
      }
    }

    if (existe==0)
    {
      // Álbum não encontrado, adiciona um novo
      Hora h= {.hora = hour, .tempoAudicao = duracao};
      g_array_append_val(horas, h);
    }
  }
}

void insereMusica(GArray* musicas,int musicId,int duracao,int novo)
{
  if(novo==1)
  {
    Musica m={ .musicId=musicId , .tempoAudicao=duracao};
    g_array_append_val(musicas, m);
  }
  else
  {
    int i;
    int N =(int) musicas->len;
    int existe=0;
    // Procurando o álbum no array
    for (i = 0; i < N && existe==0 ; i++)
    {
      Musica* musica= &g_array_index(musicas, Musica, i);
      if( musicId == musica->musicId)
      {
        musica->tempoAudicao+=duracao;
        existe=1;
      }
    }

    if (existe==0)
    {
      Musica m={ .musicId=musicId , .tempoAudicao=duracao};
      g_array_append_val(musicas, m);   
    }
  }

  }


void adicionarAno(MusicData *musicController, GArray* Anos, int musicId, int ano, int mes, int dia, int hora, int duracao,  int novo, int posicao)
{

  Ano novoAno;
  Ano* anoAtual;

  if (novo==1)
  {
     novoAno.ano=ano;
     novoAno.horas=g_array_new(FALSE, FALSE, sizeof(Hora));
     novoAno.artistas = g_array_new(FALSE, FALSE, sizeof(Artistas));
     novoAno.musicas=g_array_new(FALSE, FALSE, sizeof(Musica));
     novoAno.dia = g_array_new(FALSE, FALSE, sizeof(Dia));
       // Adiciona o novo ano ao GArray de anos
     g_array_insert_val(Anos,posicao, novoAno);
  }
 
  anoAtual = &g_array_index(Anos, Ano, posicao);
  int numartistas = get_numArtists(musicController, musicId);
  int *artistId = getArtistIdMusic(musicController, musicId);
  adicionaArtista(anoAtual->artistas, artistId, numartistas, duracao, musicId, novo);
  free(artistId);
  insereMusica(anoAtual->musicas,musicId,duracao,novo);
  insereHora(anoAtual->horas,hora, duracao,novo);
  insereDia(mes, dia, anoAtual->dia, novo);
  
}

History *inicializaUserHistory(int userId, MusicData *musicData, int musicId, int ano, int mes, int dia, int hora, int duration)
{

  History *userHistory = malloc(sizeof(History));
  userHistory->anos = g_array_new(FALSE, FALSE, sizeof(Ano));
  adicionarAno(musicData, userHistory->anos, musicId, ano, mes, dia, hora, duration,  1, 0);
  userHistory->id = userId;
  //printUserHistory(userHistory);

  return userHistory;
}

void adicionaUserHistory(History *userHistory, MusicData *musicData, int musicId, int ano, int mes, int dia, int hora, int duration)
{
    int anoPosicao = procuraAno(userHistory, ano);
   
    if (anoPosicao == -1)
    {
       int pAno= (int) userHistory->anos->len-1;
       adicionarAno(musicData, userHistory->anos, musicId, ano, mes, dia, hora, duration, 1, pAno);
      // printUserHistory(userHistory);
    }
    else
    {
     adicionarAno(musicData, userHistory->anos, musicId, ano, mes, dia, hora, duration, 0, anoPosicao);
     //printUserHistory(userHistory);
    }
  
}

void freeUserHistory(History *history)
{
  int nAnos=(int) history->anos->len;
  Ano* anos= (Ano*) history->anos->data;
  for (int i = 0; i < nAnos; i++)
  {
    
     // Liberar artistas
     int nArtistas=(int) anos[i].artistas->len;
      GArray *artistas=anos[i].artistas;
        for (int j = 0; j < nArtistas; j++) {
            // Liberar músicas dos artistas
          Artistas *artista = &g_array_index(artistas, Artistas, j);
            if (artista->musicas) {
              //  g_array_free(artista->musicas, TRUE);
              free(artista->musicas);
            }
        }
        if (artistas) {
           g_array_free(anos[i].artistas, TRUE);
        }
   

  GArray* musica= anos[i].musicas;
  if(musica)
  {
    g_array_free(musica,TRUE);
  }

    GArray* dia= anos[i].dia;
    // Liberar os dias
    if (dia)
    {
      g_array_free(dia, TRUE);
    }
   
    GArray* hora=anos[i].horas;
     if (hora)
    {
      g_array_free(hora, TRUE);
    }
   
  }

  if (history->anos)   g_array_free(history->anos, TRUE);
  free(history);
}

void freeArtistas(Artistas *artista)
{
  free(artista->musicas);
  free(artista);
}

void freeUmArtista(UmArtista *artista)
{
  if (artista == NULL)
  {
    return;
  }
  free(artista);
}

void freeDomingo(Domingo *domingo)
{
  free(domingo->data);

  g_hash_table_destroy(domingo->artistahistory);

  free(domingo);
}

void destroy_history(Domingo *domingo)
{

  free(domingo->data);

  g_hash_table_destroy(domingo->artistahistory);
}

Domingo *newDomingo(char *data)
{
  // Aloca memória para a estrutura
  Domingo *novo_domingo = malloc(sizeof(Domingo));
  if (!novo_domingo)
  {
    fprintf(stderr, "Erro ao alocar memória para Domingo\n");
    return NULL;
  }

  // Ver se é realmente preciso um strdup
  novo_domingo->data = strdup(data); // Duplica a string passada como parâmetro
                                     // GHashTable* Domingo =g_hash_table_new_full(g_int_hash, g_int_equal, free, (GDestroyNotify)freeUser);

  // Cria a hash table para armazenar o histórico dos artistas
  novo_domingo->artistahistory = g_hash_table_new_full(g_int_hash, g_int_equal, free, (GDestroyNotify)freeUmArtista);

  return novo_domingo;
}

UmArtista *new_umArtista(int artist_id, int segundos)
{
  UmArtista *n_umart = malloc(sizeof(UmArtista));

  if (n_umart == NULL)
  {
    fprintf(stderr, "Memory allocation failed for novo UMArtista\n");
    exit(1);
  }

  // Artista ainda não existe na tabela, crie um novo registro
  n_umart->artist_id = artist_id;
  n_umart->totalsemanalsegundos = segundos; // Inicialize o valor

  return n_umart;
}

void inserir_umartista_na_semana(GHashTable *artisthistory, UmArtista *novo_artista, int artist_id)
{
  // printf("INSERIR ARTISTA NA SEMANA!");

  int *key = malloc(sizeof(int)); // Aloca memória para a chave
  *key = artist_id;

  g_hash_table_insert(artisthistory, key, novo_artista);
}

GHashTable *get_artisthistorido_dedomingo(Domingo *domingo)
{
  return domingo->artistahistory;
}

UmArtista *lookup_artista_historico(GHashTable *Artista, int artist_id)
{
  return g_hash_table_lookup(Artista, &artist_id);
}

// Função para adicionar um artista ao Domingo
void new_or_add(Domingo *domingo, char **tokens, MusicData *musicController)
{
  // transforma o char music_id em int para conseguir encontrar a estrutura Music
  int music_id = transformaIds(tokens[2]);

  Music *musicadoartista = lookup_musica(musicController, music_id);

  int numartistas = get_numArtistsId(musicadoartista);

  // array de artistas que constituem essa musica
  int *arrayartistas = getArtistIDfromMuiscID(musicadoartista);

  GHashTable *artistahistory = domingo->artistahistory;
  if (!artistahistory)
  {
    fprintf(stderr, "Erro: artistahistory é NULL.\n");
    return;
  }

  char *segundosparaadicionar = remove_quotes(tokens[4]);

  int segundos = duration_to_seconds(segundosparaadicionar);

  // É PRECISO ALTERAR PARA QUANDO O NUMARTISTA É 0 ISTO É QUANDO NAO É UM GRUPO
  if (numartistas > 0)
  {
    for (int i = 0; i < numartistas; i++)
    {
      int artist_id = arrayartistas[i];

      UmArtista *artist_data = lookup_artista_historico(artistahistory, artist_id);

      if (!artist_data)
      {

        UmArtista *novo_artista = new_umArtista(artist_id, segundos);
        inserir_umartista_na_semana(artistahistory, novo_artista, artist_id);
      }
      else
      {

        artist_data->totalsemanalsegundos += segundos;
      }
    }
  }
  free(arrayartistas);
  free(segundosparaadicionar);
}

GHashTable *getArtistHistory(Domingo *domingo)
{
  return (domingo->artistahistory);
}

// FUNCOES PRINTS QUE NAO FUNCIONAM
void print_artisthistory(UmArtista *artista)
{
  if (artista)
  {
    printf("ARTIST_ID: %d\n", artista->artist_id);
    printf("TOTAL_SEGUNDOS: %d\n", artista->totalsemanalsegundos);
  }
  else
  {
    fprintf(stderr, "Erro: ESTE UMARTISTA NAO EXISTE\n");
  }
}

void printf_domingo(Domingo *domingo)
{
  if (domingo)
  {
    if (domingo->data)
    {
      printf("DATA: %s\n", domingo->data);
    }
    else
    {
      fprintf(stderr, "Erro: DATA do Domingo é NULL\n");
    }
  }
  else
  {
    fprintf(stderr, "Erro: ESTA DOMINGO NAO EXISTE\n");
  }
}

void print_artisthistory_entry(gpointer key, gpointer value, gpointer user_data)
{
  if (key == NULL || value == NULL)
  {
    fprintf(stderr, "Erro: Chave ou valor nulo encontrado.\n");
    return;
  }

  (void)user_data; // Ignora user_data, se não for usado

  printf("Processando artista com chave: %p\n", key); // Log da chave
  UmArtista *artista = (UmArtista *)value;

  print_artisthistory(artista);
}

void print_semana_completa(Domingo *domingo)
{
  if (domingo == NULL)
  {
    fprintf(stderr, "Erro: Domingo é NULL.\n");
    return;
  }

  if (get_artisthistorido_dedomingo(domingo) == NULL)
  {
    fprintf(stderr, "Erro: Hash Table artistahistory é NULL.\n");
    return;
  }

  printf("----- Hash Table DOMINGO da semana %s -----\n", domingo->data);

  g_hash_table_foreach(get_artisthistorido_dedomingo(domingo), print_artisthistory_entry, NULL);

  printf("----- Fim da Hash Table DOMINGO da semana %s -----\n", domingo->data);
}
