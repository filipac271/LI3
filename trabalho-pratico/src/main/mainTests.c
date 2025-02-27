#define _GNU_SOURCE and #define _POSIX_C_SOURCE 1999309L
#include "controler/mainController.h"
#include "controler/historyController.h"
#include "query/queryManager.h"
#include "Input.h"
#include "query/query1.h"
#include "query/query2.h"
#include "query/query3.h"
#include "query/query4.h"
#include "query/query5.h"
#include "query/query6.h"

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
    float timeQ4 = 0;
    float timeQ5 = 0;
    float timeQ6 = 0;


    int q1 = 0;
    int q2 = 0;
    int q3 = 0;
    int q4 = 0;
    int q5 = 0;
    int q6 = 0;



    Parser* parserT = newParser(queriesFile,"");
    MainController* data = mainFeed(pastaPrincipal);
    if(data == NULL)return 1;



    print_all_Data(data);

    char* line = NULL;  
    line = pegaLinha(parserT);

    //Pega controladores
    UsersData* UserController = getUserController(data);
    ArtistsData* ArtistController = getartistController(data);
    HistoryData* HistoryController = gethistoryController(data);
    MusicData* musicController=getMusicController(data);
    AlbumsData* albumController=getalbumController(data);

    int** elementosMatriz = getElementosMatrizQ5(UserController);
    char** idsUsers = getLinhasMatrizQ5(UserController);
    char** nomesGeneros = getColunasMatrizQ5(UserController);

    int i = 0;
    //Esta flag está aqui apenas para as queries 4 5 6 n serem rodadas
    int flag = 1;
    //For loop que mede os tempos de cada querie
    for (i = 0; line != NULL && flag ; i++) {

        switch (line[0]) {
            case '1':
                

                    clock_gettime(CLOCK_REALTIME, &start);

                    query1(UserController, line , i,ArtistController);
                    
                    clock_gettime(CLOCK_REALTIME, &end);

                    //Tempo unico desta chamada da querie1
                    timeQ1 += (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec)/1e9 ;
                    q1++;
                
                break;

            case '2':

                clock_gettime(CLOCK_REALTIME, &start);
                
                query2(ArtistController, line, i);

                clock_gettime(CLOCK_REALTIME, &end);

                //Tempo unico desta chamada da querie2
                timeQ2 += (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec)/1e9 ;
                q2++;
                break;

            case '3':
                clock_gettime(CLOCK_REALTIME, &start);

                query3(i, line, UserController);
                clock_gettime(CLOCK_REALTIME, &end);

                //Tempo unico desta chamada da querie3
                timeQ3 += (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec)/1e9 ;
                q3++;
                break;

            case '4':
                clock_gettime(CLOCK_REALTIME, &start);

                query4(HistoryController, ArtistController, line, i );
                clock_gettime(CLOCK_REALTIME, &end);

                //Tempo unico desta chamada da querie3
                timeQ4 += (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec)/1e9 ;
                q4++;
                break;
            case '5':
                clock_gettime(CLOCK_REALTIME, &start);

                query5(line,i,UserController,elementosMatriz,idsUsers,nomesGeneros);
                clock_gettime(CLOCK_REALTIME, &end);

                //Tempo unico desta chamada da querie3
                timeQ5 += (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec)/1e9 ;
                q5++;
                break;
             case '6':
                clock_gettime(CLOCK_REALTIME, &start);

                query6(i,line, HistoryController, musicController, albumController);
                clock_gettime(CLOCK_REALTIME, &end);

                //Tempo unico desta chamada da querie3
                timeQ6 += (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec)/1e9 ;
                q6++;
                break;

            default:
                // flag = 0;
                // i -=1;
                break;
        }

        free(line);
        line = pegaLinha(parserT);

    }

    freeQ5Matrizes(elementosMatriz,idsUsers,nomesGeneros,UserController);
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




    printf("\nTempo médio da query 1: %.6f ms\n",timeQ1/q1 * 1e3 );
    printf("Tempo médio da query 2: %.6f ms\n",timeQ2/q2 * 1e3 );
    printf("Tempo médio da query 3: %.6f ms\n",timeQ3/q3 * 1e3 );
    printf("Tempo médio da query 4: %.6f ms\n",timeQ4/q4 * 1e3 );
    printf("Tempo médio da query 5: %.6f ms\n",timeQ5/q5 * 1e3 );
     printf("Tempo médio da query 6: %.6f ms\n",timeQ6/q6 * 1e3 );
     
    printf("\nA Query 1 demorou na totalidade: %.6fms\n",timeQ1* 1e3);
    printf("A Query 2 demorou na totalidade: %.6fms\n",timeQ2* 1e3);
    printf("A Query 3 demorou na totalidade: %.6fms\n",timeQ3* 1e3);
    printf("A Query 4 demorou na totalidade: %.6fms\n",timeQ4* 1e3);
    printf("A Query 5 demorou na totalidade: %.6fms\n",timeQ5* 1e3);
    printf("A Query 6 demorou na totalidade: %.6fms\n",timeQ6* 1e3);
    
    printf("\nForam executadas %d queries 1\n",q1);
    printf("Foram executadas %d queries 2\n",q2);
    printf("Foram executadas %d queries 3\n",q3);
    printf("Foram executadas %d queries 4\n",q4);
    printf("Foram executadas %d queries 5\n",q5);
    printf("Foram executadas %d queries 6\n",q6);    


    int validLinesA = 1;
    int validLinesM = 1;
    int validLinesU = 1;

    if(strcmp(pastaPrincipal,"../../dataset/com_erros/") == 0){
        validLinesA = contar_linhas("resultados/artists_errors.csv");
        validLinesM = contar_linhas("resultados/musics_errors.csv");
        validLinesU = contar_linhas("resultados/users_errors.csv");

            if(validLinesA == 1501){
                printf(COLOR_GREEN "\nNumero de linhas do artists_error:%d\n" COLOR_RESET,validLinesA);
            }else{
                printf(COLOR_RED "\nNumero de linhas do artists_error:%d\n" COLOR_RESET,validLinesA);
            }

            if(validLinesM == 15648){
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


    
    
    


    if (correctLine == (q1 + q2 + q3+ q4 +q5 + q6)) {
        printf(COLOR_GREEN "\nNão houve erros em nenhuma query\n\n" COLOR_RESET);
    } else {
        printf(COLOR_RED "\nHouve erros em uma ou mais queries\n\n" COLOR_RESET);
    }


    destroyData(data);
    struct rusage r_usage;
    getrusage(RUSAGE_SELF,&r_usage);
    printf("%ld KB\n",r_usage.ru_maxrss);

    return 0;
}