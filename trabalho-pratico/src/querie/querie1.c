
#include "controler/usersController.h"
#include "Output.h"
#include "utilidades.h"

#include <stdio.h>
#include <stdlib.h>
#include <glib.h>
#include <unistd.h> 



void querie1(UsersData* userController, char* line,int i){

char *filename = malloc(sizeof(char) * 256);
sprintf(filename, "resultados/command%d_output.txt",i+1);

char* idChar= line+3;
char c = line[1];

Output* output= iniciaOutput(filename);

int id = transformaIds(idChar);
User* utilizador = fetchUser(userController,id);
 


char* userBirthDate ;
char* userEmail;
char* userNome;
char* userApelido;
char* userCountry;

if (utilizador != NULL)
{ 
      userBirthDate = getUserBirthDate(utilizador);
      userEmail =getUserEmail(utilizador);
      userNome =getUserNome(utilizador);
      userApelido =getUserApelido(utilizador);
      userCountry =getUserCountry(utilizador);
   
      int idade = calcular_idade(userBirthDate);
   
      output1(output,userEmail,userNome,userApelido,idade, userCountry,c);
      free(userBirthDate);
      free(userEmail);
      free(userNome);
      free(userApelido);
      free(userCountry);

}
if(utilizador==NULL)
{
 outputNULL(output);
}



free(filename);
freeOutput(output);


}