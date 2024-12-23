#include "controler/usersController.h"
#include "controler/musicsController.h"
#include "validacao/validaHistory.h"
#include "utilidades.h"
#include "Entitys/users.h"
#include "Input.h"
#include "Output.h"


#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "Entitys/history.h"
#include "controler/historyController.h"



struct historyData{
    GHashTable* Domingo;
  //  GHashTable* Anos;
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


HistoryData* historyFeed(char* diretoria, MusicData* musicData, ArtistsData* artistData) {
    HistoryData* Hdata = malloc(sizeof(HistoryData));
    if (!Hdata) {
        fprintf(stderr, "Erro: Alocação de memória para HistoryData falhou.\n");
        exit(1);
    }
    Output * Erros= iniciaOutput("resultados/history_errors.csv");

    Hdata->Domingo = createHistoryTable();

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
        newDomingo_orNot(Hdata, tokens, musicData); 
        atualizaStreams(tokens[2], musicData, artistData);
        
    }  
    
        free(linhaE);
        free(getLine(parserE));  

    }
    freeOutput(Erros);


    return Hdata;
}





//FAZER PRINT
void print_all_history (HistoryData* history){
    printf("----- Hash Table do HISTORICO -----\n");
    sleep(3);
    g_hash_table_foreach(history->Domingo, print_semana_completa, NULL);
    printf("----- Fim da Hash Table do HISTORICO-----\n");
}



void destroyHistoryData(HistoryData* data) {

        g_hash_table_destroy(data->Domingo);
    
    printf("Tabela DOMINGO destruida\n");

}



