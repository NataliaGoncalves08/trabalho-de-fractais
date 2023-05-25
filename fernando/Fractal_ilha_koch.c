#include <stdio.h>
#include <string.h>

typedef struct 
{
  int Id;
  char Axioma[7];
  int Ang;
  char Regra[15];

}str_frac;

typedef struct 
{
  char string_de_retorno[1000000];
  FILE *pont_estagios;
  int estagios;

}processamento_frac;



char* gerar_sequenciasF(str_frac p, processamento_frac *atual) {

  char string_auxiliar[1000000];

  //caso base
  if(atual->estagios == 4) {
    for (long int cont = 0; cont <= strlen(atual->string_de_retorno); cont++) {
      if (atual->string_de_retorno[cont] == 'F') {
        for (long int cont2 = 0; cont2 <= strlen(p.Regra); cont2++) {
          string_auxiliar[strlen(string_auxiliar)] = p.Regra[cont2];
        }
      }
      else {
        string_auxiliar[strlen(string_auxiliar)] = atual->string_de_retorno[cont];
      }
    }
    fprintf(atual->pont_estagios, "Estágio %d: ", atual->estagios);
    fputs(string_auxiliar, atual->pont_estagios);
    return "Fim";
  }
  //primeira geração
   else if (atual->estagios == 1) {
     for (int cont = 0; cont < strlen(p.Axioma); cont++) {
        atual->string_de_retorno[strlen(atual->string_de_retorno)] = p.Axioma[cont];
      }
      fprintf(atual->pont_estagios, "Estágio %d: ", atual->estagios);
      fputs(atual->string_de_retorno, atual->pont_estagios);
      fprintf(atual->pont_estagios, "\n");
      atual->estagios++;
      return gerar_sequenciasF(p, atual);
      
  } 
  //geração de caracteres
  else {
    for (long int cont = 0; cont <= strlen(atual->string_de_retorno); cont++) {
      if (atual->string_de_retorno[cont] == 'F') {
        for (long int cont2 = 0; cont2 <= strlen(p.Regra); cont2++) {
          string_auxiliar[strlen(string_auxiliar)] = p.Regra[cont2];
        }
      }
      else {
        string_auxiliar[strlen(string_auxiliar)] = atual->string_de_retorno[cont];
      }
    }
    
    //copia de string_auxiliar para string_de_retorno
    for(long int cont = 0; cont < strlen(string_auxiliar); cont++) {
      atual->string_de_retorno[cont] = string_auxiliar[cont];
    }
    atual->string_de_retorno[strlen(atual->string_de_retorno)] = '\0';

    //gravação no arquivo
    fprintf(atual->pont_estagios, "Estágio %d: ", atual->estagios);
    fputs(atual->string_de_retorno, atual->pont_estagios);
    fprintf(atual->pont_estagios, "\n");
  }
  atual->estagios++;
  return gerar_sequenciasF(p, atual);
}


int main() {
  //declarações de variáveis
  str_frac inicial;
  processamento_frac processamento;
  
  processamento.estagios = 1;
  //onde serão escritas as strings de cada estagio
  //FILE *regras; //tirar na versão final, serve apenas pra teste

  //atribuição de valores
  printf("Insira o número do axioma desejado:\n ");
  scanf("%d", &inicial.Id);
  printf("Insira o axioma inial\n ");
  scanf("\n%[^\n]", inicial.Axioma);
  printf("Insira o angulo\n ");
  scanf("%d", &inicial.Ang);
  printf("Insira a regra de repetição\n ");
  scanf("\n%[^\n]", inicial.Regra);

  //abertura de arquivo
  processamento.pont_estagios = fopen("estagios_fractal1.txt", "w");

  //chamar função
  gerar_sequenciasF(inicial, &processamento);

  return 0;
  
} 
