#define _GNU_SOURCE and #define _POSIX_C_SOURCE 1999309L
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
int teste(char* pastaPrincipal,char* queriesFile,char* outputEsperado) {
    printf("Entrada nos testes (Mooshak) \n");

    struct timespec start, end;

    float timeQ1 = 0;
    float timeQ2 = 0;
    float timeQ3 = 0;

    int q1 = 0;
    int q2 = 0;
    int q3 = 0;


    Parser* parserT = newParser(queriesFile,"");
    MainController* data = mainFeed(pastaPrincipal);

    char* line = NULL;  
    line = pegaLinha(parserT);


    int i = 0;

    //For loop que mede os tempos de cada querie
    for (i = 0; line != NULL ; i++) {

        //Pega controladores
        UsersData* UserController = getUserController(data);
        ArtistsData* ArtistContoller = getartistController(data);

        switch (line[0]) {
            case '1':
                

                    clock_gettime(CLOCK_REALTIME, &start);

                    querie1(UserController, line + 2, i);
                    
                    clock_gettime(CLOCK_REALTIME, &end);

                    //Tempo unico desta chamada da querie1
                    timeQ1 += (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec)/1e9 ;
                    q1++;
                
                break;

            case '2':

                clock_gettime(CLOCK_REALTIME, &start);
                
                querie2(ArtistContoller, line, i);

                clock_gettime(CLOCK_REALTIME, &end);

                //Tempo unico desta chamada da querie2
                timeQ2 += (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec)/1e9 ;
                q2++;
                break;

            case '3':
                clock_gettime(CLOCK_REALTIME, &start);

                querie3(i, line, UserController);
                clock_gettime(CLOCK_REALTIME, &end);

                //Tempo unico desta chamada da querie3
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
    int correctLine = 0;

    //For loop que faz comparação dos resultados com os outputs esperados
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
        int numLinesResult = contar_linhas(resultadoFile);
        int numLinesEsperado = contar_linhas(esperadoFile);
        if (iguais == 1 ) {
                printf("Test %d: PASS - %d ocorrências corretas\n", j + 1, ocorrenciasCorretas);
                correctLine++;
        } else {
            printf("Test %d: FAIL - %d ocorrências corretas\n\n", j + 1, ocorrenciasCorretas);
        }

        if (!(numLinesEsperado == numLinesResult))
        {    
            printf(COLOR_RED"Test %d: FAIL - Os dois ficheiros não contem o mesmo número de linhas\n\n" COLOR_RESET,j+1);
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

    int validLinesA = 1;
    int validLinesM = 1;
    int validLinesU = 1;

    if(strcmp(pastaPrincipal,"../../dataset/com_erros/") == 0){
        validLinesA = contar_linhas("resultados/artists_errors.csv");
        validLinesM = contar_linhas("resultados/musics_errors.csv");
        validLinesU = contar_linhas("resultados/users_errors.csv");

            if(validLinesA == 151){
                printf(COLOR_GREEN "\nNumero de linhas do artists_error:%d\n" COLOR_RESET,validLinesA);
            }else{
                printf(COLOR_RED "\nNumero de linhas do artists_error:%d\n" COLOR_RESET,validLinesA);
            }

            if(validLinesM == 18882){
                printf(COLOR_GREEN "\nNumero de linhas do musics_error:%d\n" COLOR_RESET,validLinesM);
            }else{
                printf(COLOR_RED "\nNumero de linhas do musics_error:%d\n" COLOR_RESET,validLinesM);
            }

            if(validLinesU == 37501){
                printf(COLOR_GREEN "\nNumero de linhas do users_errors:%d\n" COLOR_RESET,validLinesU);
            }else{
                printf(COLOR_RED "\nNumero de linhas do users_errors:%d\n" COLOR_RESET,validLinesU);
            }
    }else{


            if(validLinesA == 1){
                printf(COLOR_GREEN "\nNumero de linhas do artists_error:%d\n" COLOR_RESET,validLinesA);
            }else{
                printf(COLOR_RED "\nNumero de linhas do artists_error:%d\n" COLOR_RESET,validLinesA);
            }

            if(validLinesM == 1){
                printf(COLOR_GREEN "\nNumero de linhas do musics_error:%d\n" COLOR_RESET,validLinesM);
            }else{
                printf(COLOR_RED "\nNumero de linhas do musics_error:%d\n" COLOR_RESET,validLinesM);
            }

            if(validLinesU == 1){
                printf(COLOR_GREEN "\nNumero de linhas do users_errors:%d\n" COLOR_RESET,validLinesU);
            }else{
                printf(COLOR_RED "\nNumero de linhas do users_errors:%d\n" COLOR_RESET,validLinesU);
            }
    }


    
    
    

    if (correctLine == (q1 + q2 + q3)) {
        printf(COLOR_GREEN "\nNão houve erros em nenhuma querie\n\n" COLOR_RESET);
    } else {
        printf(COLOR_RED "\nHouve erros em uma ou mais queries\n\n" COLOR_RESET);
    }

    destroyData(data);

    //Código que mede o pico máximo de memoria a ser usada no programa no final do "principal" ser rodado
    struct rusage r_usage;
    getrusage(RUSAGE_SELF,&r_usage);
    printf("%ld KB\n",r_usage.ru_maxrss);
    return 0;
}