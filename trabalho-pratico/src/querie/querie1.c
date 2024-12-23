
#include "controler/usersController.h"
#include "controler/artistsController.h"
#include "Entitys/artists.h"
#include "Entitys/users.h"
#include "Output.h"
#include "utilidades.h"

#include <stdio.h>
#include <stdlib.h>
#include <glib.h>
#include <unistd.h> 



void querie1(UsersData* userController, char* line,int i, ArtistsData* artistController){

char *filename = malloc(sizeof(char) * 256);
sprintf(filename, "resultados/command%d_output.txt",i+1);

char* idChar= line+3;
char c = line[1];

Output* output= iniciaOutput(filename);

int id = transformaIds(idChar);

User* utilizador = NULL;
Artist* artista = NULL;

if(c == 'S'){
      if(line[3] == 'U') utilizador = fetchUser(userController,id);
      if(line[3] == 'A') artista = lookup_artist(artistController,id);
}
else{
      if(line[2] == 'U') utilizador = fetchUser(userController,id);
      if(line[2] == 'A') artista = lookup_artist(artistController,id);  
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

if (utilizador != NULL)
{ 
      userBirthDate = getUserBirthDate(utilizador);
      userEmail =getUserEmail(utilizador);
      userNome =getUserNome(utilizador);
      userApelido =getUserApelido(utilizador);
      userCountry =getUserCountry(utilizador);
   
      int idade = calcular_idade(userBirthDate);
   
      output1(output,userEmail,userNome,userApelido,&idade, userCountry,c,0);
      free(userBirthDate);
      free(userEmail);
      free(userNome);
      free(userApelido);
      free(userCountry);

}else if (artista != NULL){

      artistName = getArtistName(artista);
      artistType =getArtistType(artista);
      artistCountry = getArtistCountry(artista);
      numAlbunsIndividual = getArtistAlbunsIndividuais(artista);
      totalRecipe = getArtistProfits(artista);
      
      output1(output,artistName,artistType,artistCountry,&numAlbunsIndividual,&totalRecipe,c,1);

      free(artistName);
      free(artistType);
      free(artistCountry);

}
if(utilizador==NULL && artista ==NULL)
{
 outputNULL(output);
}



free(filename);
freeOutput(output);


}