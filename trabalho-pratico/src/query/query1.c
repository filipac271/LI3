
#include "controler/usersController.h"
#include "controler/artistsController.h"
#include "Entities/artists.h"
#include "Entities/users.h"
#include "Output.h"
#include "utilidades.h"

#include <stdio.h>
#include <stdlib.h>
#include <glib.h>
#include <unistd.h> 



void query1(UsersData* userController, char* line,int i, ArtistsData* artistController){

char *filename = malloc(sizeof(char) * 256);
sprintf(filename, "resultados/command%d_output.txt",i+1);

char* idChar= line+3;
char c = line[1];

Output* output= iniciaOutput(filename);

int id = transformaIds(idChar);

int decidingFlag = 0;

if(c == 'S'){
      if(line[3] == 'U') decidingFlag = 1;
      if(line[3] == 'A') decidingFlag = 2;
}
else{
      if(line[2] == 'U')  decidingFlag = 1;
      if(line[2] == 'A') decidingFlag = 2;  
}


 


char* userBirthDate ;
char* userEmail;
char* userNome;
char* userApelido;
char* userCountry;

char* artistName;
char* artistType;
char* artistCountry;
int numAlbunsIndividual;
double totalRecipe;

if (decidingFlag == 1)
{ 
      if(isUserValid(userController,id)){
            outputNULL(output);
            free(filename);
            freeOutput(output);
            return;
      }
      userBirthDate = getUserBirthDateControl(userController,id);
      userEmail =getUserEmailControl(userController,id);
      userNome =getUserNomeControl(userController,id);
      userApelido =getUserApelidoControl(userController,id);
      userCountry =getUserCountryControl(userController,id);
   
      int idade = calcular_idade(userBirthDate);
   
      output1(output,userEmail,userNome,userApelido,&idade, userCountry,c,0);
      free(userBirthDate);
      free(userEmail);
      free(userNome);
      free(userApelido);
      free(userCountry);

}else if (decidingFlag == 2){
      if(isArtistValid(artistController,id)){
            outputNULL(output);
            free(filename);
            freeOutput(output);
            return;
      }
      artistName = getArtistNameControl(artistController,id);
      artistType =getArtistTypeControl(artistController,id);
      artistCountry = getArtistCountryControl(artistController,id);
      numAlbunsIndividual = getArtistAlbunsIndividuaisControl(artistController,id);
      totalRecipe = getArtistProfitsControl(artistController,id);
      
      output1(output,artistName,artistType,artistCountry,&numAlbunsIndividual,&totalRecipe,c,1);

      free(artistName);
      free(artistType);
      free(artistCountry);

}




free(filename);
freeOutput(output);


}