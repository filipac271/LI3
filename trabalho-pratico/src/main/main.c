#include "main/mainMode.h"
#include "main/mainTests.h"

#include <stdio.h> 
#include <stdlib.h>
#include <sys/resource.h>

int main(int argc, char **argv){
    if(argc == 3){
    
        principal(argv[1], argv[2]);
    
        struct rusage r_usage;
        getrusage(RUSAGE_SELF,&r_usage);
        printf("%ld KB\n",r_usage.ru_maxrss);
    }
    else if (argc == 4){
        teste(argv);
    }

}