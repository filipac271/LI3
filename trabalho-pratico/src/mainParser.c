#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "../include/artistsParser.h"


  void parser(FILE** ficheiros){

     for (int i = 0; i < 3; i++)
    {


          // Verifica se o ficheiro foi aberto corretamente
        if (ficheiros[i] == NULL) {
            printf("Erro: Ficheiro %d não foi aberto corretamente.\n", i);
            continue;  // Ignora este ficheiro e passa para o próximo
        }


          
        switch (i)
            {
            case 0 :
                parser_artists(ficheiros[0]);
                break;

             case 1 :
                parser_artists(ficheiros[1]);

                 break;  

             case 2 :
                parser_artists(ficheiros[2]);
                    
                 break;

             default:
                break;
            }    
    }
    
    



   }