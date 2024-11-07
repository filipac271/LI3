#include "../../include/controler/usersController.h"
#include "../../include/controler/musicsController.h"
#include "controler/usersController.h"
#include "utilidades.h"
#include "Entitys/musics.h"
#include "Entitys/users.h"
#include "querie/querie3.h"
#include "IOManager.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <glib.h>
#include <unistd.h> 

struct querie3
{
   char* genero;
   int numMusicas;
};




void querie3(int num, int min , int max, UsersData* userController)
{
    
  
   Genero array[15];
   array[0].numMusicas=-1;

    for(int i=min;i<max+1 ;i++)
    {
     
      for(int j=0;j<getUBANGeneros(userController,i);j++)  
      {     
       
         int inserido=0;
         int a;
         char* genero = getUBAGenero(userController,i,j);   
         int numSongs= getUBANSongs( userController,i,j); 
       //Ver se o genero está presente no array 
         for( a=0;array[a].numMusicas!=-1 && !inserido;a++)
         {
            if(strcmp(array[a].genero,genero)==0)
            {
               array[a].numMusicas+=numSongs ;
               inserido=1;
             

              
            }
           
         }
         //insere o genero se nao estiver no array
         if(!inserido)
         {
            array[a].genero=genero;
            array[a].numMusicas=numSongs;
            array[a+1].numMusicas=-1;
            //printf("%s\n",array[a].genero);

         }
    
      }
   
   }


if(array[0].numMusicas!=-1)
{

   
    for (int i = 1; array[i].numMusicas!=-1; i++) {
      struct querie3 key=array[i];
        int  nm = array[i].numMusicas;  // Elemento a ser inserido na posição correta
       char* gnr = array[i].genero;
        int j = i - 1;

        // Move os elementos do array que são maiores que o "key" para uma posição à frente
        while (j >= 0 && (array[j].numMusicas < nm || (array[j].numMusicas == nm && strcmp(gnr,array[j].genero)<0))) {
            array[j + 1] = array[j];
            j = j - 1;
        }
        
        // Insere o "key" na posição correta
        array[j + 1] = key;
    }
}

    char *filename = malloc(sizeof(char) * 256);
  sprintf(filename, "resultados/command%d_output.txt",num+1);
   Output* output= iniciaOutput(filename);

if(array[0].numMusicas==-1)
{
   
  outputNULL(output);
     
}
   for(int i=0;array[i].numMusicas!=-1;i++)
   {
     output3(output, array[i].genero,array[i].numMusicas);
      
   }
  
 
freeOutput (output);


  free(filename);

 
   
}


