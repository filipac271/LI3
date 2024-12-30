#include "ncurses.h"
#include "string.h"
#include <unistd.h>
#include "controler/mainController.h"
#include "controler/usersController.h"
#include "controler/artistsController.h"
#include "controler/mainController.h"
#include "controler/historyController.h"
#include "querie/querie1.h"
#include "querie/querie2.h"
#include "querie/querie3.h"
#include "querie/query4.h"
#include "querie/query5.h"



void capturarEntrada(WINDOW *window, int linha, int coluna, const char *mensagem, char *entrada, size_t tamanhoMaximo) {
    // Exibe a mensagem na posição indicada
    mvwprintw(window, linha, coluna, "%s", mensagem);
    
    // Coloca o cursor logo após a mensagem
    wmove(window, linha, coluna + strlen(mensagem));
    
    // Ativa a entrada do usuário
    echo();
    
    // Captura a entrada do usuário, limitando o número de caracteres
    mvwgetnstr(window, linha, coluna + strlen(mensagem), entrada, tamanhoMaximo - 1);
    
    // Desativa a entrada do usuário para não mostrar caracteres digitados
    noecho();
}



void interativo() {
    initscr();
    start_color();

    cbreak();
    noecho();
    int maxY, maxX;
    init_pair(1, COLOR_BLACK, COLOR_WHITE);
    getmaxyx(stdscr, maxY, maxX);  

    const char *message = "Insira a diretoria do dataset...";
    int startX = (maxX - strlen(message)) / 2; // Centraliza horizontalmente
    char diretoriaDataset[256];
    char queryInput[256];
    char argumentosQuery[256];

    WINDOW *full_window = newwin(maxY, maxX, 0, 0);
    box(full_window, 0, 0);
    wrefresh(full_window);

    wattron(full_window, A_BOLD | A_UNDERLINE | COLOR_PAIR(1));
    mvwprintw(full_window, 1, startX, "%s", message);
    wattroff(full_window, A_BOLD | A_UNDERLINE | COLOR_PAIR(1));


    capturarEntrada(full_window,2,1,"Diretoria: ",diretoriaDataset,sizeof(diretoriaDataset));


    wattron(full_window, A_BOLD);
    mvwprintw(full_window, 4, 1, "Processando os dados, por favor aguarde...");
    wattroff(full_window, A_BOLD);
    wrefresh(full_window);

    // Redirecionar stdout para /dev/null
    int saved_stdout = dup(fileno(stdout)); // Salvar stdout atual
    FILE *devnull = fopen("/dev/null", "w"); //Ficheiro que destroi tudo que vá para ele
    dup2(fileno(devnull), fileno(stdout)); // Redirecionar stdout para /dev/null

    MainController* data = mainFeed(diretoriaDataset); // Chamar função que usa printf

    // Restaurar stdout original
    fflush(stdout); // Volta stdout há normalidade
    dup2(saved_stdout, fileno(stdout)); // Restaurar stdout
    close(saved_stdout); //Fecha a copia
    fclose(devnull);

    capturarEntrada(full_window,5,1,"Dados processados com sucesso! Insira qual query deseja executar: ",queryInput,sizeof(queryInput));

    capturarEntrada(full_window,6,1,"Insira os argumentos para a query ",argumentosQuery,sizeof(argumentosQuery));


    wgetch(full_window);  // Espera o usuário pressionar uma tecla antes de sair

    destroyData(data);

    delwin(full_window);
    endwin();
}
