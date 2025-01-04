#ifndef OUTPUT
#define OUTPUT


/**
 * @typedef Output
 * @brief Representa um objeto de saída de dados.
 */
typedef struct output Output;



/**
 * @brief Inicializa um objeto de saída de dados.
 * 
 * @param filename O nome do ficheiro de saída.
 * @return Um ponteiro para o objeto de saída de dados inicializado.
 */
Output* iniciaOutput(char* filename);

/**
 * @brief Liberta a memória alocada para um objeto de saída de dados.
 * 
 * @param output O objeto de saída de dados a libertar.
 */
void freeOutput(Output* output);

/**
 * @brief Escreve uma saída nula.
 * 
 * @param output3 O objeto de saída de dados.
 */
void outputNULL(Output* output3);

/**
 * @brief Regista erros num ficheiro de saída.
 * 
 * @param erros O objeto de saída para erros.
 * @param linha A linha de erro a registar.
 */
void outputErros(Output* erros, char* linha);

/**
 * @brief Escreve os dados de um utilizador num ficheiro de saída.
 * 
 * @param output1 O objeto de saída de dados.
 * @param userEmail O email do utilizador.
 * @param userNome O primeiro nome do utilizador.
 * @param userApelido O apelido do utilizador.
 * @param idade A idade do utilizador.
 * @param userCountry O país do utilizador.
 */
void output1(Output* output1, void* arg1, void* arg2, void* arg3,void* arg4, void* arg5, char c,int isArtist);

/**
 * @brief Escreve os dados de uma música num ficheiro de saída.
 * 
 * @param output2 O objeto de saída de dados.
 * @param nome O nome do artista.
 * @param tipo O tipo do artista.
 * @param time A duração das musicas do respetivo artista.
 * @param pais O país de origem do artista.
 */
void output2(Output* output2, char* nome, char* tipo, char* time,char* pais, char c);

/**
 * @brief Escreve as estatísticas de um género musical num ficheiro de saída.
 * 
 * @param output3 O objeto de saída de dados.
 * @param genero O género musical.
 * @param num O número de ocorrências.
 */
void output3(Output* output3, char* genero, int num, char c);

/**
 * @brief Função de saída para a Query 4.
 * 
 * A função imprime informações no arquivo de saída associada à estrutura `Output`.
 * Dependendo do valor do caractere `c`, a formatação será diferente:
 * - Se `c` for 'S', a saída será no formato "name=name;num".
 * - Caso contrário, a saída será no formato "name;type;num".
 * 
 * @param output4 A estrutura `Output` contendo o arquivo de saída.
 * @param name O nome a ser impresso.
 * @param type O tipo a ser impresso.
 * @param num O número a ser impresso.
 * @param c Caractere que determina o formato da saída ('S' ou outro).
 */
void output4(Output* output4, char* name, char* type, int num, char c);

/**
 * @brief Função de saída para a Query 5.
 * 
 * A função imprime os usernames no arquivo de saída associado à estrutura `Output`. 
 * Para cada recomendação, um nome de usuário será impresso, seguido de uma nova linha.
 * 
 * @param output5 A estrutura `Output` contendo o arquivo de saída.
 * @param usernames Um array de strings com os nomes de usuário a serem impressos.
 * @param numrecomendacoes O número total de recomendações a serem processadas.
 */
void output5(Output* output5, char** usernames, int numrecomendacoes);





void output6(char c, Output* output6, char* tempoAudicao,int nMusicas,char* artistId,char* data,char* genero,char* album, char* hora,int N);





#endif