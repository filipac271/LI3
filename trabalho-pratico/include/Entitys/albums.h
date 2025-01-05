#ifndef ALBUMS_H
#define ALBUMS_H

/**
 * @typedef
 * @brief Estrutura que representa um album.
 */
typedef struct albums Album;

/**
 * @brief Cria um novo álbum a partir dos tokens fornecidos.
 * 
 * @param tokens Array de strings contendo os dados do álbum.
 * @return Ponteiro para a estrutura Album recém-criada.
 */
Album* createAlbum(char** tokens);

/**
 * @brief Busca o nome de um album.
 * 
 * @param album Ponteiro para o album.
 * @return Nome do album em formato string.
 */
char* getAlbumName(Album* album);

/**
 * @brief Libera a memória alocada para um álbum.
 * 
 * @param album Ponteiro para o álbum a ser liberado.
 */
void freeAlbum(Album* album);

/**
 * @brief Exibe as informações de um álbum no terminal.
 * 
 * @param album Ponteiro para o álbum a ser exibido.
 */
void printAlbum(Album* album);


#endif