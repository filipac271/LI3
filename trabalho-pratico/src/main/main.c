#include "main/mainMode.h"
#include "main/mainTests.h"
#include "main/maininterativo.h"

#include <stdio.h> 
#include <stdlib.h>
#include <sys/resource.h>


/* PEQUENA NOTA DOS FICHEIROS .H JÁ ALTERADOS:
    utilidades.h
    

*/

int main(int argc, char **argv){
    if(argc == 3){
    
        int runned = principal(argv[1], argv[2]);
        if(runned == 1){
            printf("A diretoria do dataset é inválida\n");
            return 1;
        }


        //Código que mede o pico máximo de memoria a ser usada no programa no final do "principal" ser rodado
        struct rusage r_usage;
        getrusage(RUSAGE_SELF,&r_usage);
        printf("%ld KB\n",r_usage.ru_maxrss);



    }
    else if (argc == 4){
        int runned = teste(argv[1],argv[2],argv[3]);
        
        if(runned == 1){
            printf("A diretoria do dataset é inválida\n");
            return 1;
        }

    }
    else if (argc == 1){
        interativo();
    }

return 0;

}