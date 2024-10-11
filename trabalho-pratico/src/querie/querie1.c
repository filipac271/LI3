#include "../../include/controler/usersController.h"
#include "querie/querie1.h"
#include "../../include/controler/artistsController.h"

#include <stdio.h>
#include <stdlib.h>
#include <glib.h>




// Função para calcular a idade
int calcular_idade(const char* data_nascimento_str) {
    // Data atual
    int ano_atual = 2024, mes_atual = 9, dia_atual = 9;

    // Variáveis para armazenar ano, mês e dia de nascimento
    int ano_nascimento, mes_nascimento, dia_nascimento;

    // Converter a string da data de nascimento para inteiros
    sscanf(data_nascimento_str, "%d/%d/%d", &ano_nascimento, &mes_nascimento, &dia_nascimento);

    // Calcular a idade base
    int idade = ano_atual - ano_nascimento;

    // Ajustar se o mês atual for anterior ao mês de nascimento,
    // ou se for o mesmo mês, mas o dia atual for anterior ao dia de nascimento
    if (mes_atual < mes_nascimento || (mes_atual == mes_nascimento && dia_atual < dia_nascimento)) {
        idade--;
    }

    return idade;
}

void querie1(GHashTable* usersTable, char* id,int i){
char *filename = malloc(sizeof(char) * 256);
  sprintf(filename, "resultados/command%d_output.txt",i+1);
  FILE *output_file = fopen(filename, "w");

  free(filename);


 
User* utilizador = fetchUser(usersTable,id);
if (utilizador != NULL)
{

      int idade = calcular_idade( getUserBirthDate(utilizador));
      fprintf(output_file,"%s;%s;%s;%d;%s",getUserEmail(utilizador),  getUserNome(utilizador),  getUserApelido(utilizador), idade, getUserCountry(utilizador));

}

fclose(output_file);

}