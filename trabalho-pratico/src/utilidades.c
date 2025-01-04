#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <glib.h>
#include <unistd.h>
#include <ctype.h>

#include "utilidades.h"
#include "controler/musicsController.h"
#include "Entitys/history.h"



// Função para calcular a idade
int calcular_idade( char* data_nascimento_str) {
    // Data atual
    int ano_atual = 2024, mes_atual = 9, dia_atual = 9;

    // Variáveis para armazenar ano, mês e dia de nascimento
    int ano_nascimento, mes_nascimento, dia_nascimento;

    // Converter a string da data de nascimento para inteiros
    if(data_nascimento_str[0] == '\"'){
        sscanf(data_nascimento_str, "\"%d/%d/%d\"", &ano_nascimento, &mes_nascimento, &dia_nascimento);
    }else{
        sscanf(data_nascimento_str, "%d/%d/%d", &ano_nascimento, &mes_nascimento, &dia_nascimento);
    }

    // Calcular a idade base
    int idade = ano_atual - ano_nascimento;

    // Ajustar se o mês atual for anterior ao mês de nascimento,
    // ou se for o mesmo mês, mas o dia atual for anterior ao dia de nascimento
    if (mes_atual < mes_nascimento || (mes_atual == mes_nascimento && dia_atual < dia_nascimento)) {
        idade--;
    }
    return idade;
}

int duration_to_seconds(char* music_duration) {
    int hours, minutes, seconds;

    sscanf(music_duration, "%d:%d:%d", &hours, &minutes, &seconds);

    return hours * 3600 + minutes * 60 + seconds;
}




guint get_garray_length(GArray *array) {
    if (array == NULL) {
        return 0; // Retorna 0 se o GArray for NULL
    }
    return array->len; // Retorna o tamanho do GArray
}


char* seconds_to_hhmmss(int total_seconds) {
    // Aloca memória para a string de saída
    char time_string[16] ; // hh:mm:ss + \0 = 9 caracteres
    if (time_string == NULL) {
        return NULL; // Verifica se a alocação foi bem-sucedida
    }

    // Calcula horas, minutos e segundos
    int hours = total_seconds / 3600;
    int minutes = (total_seconds % 3600) / 60;
    int seconds = total_seconds % 60;

    // Formata a string no formato hh:mm:ss
    //mudar aqui tambem para 16 caso se queira tirar os warning
    snprintf(time_string, 16, "%02d:%02d:%02d", hours, minutes, seconds);

    return strdup(time_string);
}


// Função para remover aspas de uma string
char* remove_quotes(char* str) {
    size_t len = strlen(str);

    // Verifica se a string tem pelo menos 2 caracteres (as aspas)
    if (len < 2 || str[0] != '"' || str[len - 1] != '"') {
        // Se não tiver aspas, retorna uma cópia da string original
        return strdup(str);
    }

    // Aloca memória para a nova string (tamanho original - 2 para as aspas)
    char* new_str = (char*)malloc((len - 1) * sizeof(char));

    // Copia os caracteres da string original, excluindo as aspas
    strncpy(new_str, str + 1, len - 2);
    

    // Adiciona o terminador nulo ao final da nova string
    new_str[len - 2] = '\0';

    return new_str;
}


int calculate_num_members(char* grupo) {

    if (strcmp(grupo, "\"[]\"") == 0) {
        return 0; // Nenhum membro no grupo
    }

    int numMembros = 1; // Pelo menos um membro
    for (int i = 2; grupo[i] != '\0'; i++) { // Começa no índice 2 para pular as aspas iniciais e o parentesis
        if (grupo[i] == ',') {
            numMembros++;
        }
    }
    return numMembros;
}



int validaData(char *date) {
    int year, month, day;
    int offset = 0; // Offset para lidar com aspas

    // Verifica se a string está entre aspas
    if (date[0] == '"' && date[strlen(date) - 1] == '"') {
        offset = 1; // Ignorar as aspas inicial e final
    }

    // Calcula o tamanho esperado da string sem aspas
    size_t expectedLength = offset ? 12 : 10;

    // Verifica o tamanho esperado da string (aaaa/mm/dd = 10 caracteres ou "aaaa/mm/dd" = 12 caracteres)
    if (strlen(date) != expectedLength) {
        return 0;
    }

    // Verifica o formato: os caracteres nas posições corretas devem ser '/'
    if (date[4 + offset] != '/' || date[7 + offset] != '/') {
        return 0;
    }

    // Usa sscanf para extrair ano, mês e dia da string, ajustando pelo offset
    if (sscanf(date + offset, "%d/%d/%d", &year, &month, &day) != 3) {
        return 0;
    }

    // Verifica os valores de ano, mês e dia
    if (year < 0 || month < 1 || month > 12 || day < 1 || day > 31) {
        return 0;
    }

    // Verifica se a data é mais recente que 2024/09/09
    if (year > 2024 || (year == 2024 && month > 9) || (year == 2024 && month == 9 && day > 9)) {
        return 0;
    }

    return 1;
}



int validaEmail(char* emailAspas) {
    char* email = remove_quotes(emailAspas);
    int i = 0, j = 0, k = 0;

    // Verificar o username (antes do '@')
    for (i = 0; email[i] != '@'; i++) {
        if (!(islower(email[i]) || isdigit(email[i]))) {
            free(email);
            return 0;  // O username contém caracteres inválidos
        }
    }

    // Verificar se há pelo menos um caractere no username
    if (i == 0) {
        free(email);
        return 0;  // O username não pode ser vazio
    }

    i++;  // Saltar o '@'

    // Verificar o lstring (antes do '.')
    for (j = 0; email[i] != '.'; i++, j++) {
        if (!(islower(email[i]))) {
            free(email);
            return 0;  // lstring contém caracteres inválidos
        }
    }

    // Verificar se o lstring tem pelo menos 1 caractere
    if (j == 0) {
        free(email);
        return 0;  // lstring não pode ser vazio
    }

    i++;  // Saltar o '.'

    // Verificar o rstring (após o '.')
    for (k = 0; email[i] != '\0'; i++, k++) {
        if (!(islower(email[i]))) {
            free(email);
            return 0;  // rstring contém caracteres inválidos
        }
    }

    // Verificar se o rstring tem 2 ou 3 caracteres
    if (k != 2 && k != 3) {
        free(email);
        return 0;  // rstring deve ter 2 ou 3 caracteres
    }
    free(email);
    return 1;  // O e-mail é válido
}



int validaDuracao(char* duracao) {
    int hh, mm, ss;

    // Verificar se a string tem exatamente 10 caracteres ("hh:mm:ss")
    if (strlen(duracao) != 10) {
        return 0;  // Formato inválido
    }

    // Verificar se os separadores dentro das aspas são ':'
    if (duracao[3] != ':' || duracao[6] != ':') {
        return 0;  // Separadores inválidos
    }

    // Usar sscanf para extrair horas, minutos e segundos ignorando as aspas
    if (sscanf(duracao, "\"%2d:%2d:%2d\"", &hh, &mm, &ss) != 3) {
        return 0;  // Formato inválido
    }

    // Verificar se as horas estão entre 0 e 99
    if (hh < 0 || hh > 99) {
        return 0;  // Horas inválidas
    }

    // Verificar se os minutos estão entre 0 e 59
    if (mm < 0 || mm > 59) {
        return 0;  // Minutos inválidos
    }

    // Verificar se os segundos estão entre 0 e 59
    if (ss < 0 || ss > 59) {
        return 0;  // Segundos inválidos
    }

    return 1;  // Duração válida
}




int* divideGroup(char* group, int numMembros)
{
    // Verificar se a string é vazia ("[]")
    if (strcmp(group, "\"[]\"") == 0) {
        // Retornar um array vazio
        int* result_array = malloc(sizeof(int)); // Aloca espaço para um array vazio
        result_array[0] = -1;  // Indicador de array vazio
        return result_array;
    }

    // Avança o ponteiro para ignorar os primeiros caracteres: "['
    char* group_copy = &group[3];
    int* result_array = malloc(numMembros * sizeof(int));
    if (result_array == NULL) {
        fprintf(stderr, "Erro ao alocar memória para o array de inteiros\n");
        exit(1);
    }

    int i = 0;

    // Obter o primeiro elemento separado por aspas simples
    char* membro = strsep(&group_copy, "\'");

    // Dividir os itens do grupo
    while (membro != NULL && i < numMembros) {
        result_array[i++] = transformaIds(membro);  // Usa transformaIds para converter o token em inteiro
        membro = strsep(&group_copy, "\'");  // Avança para o próximo separador ignorando as virgulas e o primero separador
        membro = strsep(&group_copy, "\'");  // Captura o id ignorando o segundo separador
    }

    return result_array;
}



//Funçao para dar free das copias do likedSongs
void freeArray(int* array) {
    if (array == NULL) return; // Proteção contra ponteiros nulos

    free(array); // Libera o array de ponteiros
}



//Função divideArray que agora usa transformaIds
int* divideArray(char* inputArray, int numElementos) {
// Cria uma cópia da string original para evitar modificações na original
    char* inputCopy = strdup(inputArray);
    char* currentPosition = &inputCopy[3]; // Posição atual na string, ignorando os primeiros caracteres (ex: "[')

    // Aloca memória para armazenar os IDs inteiros
    int* idsArray = malloc(numElementos * sizeof(int));
    if (idsArray == NULL) {
        fprintf(stderr, "Erro ao alocar memória para idsArray\n");
        free(inputCopy);
        return NULL;
    }

    int i = 0;
    char* currentElement = strsep(&currentPosition, "\'");  // Extrai o primeiro elemento

    // Processa cada elemento, aplicando a transformação de string para ID
    while (currentElement != NULL && i < numElementos) {
        idsArray[i++] = transformaIds(currentElement);  // Converte para inteiro usando transformaIds
        currentElement = strsep(&currentPosition, "\'");         // Avança para o próximo separador ignorando as virgulas e o primero separador
        currentElement = strsep(&currentPosition, "\'");         // Captura o id ignorando o segundo separador
    }
    
    // Libera a memória temporária da copia
    free(inputCopy);

    return idsArray;

}



int compararFicheirosPorLinha(char *file1, char *file2, int *ocorrenciasCorretas) {
    FILE *f1 = fopen(file1, "r");
    FILE *f2 = fopen(file2, "r");

    if (f1 == NULL) {
        printf("Erro ao abrir o arquivo %s para comparação\n", file1);
        if (f2 != NULL) fclose(f2); // Fecha f2 se foi aberto
        return -1;  // Erro ao abrir f1
    }
    if (f2 == NULL) {
        printf("Erro ao abrir o arquivo %s para comparação\n", file2);
        fclose(f1);  // Fecha f1 se foi aberto
        return -1;  // Erro ao abrir f2
    }

    char linha1[1024], linha2[1024];
    int linhaNumero = 1;
    *ocorrenciasCorretas = 0;

    while (fgets(linha1, sizeof(linha1), f1) && fgets(linha2, sizeof(linha2), f2)) {
        // Remover quebra de linha para evitar diferenças acidentais
        linha1[strcspn(linha1, "\n")] = '\0';
        linha2[strcspn(linha2, "\n")] = '\0';

        if (strcmp(linha1, linha2) == 0) {            
            (*ocorrenciasCorretas)++;  // Incrementa ocorrências corretas
        } else {
            printf("\nDiferença encontrada na linha %d do arquivo %s\n", linhaNumero, file1);
            fclose(f1);
            fclose(f2);
            return 0;  // Arquivo é diferente
        }
        linhaNumero++;
    }

    fclose(f1);
    fclose(f2);
    return 1;  // Arquivos são iguais
}


//Funciona apenas se a string já vier sem aspas o que é o caso dos arrays mas não dos ids individuais
int transformaIds (char* idString){
    char* id;
    int idINT;

    //O primeiro if é para o caso de ser um id de um ALbum que tem duas letras
    if(idString[2] == 'L' && idString[0] == '\"'){
        id = strndup(&idString[3], strlen(idString) - 4); // Cria uma cópia sem modificar a original
    }
    else if (idString[0] == '\"') {
        id = strndup(&idString[2], strlen(idString) - 3); // Cria uma cópia sem modificar a original
    } else {
        //id = strndup(&idString[1], strlen(idString) - 1); // Cria uma cópia sem o primeiro caractere
        //A linha de codigo acima é o politicamente mais correto pq da maneira que está em baixo se chamarmos divideArray
        // multiplas vezes(2 ou 3(numero de zeros há esquerda +1)) no mesmo token os ids vão começar a sair errados
        //mas desta maneira é mais rápido pq n alocamos memoria tantas vezes o que nos poupa 0.5s
        //Caso se queria mudar para a versão que aloca memória tem que se eliminar o if que dá free no final da funçao e deixar só o free
        id = &idString[1];
    }

    idINT = atoi(id); // Converte a string para inteiro
    // printf("%d\n",idINT);
    // sleep(1);
    if (idString[0] == '\"')free(id); // Libera a memória da cópia

    return idINT;
}


//Função que poem toda a funçao em lowerCase
void toLowerCase(char *str) {
    while (*str) { // Itera sobre cada caractere da string
        *str = tolower((unsigned char)*str); // Converte o caractere para minúscula
        str++;
    }
}





//FUNCOES PARA O HISTORICO

// aaaa/mm/dd hh:mm:ss 
void pega_data(char* datetime, char* data) {
    memcpy(data, datetime, 10);
    data[10] = '\0'; // Adiciona o terminador nulo
}

int diasNoMes(int ano, int mes) {
    int a = ano;
    int m = mes;
    int dias[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (m == 2) {
        // Verificar se o ano é bissexto
        if ((a % 4 == 0 && a % 100 != 0) || (a % 400 == 0)) {
            return 29;
        }
    }
    return dias[m - 1];
}

    //algoritmo de Zeller ou variantes dele
int diaDaSemana(int ano, int mes, int dia) {
    int m = mes;
    int y = ano;
    int d = dia;

    if (m < 3) {
        m += 12;
        y -= 1;
    }

    // Formula para calcular o dia da semana.
    int formula = d + 2*m + (3*(m+1)/5) + y + y/4 - y/100 + y/400 + 2;  

    return formula % 7;
}

int diasParavoltar(int dia_da_semana) {
    switch (dia_da_semana) {
        case 0: return 6; // Sabado
        case 1: return 0; // DOmingo
        case 2: return 1; // Segunda
        case 3: return 2; // Terça
        case 4: return 3; // Quarta
        case 5: return 4; // Quinta
        case 6: return 5; // Sexta
        default: return -1; // default
    }
}



void calcularDomingoAnterior(const char *data, char *resultado) {
    int ano, mes, dia;
    sscanf(data, "%d/%d/%d", &ano, &mes, &dia);

    // Obter o dia da semana da data fornecida
    int diaSemana = diaDaSemana(ano, mes, dia);

    // Calcula quantos dias deve voltar para o domingo anterior
    int diasparavoltar = diasParavoltar(diaSemana);
    // Subtrair os dias para obter o domingo anterior
    dia -= diasparavoltar;
    if (dia < 1) {
        mes--;
        if (mes < 1) {
            mes = 12;
            ano--;
        }
        dia += diasNoMes(ano, mes);
    }

    sprintf(resultado, "%04d/%02d/%02d", ano, mes, dia);
    
}


void destransforma_IDs(int numero, char *resultado) {
    // Formata o número e armazena na string resultado
    sprintf(resultado, "A%07d", numero);
}



int pertence_ao_intervalo(char* data_inicial, char* data_final, char* data) {
    int ano_inicial, mes_inicial, dia_inicial;
    int ano_final, mes_final, dia_final;
    int ano, mes, dia;

    // Lê as datas inicial, final e a data fornecida
    sscanf(data_inicial, "%d/%d/%d", &ano_inicial, &mes_inicial, &dia_inicial);
    sscanf(data_final, "%d/%d/%d", &ano_final, &mes_final, &dia_final);
    sscanf(data, "%d/%d/%d", &ano, &mes, &dia);

    // Verifica se a data está fora do intervalo
    if (ano < ano_inicial || (ano == ano_inicial && (mes < mes_inicial || (mes == mes_inicial && dia < dia_inicial)))) {
        return 0; 
    }

    if (ano > ano_final || (ano == ano_final && (mes > mes_final || (mes == mes_final && dia > dia_final)))) {
        return 0; 
    }

    return 1; 
}



int verificaOrdemDatas(char *data1, char *data2) {
    int ano1, mes1, dia1;
    int ano2, mes2, dia2;

    // Parse das datas para seus componentes (ano, mês, dia)
    if (sscanf(data1, "%d/%d/%d", &ano1, &mes1, &dia1) != 3 ||
        sscanf(data2, "%d/%d/%d", &ano2, &mes2, &dia2) != 3) {
        return -1; // Retorna -1 se o formato das datas for inválido
    }

    // Comparação ano/mês/dia
    if (ano1 < ano2) return 1;
    if (ano1 > ano2) return 0;

    if (mes1 < mes2) return 1;
    if (mes1 > mes2) return 0;

    if (dia1 < dia2) return 1;
    return 0;
}

void* resize(void* array, int oldSize, char type)
{
    int newSize= 2* oldSize;
    if (type== 'i')
    {
        array=realloc(array, newSize * sizeof(int));
        
        // Verifica se a realocação foi bem-sucedida
        if (array == NULL) { 
            printf("Erro ao realocar memória.\n");
        }

    }
    else if(type=='c')
    {
        char* temp= realloc( array, newSize* sizeof(char));
         array =temp;

        // Verifica se a realocação foi bem-sucedida
        if (array == NULL) { 
            printf("Erro ao realocar memória.\n");
        }
    }
    else
    {
         printf("Tipo Inválido.\n");
    }
    

    return array;

}

