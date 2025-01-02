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

GHashTable* get_Domingo_from_HD (HistoryData* data){
    return data->Domingo;
}




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
    //tira as horas a que a musica foi ouvida
    strncpy(data, tokens[3]+1, 10);
    data[10] = '\0'; 

    char* domingo_anterior = malloc(11 * sizeof(char));

    //calcula o domingo dessa semana para usar como key da hash table externa
    calcularDomingoAnterior(data, domingo_anterior);

    //liberta-se a data original já que não vai ser mais usada
    free(data);
    //verifica se já eiste uma hashtable com domingo_anterior como key
    if (g_hash_table_contains(controller->Domingo, domingo_anterior)) {
        // Se já existe, adiciona à hash table interna
        Domingo* domingo_atual = lookup_domingo(controller->Domingo, domingo_anterior);
        if (domingo_atual) {
            new_or_add((domingo_atual), tokens, musicController);
        }
    } else {
        // se nao existir essa data então cria um novo domingo
        Domingo* n_domingo = newDomingo(domingo_anterior);
        g_hash_table_insert(controller->Domingo, strdup(domingo_anterior), n_domingo);
    }

    free(domingo_anterior);  //liberta a data
}



//Basicamente a ideia desta função é passar todas as hashtables para garrays de 10 já ordenados e apagar a hashtable 
void passa_hastable_para_garray (HistoryData* data){

    GHashTableIter iter;
    gpointer key, value;

    // Itera sobre a GHashTable e transfere os dados para o GArray
    g_hash_table_iter_init(&iter, data->Domingo);

    while (g_hash_table_iter_next(&iter, &key, &value)){

        Domingo* domingo_atual = value;

        passa_Domingo_para_garray(domingo_atual);
    } 
    
}


HistoryData* historyFeed(char* diretoria, MusicData* musicData, ArtistsData* artistData,UsersData* usersData) {

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
        
        char* genre = getMusicGenreControl(tokens[2],musicData,'s');
        atualizaPrefsUser(genre,tokens[1],usersData);
    }  

        free(linhaE);
        free(getLine(parserE));  

    }
    freeOutput(Erros);

    passa_hastable_para_garray(Hdata);

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


//Q4

int id_maiores_ocorrencias(GHashTable* domingo, int* maior_n_ocorrencias) {
    //Criamos a hash table auxiliar
    GHashTable* hash_auxiliar = g_hash_table_new_full(g_int_hash, g_int_equal, free, free);

    GHashTableIter iter;
    gpointer key, value;

    int max_ocorrencias = -1;
    int mais_freq_artist = -1;

    //Começamos a ver A hashtable externa
    g_hash_table_iter_init(&iter, domingo);

    while (g_hash_table_iter_next(&iter, &key, &value)) {
        //hash table externa
        Domingo* semana_atual = (Domingo*)value;
        //GArray interno
        GArray* top_semanal = get_garray_from_domingo(semana_atual);

        for (int i = 0; i < (int)top_semanal->len; i++) {
            //Vamos iterar o GArray interno
            UmArtista* artista_atual = g_array_index(top_semanal, UmArtista*, i);
            
            int id_atual = get_artist_id_from_garray(artista_atual);

            // Aloca memória para a chave para evitar usar algo local 
            int* id_atual_ptr = g_new(int, 1);
            *id_atual_ptr = id_atual;

            // Verifica se a chave já existe na hash table
            int* ocorrencia_atual_ptr = g_hash_table_lookup(hash_auxiliar, id_atual_ptr);

            if (!ocorrencia_atual_ptr) {
                // Não existe na tabela; inicializa com 1
                int* nova_ocorrencia = g_new(int, 1);
                *nova_ocorrencia = 1;
                g_hash_table_insert(hash_auxiliar, id_atual_ptr, nova_ocorrencia);
               // g_free(nova_ocorrencia);
            } else {
                // Já existe; incrementa
                (*ocorrencia_atual_ptr)++;
                g_free(id_atual_ptr); // Libera a chave alocada para evitar duplicação
            }

            // Atualiza o artista mais frequente
            int ocorrencia_atual = ocorrencia_atual_ptr ? *ocorrencia_atual_ptr : 1;

            if (ocorrencia_atual > max_ocorrencias || 
                (ocorrencia_atual == max_ocorrencias && id_atual < mais_freq_artist)) {
                max_ocorrencias = ocorrencia_atual;
                mais_freq_artist = id_atual;
                *maior_n_ocorrencias = max_ocorrencias;
            }
        }
    }

    g_hash_table_destroy(hash_auxiliar);
    return mais_freq_artist;
}




//Assume-se que as datas recebidas por esta funcao já sao os domingos 
int artista_mais_frequente_com_data (GHashTable* semanas, char* data_inicio, char* data_fim, int *ocorrencia_final){
    int artista_mais_frequente = -1;
    int max_ocorrencias = 0;

    GHashTable* contador_artistas = g_hash_table_new_full(g_int_hash, g_int_equal, free, free);
    // Iterar sobre as semanas no intervalo
    GHashTableIter iter;
    gpointer key, value;
    g_hash_table_iter_init(&iter, semanas);

if (data_inicio != NULL && data_fim != NULL && strcmp(data_inicio, "") != 0 && strcmp(data_fim, "") != 0) {
    while (g_hash_table_iter_next(&iter, &key, &value)) {

        char data_atual[11]; 
        calcularDomingoAnterior((char*)key, data_atual);
        // Verificar se está no intervalo
        if ( strcmp(data_atual, data_inicio) >=0 && strcmp(data_atual, data_fim) <= 0) {
        //hash table externa
        Domingo* semana_atual = (Domingo*)value;
        //GArray interno
        GArray* top_semanal = get_garray_from_domingo(semana_atual);

            // Processar o GArray (top 10 artistas)
            for (int i = 0; i < (int)top_semanal->len; i++) {

                UmArtista* artista_atual = g_array_index(top_semanal, UmArtista*, i);

                int id_atual = get_artist_id_from_garray(artista_atual);

                // Aloca memória para a chave para evitar usar algo local 
                int* id_atual_ptr = g_new(int, 1); 
                *id_atual_ptr = id_atual;

                // Verifica se a chave já existe na hash table
                int* ocorrencia_atual_ptr = g_hash_table_lookup(contador_artistas, id_atual_ptr);

                if (!ocorrencia_atual_ptr) {
                    // Não existe na tabela; inicializa com 1
                    int* nova_ocorrencia = g_new(int, 1); 
                    *nova_ocorrencia = 1;
                    g_hash_table_insert(contador_artistas, id_atual_ptr, nova_ocorrencia);

                } else {
                    // Já existe; incrementa
                    (*ocorrencia_atual_ptr)++;
                    g_free(id_atual_ptr); // Liberta a chave para nao correr o risco de haver algum tipo de duplicaçao
                }

                int ocorrencia_atual = ocorrencia_atual_ptr ? *ocorrencia_atual_ptr : 1;
                
                if (ocorrencia_atual > max_ocorrencias 
                || (ocorrencia_atual == max_ocorrencias && id_atual < artista_mais_frequente)){
                    max_ocorrencias = ocorrencia_atual;
                    artista_mais_frequente = id_atual;
                    *ocorrencia_final =  max_ocorrencias;

                }
            }
        }
    }
}
    //DEBUG
    // if (artista_mais_frequente != -1) {
    //     printf("O artista mais frequente no top 10 foi o ID %d, com %d ocorrências.\n", artista_mais_frequente, max_ocorrencias);
    // } else {
    //     printf("Nenhum artista encontrado no intervalo especificado.\n");
    // }

    g_hash_table_destroy(contador_artistas);
    return artista_mais_frequente;
}
