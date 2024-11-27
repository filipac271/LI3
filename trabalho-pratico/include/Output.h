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
void output1(Output* output1, char* userEmail, char* userNome, char* userApelido,int idade, char* userCountry,char c);

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


#endif