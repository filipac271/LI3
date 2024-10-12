#include "../../include/controler/usersController.h"
#include "../../include/controler/musicsController.h"
#include "parser/userParser.h"
#include "querie/querie3.h"

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

struct ageUsers
{
    char** likedSongs;
    int numberSongs;
};






void querie3(int num,GHashTable* music, int min , int max, Age* usersByAge)
{
    
  
   struct querie3 array[15];
   array[0].numMusicas=-1;


    for(int i=min;i<max+1 ;i++)
    {
      for(int j=0;j<usersByAge[i].numberSongs;j++)
      {     
         MusicData* song= lookup_musica(music,usersByAge[i].likedSongs[j]);
        
         char* genero=get_music_genre(song);
         int inserido=0;
         int a;
       //Ver se o genero está presente no array 
         for( a=0;array[a].numMusicas!=-1 && !inserido;a++)
         {
            if(strcmp(array[a].genero,genero)==0)
            {
               array[a].numMusicas++;
               inserido=1;
               //printf("%s\n",array[a].genero);

              
            }
           
         }
         //insere o genero se nao estiver no array
         if(!inserido)
         {
            array[a].genero=genero;
            array[a].numMusicas=1;
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
  FILE *output_file = fopen(filename, "w");

if(array[0].numMusicas==-1)
{
  int fd = fileno(output_file);  // Get the file descriptor
        ftruncate(fd, 0);
     
}
   for(int i=0;array[i].numMusicas!=-1;i++)
   {
       fprintf(output_file,"%s;%d\n",array[i].genero,array[i].numMusicas);
      
   }
  
 


fclose(output_file);
  free(filename);

 
   
}

