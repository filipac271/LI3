#ifndef OUTPUT
#define OUTPUT

typedef struct output Output;

Output* iniciaOutput (char* filename);
void freeOutput(Output* output);
void outputNULL(Output* output3);
void outputErros(Output* erros,char* linha);

void output1(Output* output1, char* userEmail, char* userNome, char* userApelido,int idade, char* userCountry,char c);
void output2(Output* output2, char* nome, char* tipo, char* time,char* pais, char c);
void output3(Output* output3, char* genero, int num, char c);

#endif