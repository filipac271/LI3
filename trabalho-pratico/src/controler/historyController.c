#include "controler/usersController.h"
#include "controler/musicsController.h"
#include "validacao/validaUser.h"
#include "utilidades.h"
#include "Entitys/users.h"
#include "Input.h"


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

  //GHashTable* Domingo =g_hash_table_new_full(g_int_hash, g_int_equal, free, (GDestroyNotify)freeUser);


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
   // printf("O TOKEN 3 É %s\n", tokens[3]);
    strncpy(data, tokens[3]+1, 10);
    data[10] = '\0'; // Garante o terminador nulo
  // printf("A DATA É %s\n", data);
    char* domingo_anterior = calcular_domingo_anterior(data);
    free(data);
  // printf("A DATA DO DOMINGO ANTERIOR NO NEW DOMINGO É: %s\n",domingo_anterior);

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

    free(domingo_anterior);  // Libera memória alocada por calcular_domingo_anterior
}

























HistoryData* historyFeed(char* diretoria, MusicData* musicData) {
    HistoryData* Hdata = malloc(sizeof(HistoryData));
    if (!Hdata) {
        fprintf(stderr, "Erro: Alocação de memória para HistoryData falhou.\n");
        exit(1);
    }
    Output * Erros= iniciaOutput("resultados/history_errors.csv");

    Hdata->Domingo = createHistoryTable();
  //  printf("CHEGOU AQUI 1\n");
    // Mesma coisa mas para a hash table da querie 6

    Parser* parserE = newParser(diretoria, "history.csv");
     //   printf("AQUIIIII 1\n");

          // Ler a primeira linha do ficheiro  
    char* linha= pegaLinha(parserE);
    //Enviar a linha para o ficheiro "artist_erros.csv", esta não será inserida na hashTable
    outputErros(Erros,linha);
    free(linha);

    while (1) {
        parserE = parser(parserE);

        char** tokens = getTokens(parserE);
        if (!tokens) {
            freeParser(parserE);
            break;
        }
      //  printf("APOSTO QUE NAO CHEGA AQUI! \n");
    char* linhaE=getLineError(parserE);

    //if(isValid) {   }  

    //é preciso depois acabar esta funcao porque eu nao tenho o artista atualizado
    //deveria estar no ArtistCOntroller, mas ainda está no history.c MUDAR DEPOIS
    //put_stream_into_Artist(tokens, musicController, artistCOntroller);
        newDomingo_orNot(Hdata, tokens, musicData);
      //  printf("MILAGRE!\n");

        free(linhaE);
        free(getLine(parserE));  // Libere a linha lida
      //  printf("ESTÁ AQUI\n");
    }
    freeOutput(Erros);


    return Hdata;
}





 //if(isValid) {   }  

    //é preciso depois acabar esta funcao porque eu nao tenho o artista atualizado
    //deveria estar no ArtistCOntroller, mas ainda está no history.c MUDAR DEPOIS
    //put_stream_into_Artist(tokens, musicController, artistCOntroller);

//FAZER PRINT
void print_all_history (HistoryData* history){
    printf("----- Hash Table do HISTORICO -----\n");
    sleep(3);
    g_hash_table_foreach(history->Domingo, print_semana_completa, NULL);
    printf("----- Fim da Hash Table do HISTORICO-----\n");
}
//FAZER DESTROY




// void freeDomingo(void* domingo) {
//     Domingo* d = (Domingo*)domingo;
//     free(domingo->data);

//     g_hash_table_destroy(get_artisthistorido_dedomingo(domingo));  // Libera a tabela de artistas
//     free(d);
// }


void destroyHistoryData(HistoryData* data) {
   // Verificar se a estrutura e tabela existem.
        // Iterar pela GHashTable e liberar cada `Domingo*`.

        // Destruir a tabela principal após liberar os elementos.
        g_hash_table_destroy(data->Domingo);
    
    printf("Tabela DOMINGO destruida\n");

}



