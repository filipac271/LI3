#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "personalRecomendador.h"

// Definição de estrutura para armazenar somatórios e IDs
struct recomendacao{
    char *userId;
    int somaDiferencas;
};

int comparaRecomendacoes(const void *a,const void *b) {
    Recomendacao *recomandacaoA = (Recomendacao *)a;
    Recomendacao *recomendacaoB = (Recomendacao *)b;
    return recomandacaoA->somaDiferencas - recomendacaoB->somaDiferencas; 
}

char **recomendaUtilizadoresP(
    char *idUtilizadorAlvo,
    int **matrizClassificacaoMusicas,
    char **idsUtilizadores,
    char **nomesGeneros,
    int numUtilizadores,
    int numGeneros,
    int numRecomendacoes
) {
    
    (void)nomesGeneros;//Esquisito não ter necessidade de usar
    
    int indiceUtilizadorAlvo = -1;
    for (int i = 0; i < numUtilizadores; i++) {
        if (strcmp(idsUtilizadores[i], idUtilizadorAlvo) == 0) {
            indiceUtilizadorAlvo = i;
            break;
        }
    }

    if (indiceUtilizadorAlvo == -1) {
        return NULL; // Utilizador alvo não encontrado
    }

    Recomendacao *recomendacoes = malloc(numUtilizadores * sizeof(Recomendacao));

    char **resultados = malloc(numRecomendacoes * sizeof(char *));
    int numResultados = 0;

    int *preferenciasAlvo = matrizClassificacaoMusicas[indiceUtilizadorAlvo];
    int countResultados = 0;

    for (int i = 0; i < numUtilizadores; i++) {
        if (i == indiceUtilizadorAlvo) continue; 

        int somaDiferencas = 0;
        for (int j = 0; j < numGeneros; j++) {
            somaDiferencas += abs(preferenciasAlvo[j] - matrizClassificacaoMusicas[i][j]);
        }

        // Adicionar diretamente ao array de resultados se a diferença for zero
        if (somaDiferencas == 0) {
            resultados[numResultados++] = idsUtilizadores[i];
            if (numResultados == numRecomendacoes) {
                free(recomendacoes); 
                return resultados;  // Retornar imediatamente 
            }
        } else {
            // Caso contrário, armazenar para posterior ordenação
            recomendacoes[countResultados].userId = idsUtilizadores[i];
            recomendacoes[countResultados].somaDiferencas = somaDiferencas;
            countResultados++;
        }
    }

    qsort(recomendacoes, countResultados, sizeof(Recomendacao),(comparaRecomendacoes));

    // Adicionar as restantes recomendações até atingir o número desejado
    for (int i = 0; i < countResultados && numResultados < numRecomendacoes; i++) {
        resultados[numResultados++] = recomendacoes[i].userId;
    }

    free(recomendacoes);
    return resultados;
}
