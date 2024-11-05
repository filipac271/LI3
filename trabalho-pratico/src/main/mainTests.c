#include "main/feeder.h"
#include "parser/parsermusica.h"
#include "parser/userParser.h"

#include "controler/mainController.h"
#include "querie/querieManager.h"
#include "IOManager.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <glib.h>



// Função para comparar linha a linha dois arquivos e contar ocorrências corretas
int compararFicheirosPorLinha(char *file1,char *file2, int *ocorrenciasCorretas) {
    FILE *f1 = fopen(file1, "r");
    FILE *f2 = fopen(file2, "r");

    if (f1 == NULL || f2 == NULL) {
        perror("Erro ao abrir um dos arquivos para comparação");
        return -1;  // Erro ao abrir arquivos
    }

    char linha1[1024], linha2[1024];
    int linhaNumero = 1;
    *ocorrenciasCorretas = 0;

    while (fgets(linha1, sizeof(linha1), f1) && fgets(linha2, sizeof(linha2), f2)) {
        // Remover quebra de linha para evitar diferenças acidentais
        linha1[strcspn(linha1, "\n")] = '\0';
        linha2[strcspn(linha2, "\n")] = '\0';

        if (strcmp(linha1, linha2) == 0) {
            (*ocorrenciasCorretas)++;  // Incrementa ocorrências corretas
        } else {
            printf("Diferença encontrada na linha %d do arquivo %s\n", linhaNumero, file1);
            fclose(f1);
            fclose(f2);
            return 0;  // Arquivo é diferente
        }
        linhaNumero++;
    }

    // Verifica se ambos os arquivos terminaram ao mesmo tempo
    if (fgets(linha1, sizeof(linha1), f1) || fgets(linha2, sizeof(linha2), f2)) {
        printf("Tamanho diferente entre os arquivos, diferença encontrada na linha %d do arquivo %s\n", linhaNumero, file1);
        fclose(f1);
        fclose(f2);
        return 0;
    }

    fclose(f1);
    fclose(f2);
    return 1;  // Arquivos são iguais
}

// Função principal para realizar os testes
int teste(char **argv) {
    printf("Entrada nos testes\n");

    char *pastaPrincipal = argv[1];       // Recebe a pasta principal como argumento
    char *queriesFile = argv[2];          // Arquivo de queries
    char *outputEsperado = argv[3];       // Pasta com os arquivos esperados

    FILE *queriesInput = abrirFILE(queriesFile, "r");
    MainController *data = feeder(pastaPrincipal);
    int numQueries = queries(data, queriesInput);

    for (int i = 0; i < numQueries; i++) {
        // Nome do arquivo gerado
        char resultadoFile[256];
        sprintf(resultadoFile, "resultados/command%d_output.txt", i + 1);

        // Nome do arquivo esperado correspondente
        char esperadoFile[256];
        sprintf(esperadoFile, "%s/command%d_output.txt", outputEsperado, i + 1);

        // Contador de ocorrências corretas
        int ocorrenciasCorretas = 0;

        // Comparar os arquivos gerado e esperado linha a linha
        int iguais = compararFicheirosPorLinha(resultadoFile, esperadoFile, &ocorrenciasCorretas);
        if (iguais == 1) {
            printf("Test %d: PASS - %d ocorrências corretas\n", i + 1, ocorrenciasCorretas);
        } else {
            printf("Test %d: FAIL - %d ocorrências corretas\n", i + 1, ocorrenciasCorretas);
        }
    }

    destroyData(data);
    fecharFILE(queriesInput);
    return 0;
}