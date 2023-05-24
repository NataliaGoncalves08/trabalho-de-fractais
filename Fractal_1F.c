#include <stdio.h>
#include <string.h>

typedef struct 
{
    int Id;
    char Axioma[7];
    int Ang;
    char Regra[15];

}str_frac;

char* gerar_sequenciasF(str_frac p, char *string_de_retorno, int estagio_atual, FILE *arquivo_strings) {

  char string_auxiliar[1000000];
  
  if(estagio_atual == 4) {
    fprintf(arquivo_strings, "Estágio %d: ", estagio_atual + 1);
    fputs(string_de_retorno, arquivo_strings);
    return string_de_retorno;
  }
    
  else if (estagio_atual == 1) {
    for (int cont = 0; cont < strlen(p.Axioma); cont++) {
      if (p.Axioma[cont] == 'F') {
        for (int cont2 = 0; cont2 < strlen(p.Regra); cont2++) {
          string_auxiliar[strlen(string_auxiliar)] = p.Regra[cont2];
        }
      }
      else {
        string_auxiliar[strlen(string_auxiliar)] = p.Axioma[cont];
      }
      
    }
    fprintf(arquivo_strings, "Estágio %d: ", estagio_atual + 1);
    fputs(string_auxiliar, arquivo_strings);
    fprintf(arquivo_strings, "\n");
    return gerar_sequenciasF(p, string_auxiliar, estagio_atual + 1, arquivo_strings);
    
  } 
  else {
    for (long int cont = 0; cont <= strlen(string_de_retorno); cont++) {
      if (string_de_retorno[cont] == 'F') {
        for (long int cont2 = 0; cont2 <= strlen(p.Regra); cont2++) {
          string_auxiliar[strlen(string_auxiliar)] = p.Regra[cont2];
        }
      }
      else {
        string_auxiliar[strlen(string_auxiliar)] = string_de_retorno[cont];
      }
    }
    
    if(estagio_atual < 4) {
    fprintf(arquivo_strings, "Estágio %d: ", estagio_atual + 1);
    fputs(string_auxiliar, arquivo_strings);
    fprintf(arquivo_strings, "\n");
    }
  }
  return gerar_sequenciasF(p, string_auxiliar, estagio_atual + 1, arquivo_strings);
}

void analise_estagio(char *estagio){
  
}

int main() {
  //declarações de variáveis
  str_frac inicial;
  int estagios = 0;
  char string_de_retorno[1000000];
  FILE *pont_estagios; //onde serão escritas as strings de cada estagio
  //FILE *regras; //tirar na versão final, serve apenas pra teste


    printf("Insira o número do axioma desejado:\n ");
    scanf("%d", &inicial.Id);
    printf("Insira o axioma inial\n ");
    scanf("\n%[^\n]", inicial.Axioma);
    printf("Insira o angulo\n ");
    scanf("%d", &inicial.Ang);
    printf("Insira a regra de repetição\n ");
    scanf("\n%[^\n]", inicial.Regra);
    pont_estagios = fopen("estagios_fractal1.txt", "w");
    fprintf(pont_estagios, "Estágio 1: F+F+F+F\n");

    gerar_sequenciasF(inicial, string_de_retorno, estagios + 1, pont_estagios);

  return 0;
  
} 
