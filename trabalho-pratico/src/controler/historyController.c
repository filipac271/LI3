#include "controler/usersController.h"
#include "controler/musicsController.h"
#include "controler/albumsController.h"
#include "validacao/validaHistory.h"
#include "utilidades.h"
#include "Entitys/users.h"
#include "Entitys/history.h"
#include "Input.h"
#include "Output.h"

#include <glib.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "Entitys/history.h"
#include "controler/historyController.h"



struct historyData{
    GHashTable* Domingo;
    GHashTable* history;
};


GHashTable* createHistoryTable() {
    GHashTable* Domingo = g_hash_table_new_full(g_str_hash, g_str_equal, free, (GDestroyNotify)freeDomingo);

    if (!Domingo) {
        fprintf(stderr, "Erro: Hash table Domingo não foi criada.\n");
        exit(1);
    } else {
        printf("Hash table Domingo criada com sucesso.\n");
    }

    return Domingo;
}

GHashTable* createUserHistoryTable() {
    GHashTable* history = g_hash_table_new_full(g_int_hash, g_int_equal, free, (GDestroyNotify)freeUserHistory);

    if (!history) {
        fprintf(stderr, "Erro: Hash table history não foi criada.\n");
        exit(1);
    } else {
        printf("Hash table history criada com sucesso.\n");
    }

    return history;
}



Domingo* lookup_domingo(GHashTable* domingo, char* data) {
    if (!domingo) {
        fprintf(stderr, "Erro: Tabela Domingo é NULL.\n");
        return NULL;
    }
    return g_hash_table_lookup(domingo, data);
}


void newDomingo_orNot(HistoryData* controller, char** tokens, MusicData* musicController) {

    char* data = malloc(11 * sizeof(char));

    strncpy(data, tokens[3]+1, 10);
    data[10] = '\0'; 

    char* domingo_anterior = calcular_domingo_anterior(data);
    free(data);


    if (g_hash_table_contains(controller->Domingo, domingo_anterior)) {
        // Se já existe, adiciona à hash table interna
        Domingo* domingo_atual = lookup_domingo(controller->Domingo, domingo_anterior);
        if (domingo_atual) {
            new_or_add((domingo_atual), tokens, musicController);
        }
    } else {
        // Cria um novo domingo
        Domingo* n_domingo = newDomingo(domingo_anterior);
        g_hash_table_insert(controller->Domingo, strdup(domingo_anterior), n_domingo);
    }

    free(domingo_anterior);  
}



History* lookup_UserHistory(HistoryData* historyController,int userId)
{
    return g_hash_table_lookup(historyController->history, &userId);
}


void addhistory(HistoryData* history, char* user_id,char* music_id,char* timestamp,char* duration )
{

        int ano, mes,dia,hora;
        sscanf(timestamp,"\"%d/%d/%d %d",&ano,&mes,&dia,&hora); 
        int musicId=transformaIds(music_id);
        int userId= transformaIds(user_id);
        int duracao= duration_to_seconds(duration);
        History* userHistory=lookup_UserHistory(history, userId);
        
    if(userHistory==NULL)
    {
        int* key = malloc(sizeof(int));  // Aloca memória para a chave
        *key = userId;
        userHistory= inicializaUserHistory(userId, musicId, ano,mes,dia,hora, duracao); 
         g_hash_table_insert(history->history,key, userHistory); 


    }
    else
    {    
        adicionaUserHistory(userHistory, musicId, ano,mes,dia,hora, duracao);
    }
  

}

HistoryData* historyFeed(char* diretoria, MusicData* musicData,ArtistsData* artistData) {
    HistoryData* Hdata = malloc(sizeof(HistoryData));
    if (!Hdata) {
        fprintf(stderr, "Erro: Alocação de memória para HistoryData falhou.\n");
        exit(1);
    }
    
    Output * Erros= iniciaOutput("resultados/history_errors.csv");

    Hdata->Domingo = createHistoryTable();
    Hdata->history=createUserHistoryTable();

    // Mesma coisa mas para a hash table da querie 6

    Parser* parserE = newParser(diretoria, "history.csv");

          // Ler a primeira linha do ficheiro  
    char* linha= pegaLinha(parserE);
    //Enviar a linha para o ficheiro "history_erros.csv", esta não será inserida na hashTable
    outputErros(Erros,linha);
    free(linha);

    while (1) {

        parserE = parser(parserE);

        char** tokens = getTokens(parserE);
        if (!tokens) {
         
            freeParser(parserE);
            break;
        }

    char* linhaE=getLineError(parserE);
    int isValid = validaHistory(tokens[5],tokens[4],Erros,linhaE);
    if(isValid) {
        addhistory(Hdata,tokens[1],tokens[2],tokens[3], tokens[4]);
       // newDomingo_orNot(Hdata, tokens, musicData); 
        //atualizaStreams(tokens[2], musicData, artistData);
       
    }  
     
        free(linhaE);
        free(getLine(parserE));  

    }
  
    freeOutput(Erros);


    return Hdata;
}


int getPosicaoAno(HistoryData* historyController,int user_id, int ano)
{
    History* userHistory= lookup_UserHistory(historyController, user_id);
    if(userHistory==NULL) 
    {
        return -1; 
    }
    int i= procuraAno(userHistory,ano);
    return i;
   
}


char** getNartistasMaisOuvidos(HistoryData* historyController, MusicData*musicController, int user_id,int  posicaoAno,int N)
{
     History* userHistory= lookup_UserHistory(historyController, user_id);
     char** resultados= NartistasMaisOuvidos(userHistory,musicController, posicaoAno,N);
    return resultados;

}



char* getDia(HistoryData*  historyController,int user_id,int ano)
{
   
    History* userHistory= lookup_UserHistory(historyController, user_id);
    char* data=DataMaisMusicas(userHistory,ano); //////Falta dar copia 
    return data;
}

char * getAlbumGenero(HistoryData* historyController,MusicData* musicController, AlbumsData*albumController, int userId,int posicaoAno)
{
    History* userHistory= lookup_UserHistory(historyController, userId);
    char* resultados=   AlbumGenero(musicController, userHistory,albumController, posicaoAno);
    return resultados;
}

char* getHora(HistoryData* historyController,int user_id,int ano)
{
    History* userHistory= lookup_UserHistory(historyController, user_id);
    char* hora= HoraMaisAudicoes(userHistory, ano);//////Falta dar copia
    return hora; 
}

//FAZER PRINT
void print_all_history (HistoryData* Hdata){
    printf("----- Hash Table do HISTORICO -----\n");
    sleep(3);
    g_hash_table_foreach(Hdata->Domingo, print_semana_completa, NULL);
    printf("----- Fim da Hash Table do HISTORICO-----\n");
}



void destroyHistoryData(HistoryData* data) {

        g_hash_table_destroy(data->Domingo);
        g_hash_table_destroy(data->history);
    
    printf("Tabela DOMINGO destruida\n");

}



