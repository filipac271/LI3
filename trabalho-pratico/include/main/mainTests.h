#ifndef MAINTESTS_H
#define MAINTESTS_H

/**
 * @brief Função que executa os testes e mede o desempenho das queries.
 * 
 * Esta função realiza os seguintes passos:
 * - Inicializa o parser e os controladores de dados.
 * - Executa as queries 1 a 5 em loop, registrando os tempos de execução de cada uma.
 * - Compara os resultados gerados com os arquivos esperados e imprime os resultados.
 * - Calcula o tempo total e médio de cada query.
 * - Verifica a quantidade de erros nas linhas dos arquivos de saída.
 * - Exibe os tempos de execução das queries e a quantidade de erros encontrados.
 * - Libera a memória utilizada pelos dados e pelo parser.
 * 
 * @param pastaPrincipal Caminho para o diretório onde os dados de entrada estão armazenados.
 * @param queriesFile Caminho para o arquivo contendo as queries a serem executadas.
 * @param outputEsperado Caminho para o diretório onde os arquivos de saída esperados estão localizados.
 * 
 * @return Retorna 1 caso n tenha conseguido executar testes devido a falha no carregamento dos dados, retorna 0 caso contrário
 * 
 */
int teste(char* pastaPrincipal, char* queriesFile, char* outputEsperado);

#endif