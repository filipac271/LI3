#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <glib.h>
#include <unistd.h>


int validaUser(char* email, char* date, char* type){
    int t = 1;
    int d = 1;
    int e = 1;
    if (!(strcmp(type, "premium") == 0 || strcmp(type, "normal") == 0)) t = 0;

    
return (t & d & e);

}
