#ifndef VALIDAMUSICS_H
#define VALIDAMUSICS_H
#include "controler/artistsController.h"
#include "controler/albumsController.h"
#include "Output.h"

/**
 * @brief Função para validar as informações de uma música.
 * 
 * Esta função valida a duração de uma música, verifica se os artistas estão registrados no controlador de artistas e
 * se o álbum associado à música está presente no controlador de álbuns. A música será considerada válida se:
 * 1. A duração for válida (através da função `validaDuracao`).
 * 2. A lista de artistas estiver bem formatada (iniciada com `[`).
 * 3. Cada artista na lista for encontrado no controlador de artistas.
 * 4. O álbum associado for encontrado no controlador de álbuns.
 * Se qualquer uma dessas condições falhar, um erro será registrado.
 * 
 * @param duracaoAspas Duração da música entre aspas.
 * @param music_artists Lista de artistas associados à música, formatada entre `[]`.
 * @param artistsController Ponteiro para o controlador de artistas.
 * @param Erros Ponteiro para a estrutura de erros, onde as mensagens de erro serão armazenadas.
 * @param linha Linha de entrada contendo os dados da música.
 * @param albumController Ponteiro para o controlador de álbuns.
 * @param albumId ID do álbum associado à música.
 * @return Retorna 1 se todas as validações forem bem-sucedidas, 0 caso contrário.
 */
int validaMusic(char *duracaoAspas, char *music_artists, ArtistsData *artistsController, Output *Erros, char *linha, AlbumsData *albumController, char *albumId);

#endif