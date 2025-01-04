#ifndef MAININTERATIVO_H
#define MAININTERATIVO_H


/**
 * @brief Função principal para o programa interativo.
 * 
 * Esta função executa a interface interativa do programa utilizando a biblioteca ncurses.
 * Ela exibe uma janela no terminal onde o usuário pode interagir com o sistema.
 * A função permite que o usuário escolha entre usar a diretoria padrão ou inserir um novo caminho para o dataset.
 * Após o processamento dos dados, o usuário pode executar diversas queries, ou finalizar o programa.
 * 
 * A função possui as seguintes etapas:
 * - Exibe uma mensagem de boas-vindas.
 * - Pergunta ao usuário se ele deseja usar a diretoria padrão para o dataset ou se prefere inserir um novo caminho.
 * - Processa os dados do dataset especificado.
 * - Permite ao usuário executar queries e visualizar os resultados.
 * - O usuário pode repetir a execução das queries ou sair do programa.
 */
void interativo();


#endif