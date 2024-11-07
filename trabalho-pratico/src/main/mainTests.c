#define _GNU_SOURCE and #define _POSIX_C_SOURCE 1999309L
#include "main/feeder.h"
#include "controler/mainController.h"
#include "querie/querieManager.h"
#include "IOManager.h"
#include "querie/querie1.h"
#include "querie/querie2.h"
#include "querie/querie3.h"
#include "utilidades.h"


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <glib.h>
#include<sys/resource.h>

// Constantes de cor
#define COLOR_RESET "\033[0m"
#define COLOR_GREEN "\033[32m"
#define COLOR_RED "\033[31m"






// Função principal para realizar os testes
int teste(char **argv) {
    printf("Entrada nos testes\n");

    struct timespec start, end;

    float timeQ1 = 0;
    float timeQ2 = 0;
    float timeQ3 = 0;

    int q1 = 0;
    int q2 = 0;
    int q3 = 0;


    char *pastaPrincipal = argv[1];       // Recebe a pasta principal como argumento
    char *queriesFile = argv[2];          // Arquivo de queries
    char *outputEsperado = argv[3];       // Pasta com os arquivos esperados

    // FILE *queriesInput = abrirFILE(queriesFile, "");
    Parser* parserT = newParser(queriesFile,"");
    MainController *data = feeder(pastaPrincipal);

    char* line = NULL;  // Ponteiro para a linha, alocado dinamicamente pelo getline
    line = pegaLinha(parserT);

    int min, max;
    int n;
    char country[256] = "";  // String para armazenar o país, inicializada como string vazia
    int i = 0;

    for (i = 0; line != NULL ; i++) {
        // Verifica se a linha tem pelo menos 1 caractere
        if (strlen(line) == 0) continue;

        // Remove a nova linha no final, se existir
        if (line[strlen(line) - 1] == '\n') {
            line[strlen(line) - 1] = '\0';
        }

        // Recupera controladores
        UsersData* UserController = getUserController(data);
        ArtistsData* ArtistContoller = getartistController(data);

        switch (line[0]) {
            case '1':
                if (strlen(line) >= 2) {

                    clock_gettime(CLOCK_REALTIME, &start);

                    querie1(UserController, line + 2, i);
                    
                    clock_gettime(CLOCK_REALTIME, &end);
                    timeQ1 += (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec)/1e9 ;
                    q1++;
                }
                break;

            case '2':
                // Limpa a string `country` antes de processar cada linha
                strcpy(country, "");

                // Lê o número e a string entre aspas, se existir
                int query2_result = sscanf(line + 1, "%d \"%[^\"]\"", &n, country);

                if (query2_result == 1) {
                    // Apenas o número foi lido, país não fornecido
                    strcpy(country, "");  // Define `country` como string vazia
                }

                clock_gettime(CLOCK_REALTIME, &start);
                // Executa a query 2
                querie2(ArtistContoller, n, i, country);
                clock_gettime(CLOCK_REALTIME, &end);
                timeQ2 += (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec)/1e9 ;
                q2++;
                break;

            case '3':
                sscanf(line + 1, "%d %d", &min, &max);
                clock_gettime(CLOCK_REALTIME, &start);

                querie3(i, min, max, UserController);
                clock_gettime(CLOCK_REALTIME, &end);
                timeQ3 += (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec)/1e9 ;
                q3++;
                break;

            default:
                break;
        }

        free(line);
        line = pegaLinha(parserT);

    }

    freeParser(parserT);






    int j;
    int passes = 0;

    for ( j = 0; j < i; j++) {
        // Nome do arquivo gerado
        char resultadoFile[256];
        sprintf(resultadoFile, "resultados/command%d_output.txt", j + 1);
        // Nome do arquivo esperado correspondente
        char esperadoFile[256];
        sprintf(esperadoFile, "%s/command%d_output.txt", outputEsperado, j + 1);

        // Contador de ocorrências corretas
        int ocorrenciasCorretas = 0;

        // Comparar os arquivos gerado e esperado linha a linha
        int iguais = compararFicheirosPorLinha(resultadoFile, esperadoFile, &ocorrenciasCorretas);
        if (iguais == 1) {
            printf("Test %d: PASS - %d ocorrências corretas\n", j + 1, ocorrenciasCorretas);
            passes++;
        } else {
            printf("Test %d: FAIL - %d ocorrências corretas\n\n", j + 1, ocorrenciasCorretas);
        }
    }




    printf("\nTempo médio da querie 1: %.6f ms\n",timeQ1/q1 * 1e3 );
    printf("Tempo médio da querie 2: %.6f ms\n",timeQ2/q2 * 1e3 );
    printf("Tempo médio da querie 3: %.6f ms\n",timeQ3/q3 * 1e3 );
    printf("\nA Querie 1 demorou na totalidade: %.6fms\n",timeQ1* 1e3);
    printf("A Querie 2 demorou na totalidade: %.6fms\n",timeQ2* 1e3);
    printf("A Querie 3 demorou na totalidade: %.6fms\n",timeQ3* 1e3);
    printf("\nForam executadas %d queries 1\n",q1);
    printf("Foram executadas %d queries 2\n",q2);
    printf("Foram executadas %d queries 3\n",q3);
    if (passes == (q1 + q2 + q3)) {
        printf(COLOR_GREEN "\nNão houve erros em nenhuma querie\n\n" COLOR_RESET);
    } else {
        printf(COLOR_RED "\nHouve erros em uma ou mais queries\n\n" COLOR_RESET);
    }

    destroyData(data);


    struct rusage r_usage;
    getrusage(RUSAGE_SELF,&r_usage);
    printf("%ld KB\n",r_usage.ru_maxrss);
    return 0;
}