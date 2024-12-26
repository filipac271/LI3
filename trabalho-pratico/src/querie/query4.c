#include "controler/artistsController.h"
#include "controler/historyController.h"
#include "controler/musicsController.h"
#include "utilidades.h"
#include "Entitys/artists.h"
#include "Entitys/history.h"
#include "Entitys/musics.h"
#include "Output.h"
#include "querie/query4.h"


#include <stdio.h>
#include <stdlib.h>
#include <glib.h>
#include <unistd.h>


// struct ocorrencias{
//     int artist_id;
//     int n_ocorrencias;
// };

// struct ocorrencias_Data{
//     GHashTable* hash_ocorrencias;
// };




// Ocorrencias* new_ocorencia (int artist_id, int n_ocorrencia){
//     Ocorrencias* novo = malloc(sizeof(Ocorrencias));
//     if (novo == NULL) {
//         fprintf(stderr, "Memory allocation failed for new music\n");
//         exit(1);
//     } 

//     novo->artist_id = artist_id;
//     novo->n_ocorrencias = n_ocorrencia;
//     return novo;
// }





// Ocorrencias* lookup_ocorrencia_artista (GHashTable* ocorrencias_artistas, int artist_id){
//     return g_hash_table_lookup(ocorrencias_artistas, &artist_id);
// }



// void free_ocorrencias(Ocorrencias* ocorreu){
//     if(ocorreu != NULL){
//         free(ocorreu);
//     }
// }

// GHashTable* iniciar_hash_ocorrencias(){

// // A key da Hash Table é o ID  das músicas
//   GHashTable* hash_ocorrencias = g_hash_table_new_full(g_int_hash, g_int_equal, free, (GDestroyNotify)free_ocorrencias);

//  // Verificar se a hash table foi criada corretamente
//   if(hash_ocorrencias == NULL){
   
//     printf("Erro: Algo nao ocorreu como devia.\n");
//     exit(1);

//   } else {

//     printf("Diversas ocorrencias estao a ocorrer.\n");
//   }

//   return(hash_ocorrencias);

// }


// //Inserir música na Hash Table
// void inserir_ocorrencia_na_htable(GHashTable* hash_ocorrencia, Ocorrencias*ocorreu, int artist_id) {
//     int* key = malloc(sizeof(int));  // Aloca memória para a chave

//     *key = artist_id;
//     g_hash_table_insert(hash_ocorrencia, key, ocorreu);
// }

// void print_ocorrencias (Ocorrencias* ocorreu){
//     if(ocorreu){
//         printf("O ARTIST ID É ESTE :%d\n", ocorreu->artist_id);
//         printf("AS OCORRENCIAS SÃO: %d\n", ocorreu->n_ocorrencias);
//     }else{
//         printf("NADA OCORREUEUEUEUEU");
//     }

// }




// // Função  para imprime uma música
// void print_ocorrencia_entry (gpointer key, gpointer value, gpointer user_data) {

//     if (key == NULL || value == NULL) {
//         printf( "Chave ou valor nulo encontrado.\n");
//         sleep(2);
//         return;
//     }

//     // Suprime o aviso de variáveis não usadas
//     (void)user_data;

//     //char* id = (char*)key;
//     Ocorrencias* ocorreu = (Ocorrencias*)value;

//     print_ocorrencias(ocorreu);
// }


// // Função para imprimir toda a hash table das Músicas
// void print_all_ocorrencias(Ocorridos* hash) {

//     printf("----- Hash Table de OCORRENCIA -----\n");
//     sleep(3);
//     g_hash_table_foreach(hash->hash_ocorrencias, print_ocorrencia_entry, NULL);
//     sleep(3);
//     printf("----- Fim da Hash OCORRENCIA -----\n");

// }




















// int artista_mais_frequente_sem_data(GHashTable* semanas, int *ocorrencia_final) {
//    // printf("Entoru aqui sem data aaaa\n");
//     int artista_mais_frequente = -1;
//     int max_ocorrencias = 0;

//     //GHashTable* contador_artistas = g_hash_table_new(g_int_hash, g_int_equal);
//     Ocorridos* hash = malloc(sizeof(Ocorridos));

//     if(hash == NULL){
//         fprintf(stderr,"Alocação de memória do MusicsController não foi bem sucedido");
//         exit(1);
//     }
//     //printf("HERE WE GO AGAIN!\n");
//     hash->hash_ocorrencias = iniciar_hash_ocorrencias();

//     GHashTableIter iter;
//     gpointer key, value;
//     //printf("DEIXA VER\n");
//     g_hash_table_iter_init(&iter, semanas);
//     //printf("ESTOU AQUIIIIII ANTES DO WHILE\n");

//     while (g_hash_table_iter_next(&iter, &key, &value)) {
//         Domingo* semana_atual = (Domingo*)value;
//         //printf("AQUI ESTAMOS!!!\n");

//         GArray* garray = (get_garray_from_domingo(semana_atual));
//        // printf("MAYBE!\n");
//         if (garray == NULL) {
//             continue;
//         }

//         for (guint i = 0; i < garray->len; i++) {
//          //   printf("Dentro do for\n");
//             ArrayArtistas* artista = g_array_index(garray, ArrayArtistas*, i);
//         //print_artisthistorygarray(artista);
//             //sleep(4);
// //            printf("O GARRAY COISO AQUI \n");

//             int artist_id = get_artist_id_from_garray(artista);
//            // printf("O ARTIST ID É %d\n", artist_id);

//             int contagem = 0;

//             Ocorrencias* ocorrencia_atual = lookup_ocorrencia_artista(hash->hash_ocorrencias, artist_id);
//             //printf("FOI AQUI\n");
//             if(!ocorrencia_atual){
//                 Ocorrencias* nova = new_ocorencia(artist_id, 1);
//                 inserir_ocorrencia_na_htable(hash->hash_ocorrencias, nova, artist_id);
//                // printf("chegou aqui espero eu!\n");
//                 contagem = 1;

//             }else{
//                 int temp = ocorrencia_atual->n_ocorrencias ;
//                 ocorrencia_atual->n_ocorrencias = temp + 1;
//                 contagem = temp +1;
//             }
//            // printf("Sei lá\n");
//             int nova_ocorrencia = contagem;
//             //printf("AS OCORRENCIAS SÃO %d\n", nova_ocorrencia);
//             //printf("O artist id da ocorrencia é %d\n", artist_id);
//             //printf("\n");
//             //sleep(2);

//             //printf("Procurandoooo\n");
//             //estes ifs nao estaoa  fucnionar??? resolver amanha
//             if (nova_ocorrencia > max_ocorrencias) {
//                 max_ocorrencias = nova_ocorrencia;
//                 artista_mais_frequente = artist_id;
//             }else{
                
//                 if(nova_ocorrencia == max_ocorrencias){
//                     if(artist_id < artista_mais_frequente){
//                         artista_mais_frequente = artist_id;
//                     }
//                 }
//             }
//         }
//     }

//     if (artista_mais_frequente != -1) {
//         printf("O artista mais frequente no top 10 foi o ID %d, com %d ocorrências.\n", artista_mais_frequente, max_ocorrencias);
//     } else {
//         printf("Nenhum artista encontrado no intervalo especificado.\n");
//     }

//     *ocorrencia_final = max_ocorrencias;
//     printf("chegou!");

//     //print_all_ocorrencias(hash);

//     g_hash_table_destroy(hash->hash_ocorrencias);
//     printf("Honestamente, só deus sabe\n");

//     return artista_mais_frequente;
// }







// int artista_mais_frequente_com_data (GHashTable* semanas, char* data_inicio, char* data_fim, int *ocorrencia_final){
//     int artista_mais_frequente = -1;
//     int max_ocorrencias = 0;

//     GHashTable* contador_artistas = g_hash_table_new(g_int_hash, g_int_equal);
//     // Iterar sobre as semanas no intervalo
//     GHashTableIter iter;
//     gpointer key, value;
//     g_hash_table_iter_init(&iter, semanas);



// if (data_inicio != NULL && data_fim != NULL && strcmp(data_inicio, "") != 0 && strcmp(data_fim, "") != 0) {
//     while (g_hash_table_iter_next(&iter, &key, &value)) {

//         const char* data_atual = (const char*)key;
//         Domingo* semana_atual = (Domingo*)value;

//         // Verificar se está no intervalo
//         if (strcmp(data_atual, data_inicio) >= 0 && strcmp(data_atual, data_fim) <= 0) {
//            // printf("APOSTO QUE O ERRO É ISTO: %s\n", data_atual);
//             // Processar o GArray (top 10 artistas)
//             for (int i = 0; i < get_garray_len(semana_atual); i++) {

//                // print_garray(get_garray_from_domingo(semana_atual));

//                 ArrayArtistas* artista = g_array_index((get_garray_from_domingo(semana_atual)), ArrayArtistas*, i);

//                 int artist_id = get_artist_id_from_garray(artista);
//                // printf("O ARTIST ID É %d\n", artist_id);
//                 int ocorrencias = GPOINTER_TO_INT(g_hash_table_lookup(contador_artistas, &artist_id));
//                // printf("AQUI O N DE OCORRENCIAS É:%d\n", ocorrencias);

//                // int* ocorrencias = (int*)g_hash_table_lookup(contador_artistas, GINT_TO_POINTER(get_artist_id_from_garray(artista)));
//                 int nova_ocorrencia = (ocorrencias ? ocorrencias : 0) + 1;
//                // printf("A NOVA OCORRENCIA é: %d\n", nova_ocorrencia);
//                 // if(artist_id == 144){
//                 //     printf("A OCORRENCIAS DAQUELE QUE DEVIA SER É %d\n", nova_ocorrencia);
//                 // }

//                 // Atualizar o contador na hashtable
//                 g_hash_table_insert(contador_artistas, &(artist_id), GINT_TO_POINTER(nova_ocorrencia));
//                 // Verificar se este é o artista mais frequente
//                 if (nova_ocorrencia > max_ocorrencias) {
//                     max_ocorrencias = nova_ocorrencia;
//                    // printf("A OCORRENCIA MAXIMA É %d\n", max_ocorrencias);
//                     artista_mais_frequente = (get_artist_id_from_garray(artista));
//                 }else{
//                 if(nova_ocorrencia == max_ocorrencias){
//                     if((get_artist_id_from_garray(artista)) < artista_mais_frequente){
//                         artista_mais_frequente = (get_artist_id_from_garray(artista));
//                         }
//                     }
//                 }
//             }
//         }
//     }
// }
//     //DEBUG
//     if (artista_mais_frequente != -1) {
//         printf("O artista mais frequente no top 10 foi o ID %d, com %d ocorrências.\n", artista_mais_frequente, max_ocorrencias);
//     } else {
//         printf("Nenhum artista encontrado no intervalo especificado.\n");
//     }


//     g_hash_table_destroy(contador_artistas);
//     *ocorrencia_final =  max_ocorrencias;
//     return artista_mais_frequente;
// }







// // //name;type;count_top_10

// // //4S 2022/12/09 2024/05/02


// // 46 -4S        Jamie Burton é A0003542=individual=44 mas o 46 esta mal

// // 47 - 4S 2023/10/29 2024/05/27   A0000144=individual=3 // esta mal  é suposto ser o CornflowerBlue Far
// // O DOMINGO INCIAL É 2023/10/29 domingo certo
// // O DOMINGO FINAL É: 2024/05/26 domingo certo

// // 48 - 4 as ocorrencias estao mal
// // 49 - 4S 2022/12/09 2024/05/02 as ocorrencias estao mal deviam ser 13
// // O DOMINGO INCIAL É 2022/12/04 domingo certo
// // O DOMINGO FINAL É: 2024/04/28 domingo certo

// // 50 - 4S 2021/04/26 2023/03/22 as ocorrencias estao mal deviam ser 11 //o 50 corrigiu milagrosamente
// // O DOMINGO INCIAL É 2021/04/25 domingo certo
// // O DOMINGO FINAL É: 2023/03/19 domingo certo

// // 51 - 4S 2017/07/26 2023/02/14 as ocorrenciass estao mal deviam ser 28
// // O DOMINGO INCIAL É 2017/07/23 domingo certo
// // O DOMINGO FINAL É: 2023/02/12 domingo certo

// // 52 - 4S 2023/02/03 2024/08/19 as ocorrencias estao mal deviam ser 15
// // O DOMINGO INCIAL É 2023/01/29 domingo certo
// // O DOMINGO FINAL É: 2024/08/18 domingo certo

// // 53 - 4S 2022/06/06 2022/07/23 as ocorrencias deviam ser 3 e o 113 é o Lil Tyler
// // O DOMINGO INCIAL É 2022/06/05 domingo certo
// // O DOMINGO FINAL É: 2022/07/17 domingo certo

// // 54 - 4S as ocorrencias deviam ser 44
// // 55 - 4


// //NOTE TO SELF: o erro nao está no calcular domingo

// void query4 (HistoryData* HistoryController, ArtistsData* ArtistController, char* line, int i){
//     char data_inicio[11] = ""; 
//     char data_fim[11] = "";
//     //printf("CHEGUEI AQUI!\n");

//     int query4_result = sscanf(line + 2, "%s %s", data_inicio, data_fim);  // Lê o intervalo de idades (min e max) a partir da linha de entrada
//     int artist_id = 0;
//     int ocorrencias = 0;
//     //printf("Estou aqui!\n");


// if(query4_result < 2){
//    // printf("ENTROU SEM DATA\n");
//     artist_id = artista_mais_frequente_sem_data((get_Domingo_from_HD(HistoryController)),&ocorrencias);


//     } else {
//     char* domingo_inicio = malloc(11 * sizeof(char));
//     calcularDomingoAnterior(data_inicio, domingo_inicio);
//    // printf("O DOMINGO INCIAL É %s\n", domingo_inicio);

//     char* domingo_final = malloc(11 * sizeof(char));
//     calcularDomingoAnterior(data_fim, domingo_final);
//     //printf("O DOMINGO FINAL É: %s\n", domingo_final);

//     artist_id = artista_mais_frequente_com_data((get_Domingo_from_HD(HistoryController)), domingo_inicio, domingo_final, &ocorrencias);
//    // printf("O ARTIST ID DO ARTISTA MAIS VEZES NO TOP 10 É %d\n", artist_id);

//    // printf("O NUMERO DE OCORRENCIAS FOI %d\n", ocorrencias);

//     free(domingo_inicio);
//     free(domingo_final);
//     }

//     char* filename = malloc(sizeof(char) * 256);
//     sprintf(filename, "resultados/command%d_output.txt", i + 1);
//     Output* output = iniciaOutput(filename);

//     Artist* artista_atual = lookup_artist(ArtistController, artist_id);
//     char* nome = getArtistName(artista_atual);
//     char* tipo = getArtistType(artista_atual);

//     output4(output, nome, tipo, (ocorrencias), line[1]);

//     free(nome);
//     free(tipo);
//     free(filename);
    
//     //free(data_fim);
//     //free(data_inicio);
//     freeOutput(output);
// }



