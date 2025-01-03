#ifndef MAINMODE_H
#define MAINMODE_H

/**
 * @brief Função principal que executa o programa.
 * 
 * Esta função é responsável por orquestrar a execução do programa. Ela realiza as seguintes tarefas:
 * - Chama a função `mainFeed` para processar o dataset e obter o controlador principal (`MainController`).
 * - Verifica se os dados foram carregados corretamente. Se falhar ao carregar os dados, a função retorna um código de erro (1).
 * - Exibe todas as HashTables principais utilizando a função `print_all_Data`.
 * - Executa as queries com base no arquivo de queries fornecido, utilizando a função `queries`.
 * - Libera toda a memória alocada durante a execução, utilizando a função `destroyData`.
 * 
 * @param pastaPrincipal Diretório onde está localizado o dataset.
 * @param queriesFile Caminho para o arquivo de queries a serem executadas.
 * 
 * @return Retorna 0 se o programa for executado com sucesso, ou 1 em caso de falha no carregamento dos dados.
 */
int principal(char* pastaPrincipal , char* queriesFile);


#endif