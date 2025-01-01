#include "controler/usersController.h"
#include "controler/artistsController.h"
#include "controler/mainController.h"
#include "controler/historyController.h"
#include "querie/querie1.h"
#include "querie/querie2.h"
#include "querie/querie3.h"
#include "querie/query4.h"
#include "querie/query5.h"
#include "utilidades.h"
#include "Input.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <glib.h>
#include <ctype.h>

int validaQ1Input(char *argumentos,char possivelS)
{
    if (!(possivelS == 'S' || possivelS == '\0')){
        return 0;
    }
    if (strlen(argumentos) != 8)return 0;
    if(!(argumentos[0] == 'A' || argumentos[0] == 'U')) return 0;

    for (int i = 1; argumentos[i] != '\0'; i++)
    {
        if(!isdigit(argumentos[i]))return 0;
    }


    
    return 1;
}

int validaQ2Input(char *argumentos,char possivelS){

    if (!(possivelS == 'S' || possivelS == '\0')){
        return 0;
    }
    int n = -1;
    char country[256];
    sscanf(argumentos, "%d \"%[^\"]\"", &n, country);
    if (n < 0)return 0;


    return 1;
}

int validaQ3Input(char *argumentos,char possivelS){

    if (!(possivelS == 'S' || possivelS == '\0')){
        return 0;
    }

    int min, max;
    int result = sscanf(argumentos, "%d %d", &min, &max);

    if(min < 0) return 0;
    if(max < 0) return 0;    
    if(min > max) return 0;

    if(result != 2)return 0;

    return 1;

}
int validaQ4Input(char *argumentos,char possivelS){

    if (!(possivelS == 'S' || possivelS == '\0')){
        return 0;
    }

    char data_inicio[256] = ""; 
    char data_fim[256] = "";
    if(argumentos[0] == '\0')return 1;


    int query4_result = sscanf(argumentos, "%s %s", data_inicio, data_fim);
    if(query4_result != 2)return 0;

    int data1 = validaData(data_inicio);
    int data2 = validaData(data_fim);
    if(!data1) return 0;    

    if(!data2) return 0;

    int validaOrdem = verificaOrdemDatas(data_inicio,data_fim);

    if(!validaOrdem)return 0;


    return 1;
}
int validaQ5Input(char *argumentos,char possivelS){

    if (!(possivelS == 'S' || possivelS == '\0')){
        return 0;
    }

    char userID[256]; 
    int numrecomendacoes;

    int q5Result = sscanf(argumentos, "%s %d", userID, &numrecomendacoes);

    if(q5Result != 2)return 0;

    if (strlen(userID) != 8)return 0;

    if(numrecomendacoes < 0) return 0;

    if(!(userID[0] == 'A' || userID[0] == 'U')) return 0;

    for (int i = 1; userID[i] != '\0'; i++)
    {
        if(!isdigit(userID[i]))return 0;
    }


    return 1;
}
int validaQ6Input(char *argumentos,char possivelS){

    if (!(possivelS == 'S' || possivelS == '\0')){
        return 0;
    }

    char userId[256];
    int ano, N = -1;
    int q6Result = sscanf(argumentos, "%s %d %d",userId,&ano,&N);
    if(q6Result == 2){
        if (strlen(userId) != 8)return 0;
        if(ano < 0) return 0;
        if(!(userId[0] == 'A' || userId[0] == 'U')) return 0;

        for (int i = 1; userId[i] != '\0'; i++)
        {
            if(!isdigit(userId[i]))return 0;
        }
    
        }
    if(q6Result == 3){
        if (strlen(userId) != 8)return 0;
        if(ano < 0) return 0;
        if(N < 0) return 0;

        if(!(userId[0] == 'A' || userId[0] == 'U')) return 0;

        for (int i = 1; userId[i] != '\0'; i++)
        {
            if(!isdigit(userId[i]))return 0;
        }
    
    }
    if(q6Result < 2)return 0;
    if(q6Result > 3)return 0;

return 1;



}

void queries(MainController *data, char *querieFile)
{
    Parser *parserQ = newParser(querieFile, "");
    char *line = NULL;
    line = pegaLinha(parserQ);
    // Recupera controladores
    UsersData *UserController = getUserController(data);
    ArtistsData *ArtistController = getartistController(data);
    HistoryData *HistoryConctoller = gethistoryController(data);

    int **elementosMatriz = getElementosMatrizQ5(UserController);
    char **idsUsers = getLinhasMatrizQ5(UserController);
    char **nomesGeneros = getColunasMatrizQ5(UserController);

    int i = 0;
    for (i = 0; line != NULL; i++)
    {

        switch (line[0])
        {
        case '1':

            querie1(UserController, line, i, ArtistController);

            break;

        case '2':

            querie2(ArtistController, line, i);

            break;

        case '3':

            querie3(i, line, UserController);

            break;

        case '4':

            query4(HistoryConctoller, ArtistController, line, i);

            break;

        case '5':

            query5(line, i, UserController, elementosMatriz, idsUsers, nomesGeneros);

            break;
        default:
            break;
        }

        free(line);
        line = pegaLinha(parserQ);
    }
    freeQ5Matrizes(elementosMatriz, idsUsers, nomesGeneros, UserController);

    freeParser(parserQ);
}
