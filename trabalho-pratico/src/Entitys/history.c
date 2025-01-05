#include "Entitys/musics.h"
#include "controler/musicsController.h"
#include "utilidades.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <glib.h>

#include "Entitys/history.h"
#include "Entitys/artists.h"
#include "controler/historyController.h"

struct artistahistory{
    int artist_id;
    int totalsemanalsegundos; //passar a duration de hh:mm:ss (funcao defenida nas utilities) 
};

struct domingo{
    char* data ;
    GHashTable* artistahistory; //mudar para garray
    GArray* artistahistory_garray;
};

struct artista
{
  int artista;
  int nMusicas;
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
  GArray* musicas;
  GArray *horas;
  GArray *dia;
};

struct userHistory
{
  int id;
  GArray *anos;
};



int comparaArtistas(const void *a, const void *b)
{
  Artistas* A=(Artistas*)a;
  Artistas* B=(Artistas*) b;

  int tempoA=A->tempoAudicao;
  int tempoB= B->tempoAudicao;
  int idA=A->artista;
  int idB=B->artista;
 
  if(tempoA>tempoB || (tempoA==tempoB && idA<idB ))
  {
    return -1;
  }
  else
  {
    return 1;
  }
}

int artistaMaisOuvido(GArray * artistas, int N)
{
   Artistas* artista=(Artistas*)artistas->data;
   int max=artista[0].tempoAudicao;
   int maxId=artista[0].artista;
   int tempo,id,posicao=0;
   for(int i=1;i<N;i++)
   {
     tempo=artista[i].tempoAudicao;
     id=artista[i].artista;
     if(tempo>max ||(tempo==max && id< maxId))
     {
        max=tempo;
        maxId=id;
        posicao=i;
     }
   }
   return posicao;
}


int adicionarArtista(Musica* musicas, int i, MusicData* musicController,GArray* artistas,int inseridos)
{
    int existe=0; int * Id;
    int numArtistas=getnumartistaMusicControl(musicController,musicas[i].musicId);
    Id=getarrayArtistasMusicControl( musicController, musicas[i].musicId , numArtistas);
   
   for(int k=0;k<numArtistas;k++)
   {
       for(int j=0;j<inseridos;j++)
      {
         Artistas* artista= &g_array_index(artistas,Artistas,j);
         if(artista->artista==Id[k])
         {
          artista->nMusicas++;
          artista->tempoAudicao+=musicas[i].tempoAudicao;
          existe=1;
         }
      }
      if(!existe)
      {
          Artistas novoArtista={.artista=Id[k], .nMusicas=1, .tempoAudicao=musicas[i].tempoAudicao};
          inseridos+=1;
          g_array_append_val(artistas, novoArtista);
      }
   }

   free(Id);
   return inseridos;
}


char ** resultados (int N, int inseridos, GArray * artistas, int nMusicas,int tempoTotal)
{
  char** resultados;
  if (N==0)
  {
      resultados=malloc(1 * sizeof(char*));
      resultados[0] = malloc(256 * sizeof(char));
      int posicao= artistaMaisOuvido(artistas, inseridos);
      Artistas* ARTISTA= &g_array_index(artistas,Artistas,posicao);
      snprintf(resultados[0], 256, "%d %d %d", ARTISTA->artista ,nMusicas,tempoTotal);
  }
  else if (N > inseridos)
  {
      resultados = malloc((inseridos+1) * sizeof(char*));
      Artistas* ARTISTA=(Artistas*) artistas->data;
      qsort(ARTISTA,inseridos, sizeof(Artistas),  comparaArtistas);
      for(int i=0;i<inseridos;i++)
      {
        resultados[i]=malloc(256 * sizeof(char));
        snprintf(resultados[i], 256, "%d %d %d", ARTISTA[i].artista ,ARTISTA[i].nMusicas,ARTISTA[i].tempoAudicao);
      }
      resultados[inseridos]=NULL;
  }
  else 
 {
     resultados = malloc((N+1) * sizeof(char*));
     Artistas* ARTISTA=(Artistas*) artistas->data;
     qsort(ARTISTA,inseridos, sizeof(Artistas),  comparaArtistas);
     for(int i=0;i<N;i++)
     {
        resultados[i]=malloc(256 * sizeof(char));
        snprintf(resultados[i], 256, "%d %d %d", ARTISTA[i].artista ,ARTISTA[i].nMusicas,ARTISTA[i].tempoAudicao);
     }
     resultados[N]=NULL;
  }
  g_array_free(artistas,TRUE);
  return resultados;
}

char**NartistasMaisOuvidos(History *userHistory, MusicData* musicController, int pAno, int N)
{
  Ano *ano = (Ano *)userHistory->anos->data;
  Musica *musica= (Musica *)ano[pAno].musicas->data;
  int nMusicas = (int)ano[pAno].musicas->len;
  GArray* artistas= g_array_new(FALSE, FALSE, sizeof(Artistas));
  int Ainseridos=0;
  int tempoTotal=0; 
  for(int i=0;i<nMusicas;i++)
  {
     tempoTotal+=musica[i].tempoAudicao;
     Ainseridos= adicionarArtista(musica, i, musicController, artistas, Ainseridos);
  }
  if (N==0)
  {    
      return resultados(N,Ainseridos ,artistas, nMusicas,tempoTotal);
  }
  else
  {
     return resultados(N,Ainseridos,artistas, nMusicas,tempoTotal);
  }
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

  int adicionaGenero(Musica* musicas ,int i, MusicData* musicController, GArray* generos,int inseridos)
  {
    char* genero=getMusicGenreControl(&( musicas[i].musicId), musicController, 'i');
    int existe=0;

     for(int j=0;j< inseridos && !existe ;j++)
       {
         Generos* genre= &g_array_index(generos,Generos,j);
         if(strcmp(genre->genero,genero)==0 && !existe)
         {
            genre->tempoAudicao+= musicas[i].tempoAudicao;
            existe=1;
         }
       } 
       if(!existe)
       {
        Generos novoGenero={ .tempoAudicao= musicas[i].tempoAudicao, .genero= strdup(genero)};
         inseridos+=1;
         g_array_append_val(generos, novoGenero);
       }

  free(genero);
  return inseridos;
}

int adicionaAlbum( Musica* musicas, int i, MusicData* musicController, AlbumsData* albumController, GArray* albuns, int inseridos)
{
       int albumID= get_musicAlbum(musicController,musicas[i].musicId);
       char* albumNome= get_Album_Name(albumController, albumID);
       int existe=0;
       for(int j=0;j<inseridos && !existe;j++)
       {
          Albuns* ALBUM =&g_array_index(albuns,Albuns,j);
          if(albumID==  ALBUM->album)
          {
             ALBUM->tempoAudicao+= musicas[i].tempoAudicao;
             existe=1;
          }
       }  
     
       if(!existe)
       {
          Albuns novoAlbum={ .tempoAudicao= musicas[i].tempoAudicao, .album=albumID, .albumName=strdup(albumNome)};
          inseridos+=1;
          g_array_append_val(albuns,novoAlbum);
       }

       free(albumNome);
       return inseridos;
}

void freeGenero_Album(GArray * array, int N, char type)
{
    if(type=='g')
    {
        for (int i = 0; i < N; i++)
        {
          Generos* generos=&g_array_index(array, Generos,i );
          free(generos->genero); 
        }
        g_array_free(array,TRUE);
    }
    else if (type=='a')
    {
        for (int i = 0; i < N; i++) 
        {
          Albuns * albuns=&g_array_index(array, Albuns,i );
          free(albuns->albumName);
        }
        g_array_free(array,TRUE);
    }
}

char * AlbumGenero(MusicData* musicController,  History* userHistory,AlbumsData* albumController, int posicaoAno)
{
     Ano *ano = (Ano *)userHistory->anos->data;
     Musica * musicas= (Musica*) ano[posicaoAno].musicas->data;
     GArray* generos=g_array_new(FALSE, FALSE, sizeof(Generos));
     GArray* albuns=g_array_new(FALSE, FALSE, sizeof(Albuns));
     int GInseridos=0;
     int AInseridos=0;
   
     for(int i=0;i<(int)ano[posicaoAno].musicas->len ;i++)
     { 
        GInseridos= adicionaGenero(musicas, i, musicController, generos, GInseridos);
        AInseridos= adicionaAlbum(musicas,i, musicController,albumController, albuns, AInseridos);    
     }

     Generos* GENERO= (Generos*)generos->data;
     Albuns* ALBUNS=(Albuns*) albuns->data;
     qsort(GENERO,GInseridos, sizeof(Generos), comparaGeneros);
     qsort(ALBUNS, AInseridos, sizeof(Albuns),comparaAlbuns);
     char resultados[256];
     snprintf(resultados, 256, "%d%s" ,ALBUNS[0].album, GENERO[0].genero);
     freeGenero_Album(generos, GInseridos, 'g');
     freeGenero_Album(albuns, AInseridos, 'a');

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
      maior= dias[i].nMusicas;
    }
  }
  char *data = DataParaChar(ano[anoP].ano, mes, dia);
  return data;
}

int procuraAno(History* history, int year)
{
  int anoP = -1;;
  for (int i = 0; i < (int)history->anos->len; i++)
  {
    Ano* anos=&g_array_index(history->anos,Ano,i);
    if (anos->ano == year)
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
    Dia novoDia = {.dia = dia, .mes = mes, .nMusicas = 1};
    g_array_append_val(Dias, novoDia);
  }
  else
  {
    int i;
    int N = (int)Dias->len;

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
      Dia novoDia = {.dia = dia, .mes = mes, .nMusicas = 1};
      g_array_append_val(Dias, novoDia);
    }
  }
}

void freeUmArtista (UmArtista* artista){
    if(artista == NULL){
        return;
    } 
    free(artista);
}

// Função para libertar o GArray e seus dados
void free_garray_with_data(GArray* array) {
    if (array != NULL) {
        // Itera sobre o GArray e liberta cada elemento
        guint i;
        for (i = 0; i < array->len; i++) {
            UmArtista* artista = g_array_index(array, UmArtista*, i);
            freeUmArtista(artista);  // Liberta os dados (cada UmArtista)
        }
        g_array_free(array, FALSE);  
    }
}

void free_garray_with_data2(GArray* array) {
    if (array != NULL) {
        // Itera sobre o GArray e liberta cada elemento
        guint i;
        for (i = 0; i < array->len; i++) {
            UmArtista* artista = g_array_index(array, UmArtista*, i);
            freeUmArtista(artista);  // Liberta os dados (cada UmArtista)
        }
        g_array_free(array, TRUE);  
    }
}

void freeDomingo(Domingo* domingo) {
    free(domingo->data);  

    for (guint i = 0; i < domingo->artistahistory_garray->len; i++) {
    // Obter o ponteiro para UmArtista no índice i
    UmArtista* artista = g_array_index(domingo->artistahistory_garray, UmArtista*, i);

    // Libertar a estrutura com a função específica
    freeUmArtista(artista);
    }
    // Libertar o GArray
    g_array_free(domingo->artistahistory_garray, TRUE);
    free(domingo);

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
      Hora h= {.hora = hour, .tempoAudicao = duracao};
      g_array_append_val(horas, h);
    }
  }
}

void insereMusica(GArray* musicas,int musicId,int duracao,int novo)
{
  int existe=0;
  if(novo==1)
  {
    Musica m={ .musicId=musicId , .tempoAudicao=duracao};
    g_array_append_val(musicas, m);
  }
  else
  {
    int i;
    int N =(int) musicas->len;
    
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


void adicionarAno( GArray* Anos, int musicId, int ano, int mes, int dia, int hora, int duracao,  int novo, int posicao)
{
  Ano novoAno;
  Ano* anoAtual;

  if (novo==1)
  {
     novoAno.ano=ano;
     novoAno.horas=g_array_new(FALSE, FALSE, sizeof(Hora));
     novoAno.musicas=g_array_new(FALSE, FALSE, sizeof(Musica));
     novoAno.dia = g_array_new(FALSE, FALSE, sizeof(Dia));

     g_array_insert_val(Anos,posicao, novoAno);
  }
 
  anoAtual = &g_array_index(Anos, Ano, posicao);
  insereMusica(anoAtual->musicas,musicId,duracao,novo);
  insereHora(anoAtual->horas,hora, duracao,novo);
  insereDia(mes, dia, anoAtual->dia, novo);

}


Domingo* newDomingo(char* data){
   // Aloca memória para a estrutura
    Domingo* novo_domingo = malloc(sizeof(Domingo));
    if (!novo_domingo) {
        fprintf(stderr, "Erro ao alocar memória para Domingo\n");
        return NULL;
    }

    novo_domingo->data = strdup(data); // Duplica a string passada como parâmetro

    // Cria a hash table para armazenar o histórico dos artistas   
    novo_domingo->artistahistory = g_hash_table_new_full(g_int_hash, g_int_equal, NULL, (GDestroyNotify)freeUmArtista);

    novo_domingo->artistahistory_garray = g_array_new(FALSE, FALSE, sizeof(UmArtista*));
  
    return novo_domingo;
}


  History *inicializaUserHistory(int userId,  int musicId, int ano, int mes, int dia, int hora, int duration)
{
    History *userHistory = malloc(sizeof(History));
    userHistory->anos = g_array_new(FALSE, FALSE, sizeof(Ano));
    adicionarAno( userHistory->anos, musicId, ano, mes, dia, hora, duration,  1, 0);
    userHistory->id = userId;
    return userHistory;
}


void adicionaUserHistory(History *userHistory,  int musicId, int ano, int mes, int dia, int hora, int duration)
{
    int anoPosicao = procuraAno(userHistory, ano);

    if (anoPosicao == -1)
    {
       int pAno= (int) userHistory->anos->len;
       adicionarAno( userHistory->anos, musicId, ano, mes, dia, hora, duration, 1, pAno);
    }
    else
    {
       adicionarAno( userHistory->anos, musicId, ano, mes, dia, hora, duration, 0, anoPosicao);
    }
  
}

void freeUserHistory(History *history)
{
  int nAnos=(int) history->anos->len;
  Ano* anos= (Ano*) history->anos->data;

  for (int i = 0; i < nAnos; i++)
  {
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




UmArtista* new_umArtista (int artist_id, int segundos){
    UmArtista* n_umart = malloc(sizeof(UmArtista)); 

    if (n_umart == NULL) {
        fprintf(stderr, "Memory allocation failed for novo UMArtista\n"); //this is line 123
        exit(1);
    }
    // Artista ainda não existe na tabela, cria um novo registro
    n_umart->artist_id = artist_id;
    n_umart->totalsemanalsegundos = segundos;

    return n_umart;  
}


//Função para inserir um novo artista na Hash Table
void inserir_umartista_na_semana(GHashTable* artisthistory, UmArtista* novo_artista, int artist_id){
    
    int* key = malloc(sizeof(int));  
    *key = artist_id;

    g_hash_table_insert(artisthistory, key, novo_artista);

}



int get_seconds_from_garray (UmArtista* artista){
    return artista->totalsemanalsegundos;
}


gint compare_seconds(gconstpointer a, gconstpointer b) {
    
    UmArtista *artist_a = *(UmArtista **)a;
    UmArtista *artist_b = *(UmArtista **)b;

    int segundos_a = get_seconds_from_garray(artist_a);
    int segundos_b = get_seconds_from_garray(artist_b);

    // Compara pela duração em segundos (ordem decrescente)
    int r = segundos_b - segundos_a;

    // Se os segundos forem iguais, compara pelo artist_id para ficar com o de menor id 
    if (r == 0) {
        r = artist_a->artist_id - artist_b->artist_id;
    }

    return r;
}


void passa_Domingo_para_garray(Domingo* domingo) {
    if (domingo == NULL || domingo->artistahistory == NULL || domingo->artistahistory_garray == NULL) {
        return;
    }

    // Limpa o GArray antes de começar
    g_array_set_size(domingo->artistahistory_garray, 0); 

    GHashTableIter iter;
    gpointer key, value;
    //pega no domingo e vai começar a iterar por ele
    g_hash_table_iter_init(&iter, domingo->artistahistory);

    while (g_hash_table_iter_next(&iter, &key, &value)) {

        UmArtista* artist = value; //resolvido

        if(artist == NULL){
            free(key); // Liberta a chave se o artista for ignorado
            continue;
        }

        if (artist->totalsemanalsegundos == 0) { // se o tempo for 0 o artista é ignorado porque nao vale a pena ele ocupar espaço
            free(key); // Liberta a chave se o artista for ignorado
            continue;
        }

        UmArtista* artist_to_filter = new_umArtista(artist->artist_id, artist->totalsemanalsegundos); //novo leak

        g_array_append_val(domingo->artistahistory_garray, artist_to_filter);
        free(key); //liberta a chave para ele ir para o proximo
    }
    g_hash_table_destroy(domingo->artistahistory);
    domingo->artistahistory = NULL;

    // Ordena o GArray
    g_array_sort(domingo->artistahistory_garray, (GCompareFunc)compare_seconds);

    // Remove elementos excedentes, mantendo apenas os 10 primeiros
    guint length = domingo->artistahistory_garray->len;
    if (length > 10) {    
        for (guint i = 10; i < domingo->artistahistory_garray->len; i++) {
            UmArtista* artista = g_array_index(domingo->artistahistory_garray, UmArtista*, i);
            freeUmArtista(artista); // Liberta os elementos excedentes
        }
    g_array_set_size(domingo->artistahistory_garray, 10);
    }
}




UmArtista* lookup_artista_historico(GHashTable* Artista, int artist_id){
    return g_hash_table_lookup(Artista, &artist_id);

}




// Função para adicionar um artista ao Domingo
void new_or_add(Domingo *domingo, char **tokens, MusicData *musicController)
{
  // transforma o char music_id em int para conseguir encontrar a estrutura Music
    int music_id = transformaIds(tokens[2]);
    int numartistas = getnumartistaMusicControl(musicController, music_id);
    //array de artistas que constituem essa musica
    int* arrayartistas = getarrayArtistasMusicControl(musicController,music_id, numartistas);

    GHashTable *artistahistory = domingo->artistahistory;
    if (!artistahistory)
    {
        fprintf(stderr, "Erro: artistahistory é NULL.\n");
        return;
    }

    char *segundosparaadicionar = remove_quotes(tokens[4]);
    int segundos = duration_to_seconds(segundosparaadicionar);

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
    else {
        printf("SOMETHING IS VERY WRONG\n");
    }

  free(arrayartistas);
  free(segundosparaadicionar);
}








GArray* get_artistahistory_garray_copy(Domingo* dom) {

    if (!dom || !dom->artistahistory_garray) return NULL;

    // Cria um novo GArray com as mesmas propriedades do original
    GArray* copy = g_array_new(FALSE, FALSE, sizeof(UmArtista*));

    // Itera pelos elementos e copia cada um
    for (guint i = 0; i < dom->artistahistory_garray->len; i++) {

        UmArtista* original = g_array_index(dom->artistahistory_garray, UmArtista*, i);
        // Cria uma cópia do elemento
        UmArtista* copy_element = new_umArtista(original->artist_id, original->totalsemanalsegundos);

        // Adiciona ao novo GArray
        g_array_append_val(copy, copy_element);
    }

    g_array_sort(copy, (GCompareFunc)compare_seconds);

    return copy;
}




int get_artist_id_from_garray (UmArtista* artista){
    return artista->artist_id;
}








//FUNCOES PRINTS 
void print_artisthistory (UmArtista* artista) {
    if (artista) {
        printf("ARTIST_ID: %d\n", artista->artist_id);
        printf("TOTAL_SEGUNDOS: %d\n", artista->totalsemanalsegundos);
    } else {
        fprintf(stderr, "Erro: ESTE UMARTISTA NAO EXISTE\n");

    }

}

// Função para imprimir o GArray
void print_garray(GArray* array) {
    if (array == NULL) {
        printf("O GArray está vazio ou não foi inicializado.\n");
        return;
    }

    printf("O GArray contém %d elementos:\n", array->len);

    // Iterar sobre todos os elementos do GArray
    for (guint i = 0; i < array->len; i++) {
        UmArtista* artista = g_array_index(array, UmArtista*, i);
        print_artisthistory(artista);
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


void print_semana_completa(gpointer key, gpointer value, gpointer user_data) {
    (void)key; // Se não for usado
    (void)user_data; // Ignora user_data, se não for usado

    Domingo *domingo = (Domingo *)value;

    if (domingo == NULL) {
        fprintf(stderr, "Erro: Domingo é NULL.\n");
        return;
    }

    if ((domingo->artistahistory) == NULL) {
        fprintf(stderr, "Erro: Hash Table artistahistory é NULL.\n");
        return;
    }

    printf("----- Hash Table DOMINGO da semana %s -----\n", domingo->data);
    g_hash_table_foreach(domingo->artistahistory, print_artisthistory_entry, NULL);
    printf("----- Fim da Hash Table DOMINGO da semana %s -----\n", domingo->data);
}
