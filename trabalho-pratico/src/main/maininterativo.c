#include "ncurses.h"
#include "string.h"
#include <unistd.h>
#include "controler/mainController.h"
#include "controler/usersController.h"
#include "controler/artistsController.h"
#include "controler/mainController.h"
#include "controler/historyController.h"
#include "Input.h"
#include "querie/querieManager.h"
#include "querie/querie1.h"
#include "querie/querie2.h"
#include "querie/querie3.h"
#include "querie/query4.h"
#include "querie/query5.h"


void capturarEntrada(WINDOW *window, int *linha, int coluna, const char *mensagem, char *entrada, size_t tamanhoMaximo) {
    // Exibe a mensagem na posição indicada
    mvwprintw(window, *linha, coluna, "%s", mensagem);
    
    // Coloca o cursor logo após a mensagem
    wmove(window, *linha, coluna + strlen(mensagem));
    
    // Ativa a entrada do usuário
    echo();
    
    // Captura a entrada do usuário, limitando o número de caracteres
    mvwgetnstr(window, *linha, coluna + strlen(mensagem), entrada, tamanhoMaximo - 1);
    
    // Desativa a entrada do usuário para não mostrar caracteres digitados
    noecho();
    
    // Incrementa a linha atual
    (*linha)++;
}


int validaInputs (char* argumentos,char* query){
    int q = query[0] - '0';    
    int validade = 0;
    switch (q)
    {
    case 1:
        validade =validaQ1Input(argumentos,query[1]);
        break;
    case 2:
        validade = validaQ2Input(argumentos,query[1]);
        break;
    case 3:
        validade = validaQ3Input(argumentos,query[1]);
        break;
    case 4:
        validade = validaQ4Input(argumentos,query[1]);
        break;
    case 5:
        validade = validaQ5Input(argumentos,query[1]);
        break;
    case 6:
        validade = validaQ6Input(argumentos,query[1]);
        break;
    default:
        return 0;
        break;
    }
    return validade;
}

void querieManagerInt(char* argumentos,char* query,MainController* data){
    UsersData *UserController = getUserController(data);
    ArtistsData *ArtistController = getartistController(data);
    HistoryData *HistoryConctoller = gethistoryController(data);

    int **elementosMatriz = getElementosMatrizQ5(UserController);
    char **idsUsers = getLinhasMatrizQ5(UserController);
    char **nomesGeneros = getColunasMatrizQ5(UserController);

    char line[256];
    snprintf(line,sizeof(line),"%s %s",query,argumentos);

        switch (query[0])
        {
        case '1':

            querie1(UserController, line, 0, ArtistController);

            break;

        case '2':

            querie2(ArtistController, line, 0);

            break;

        case '3':

            querie3(0, line, UserController);

            break;

        case '4':

            query4(HistoryConctoller, ArtistController, line, 0);

            break;

        case '5':

            query5(line, 0, UserController, elementosMatriz, idsUsers, nomesGeneros);

            break;
        default:
            break;
        }

        
        
    freeQ5Matrizes(elementosMatriz, idsUsers, nomesGeneros, UserController);

}
void printaNcursesQ(WINDOW *full_window,int* currentY){

    Parser* parser = newParser("./resultados","command1_output.txt");
    char* output;
    while (1)
    {
        output = pegaLinha(parser);
        if(output == NULL)break;
        mvwprintw(full_window, (*currentY)++, 1, "Output: %s", output);
        free(output);
    }
        wmove(full_window,*currentY,1);
    

    

    freeParser(parser);

    remove("./resultados/command1_output.txt");


}


void processaQueries(WINDOW *full_window, int *currentY, MainController* data) {
    char queryInput[256];
    char argumentosQuery[256];

    capturarEntrada(full_window, currentY, 1, "Dados processados com sucesso! Insira qual query deseja executar: ", queryInput, sizeof(queryInput));
    capturarEntrada(full_window, currentY, 1, "Insira os argumentos para a query: ", argumentosQuery, sizeof(argumentosQuery));
    int valido = validaInputs(argumentosQuery, queryInput);
    if (valido) {
        querieManagerInt(argumentosQuery, queryInput,data);
        printaNcursesQ(full_window,currentY);
    } else {
        wattron(full_window, A_BOLD | A_UNDERLINE);
        mvwprintw(full_window, (*currentY)++, 1, "Input inválido.");
        wattroff(full_window, A_BOLD | A_UNDERLINE);
    }
}

void interativo() {
    initscr();
    start_color();

    cbreak();
    noecho();
    int maxY, maxX, currentY = 1; // Variável para rastrear a linha atual
    init_pair(1, COLOR_BLACK, COLOR_WHITE);
    getmaxyx(stdscr, maxY, maxX);  

    const char *message = "Programa Interativo";
    int startX = (maxX - strlen(message)) / 2; // Centraliza horizontalmente
    char diretoriaDataset[256];
    char* diretoriaDefault = "../../dataset/com_erros";
    char quererDefault[256];
    int processouData = 0;
    int primeiraIteracao = 1;
    int ch = 0;
    char continuar[2];
    MainController* data;

    WINDOW *full_window = newwin(maxY, maxX, 0, 0);
    scrollok(full_window, TRUE); // Habilita o scroll automático para a janela
    box(full_window, 0, 0);
    wrefresh(full_window);

    wattron(full_window, A_BOLD | A_UNDERLINE | COLOR_PAIR(1));
    mvwprintw(full_window, currentY++, startX, "%s", message); 
    wattroff(full_window, A_BOLD | A_UNDERLINE | COLOR_PAIR(1));

    while (1) {
        if (!primeiraIteracao) {
            ch = wgetch(full_window); 
            if (ch == 27) {
                break; 
            }
        }

            capturarEntrada(full_window,&currentY,1,"Quer usar a diretoria default? (y or n) ",quererDefault,sizeof(quererDefault));
        if(quererDefault[0] == 'n'){
            capturarEntrada(full_window, &currentY, 1, "Insira a Diretoria para o dataset: ", diretoriaDataset, sizeof(diretoriaDataset));
        }


        wattron(full_window, A_BOLD);
        mvwprintw(full_window, currentY++, 1, "Processando os dados, por favor aguarde...");
        wattroff(full_window, A_BOLD);
        wrefresh(full_window);

        // Redirecionar stdout para /dev/null
        int saved_stdout = dup(fileno(stdout)); // Salvar stdout atual
        FILE *devnull = fopen("/dev/null", "w"); // Ficheiro que descarta o output
        dup2(fileno(devnull), fileno(stdout)); // Redirecionar stdout para /dev/null

        if(quererDefault[0] == 'n'){
            data = mainFeed(diretoriaDataset); // Chamar função que usa printf
        }
        if(quererDefault[0] == 'y'){
            data = mainFeed(diretoriaDefault); // Chamar função que usa printf
        }

        // Restaurar stdout original
        fflush(stdout); // Volta stdout à normalidade
        dup2(saved_stdout, fileno(stdout)); // Restaurar stdout
        close(saved_stdout); // Fecha a cópia
        fclose(devnull);
        
        if (data == NULL) {
            mvwprintw(full_window, currentY++, 1, "Diretoria inválida.");
            mvwprintw(full_window, currentY++, 1, "Se quiser acabar o programa clique Esq caso contrário clique qualquer outra letra ");
            wrefresh(full_window);
            primeiraIteracao = 0;
            continue;
        }

        processouData = 1;
        processaQueries(full_window, &currentY, data);
        
        while (1)
        {
            capturarEntrada(full_window,&currentY,1,"Deseja executar mais queries? Insira y se sim ou n se não:",continuar,sizeof(continuar));
            if(continuar[0] == 'y'){
                processaQueries(full_window, &currentY, data);

            }
            if(continuar[0] == 'n')break;

        }
        

        break;
    }

    if (ch == 27) {
        delwin(full_window);
        endwin(); 
    }

    if (processouData) {
        mvwprintw(full_window, currentY++, 1, "Digite qualquer tecla para acabar o programa");

        ch = wgetch(full_window); 
        if (ch) {
            delwin(full_window);
            endwin(); 
            destroyData(data);  
        }
    }
}

