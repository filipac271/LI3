#include "controler/musicsController.h"
#include "querie/querie1.h"


#include <stdio.h>
#include <stdlib.h>
#include <glib.h>


// void insert_or_sum(GHashTable table, charkey, float valor_novo) {
//     // Tentar buscar o tuplo existente
//     Tuplo tuplo_existente = g_hash_table_lookup(table, key);

//     if (tuplo_existente != NULL) {
//         // Se o tuplo já existir, somar o valor ao valor existente
//         tuplo_existente->valor += valor_novo;
//         // A tabela vai manter o tuplo existente, pois a referência é a mesma
//     } else {
//         // Se não existir, criar um novo tuplo e inserir na hash table
//         Tuplonovo_tuplo = malloc(sizeof(Tuplo));
//         novo_tuplo->nome = strdup(key);  // Copiar a string da chave
//         novo_tuplo->valor = valor_novo;

//         // Inserir o novo tuplo na hash table (substitui se já existir)
//         g_hash_table_replace(table, novo_tuplo->nome, novo_tuplo);
//     }
// }

// Output
// name 1;type 1;discography duration 1;country 1

struct querie2{
  char *artist_id; //array
  char *artist_type; //string
  int discography; //int em segundos
  char *artist_country; //???????? //string
};


//a ideia seria ir criando as coisas e pondo na hash table e ao emsmo tempo ir criando um array com os tempos, os tempos seriam a key da hash table
// entao eu fazia uma funlao que procurasse o maior elemento do array, e dava à key a hash tbale para procurar o artista ()
//NAO ESQUECER RESOLUÇAO DE CONFITOS COM OS EMPATES!!!!! (pensar depois)

//maybe mudar a estrutura da musica para a duration passar a segundos????
//FUnções basicas que eu já posso fazer

int duration_to_seconds(const char *duration_str) {
    int hours, minutes, seconds;

    sscanf(duration_str, "%d:%d:%d", &hours, &minutes, &seconds);

    return hours * 3600 + minutes * 60 + seconds;
}


