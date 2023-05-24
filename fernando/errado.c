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
    int Fs;
    int Cs;

}dados_sequencia;

typedef struct 
{
    dados_sequencia* final[4];
    char string_de_retorno[1000000];
    FILE *pont_estagios;
    int estagios;

}processamento_frac;



char* gerar_sequenciasF(str_frac p, processamento_frac atual) {

  char string_auxiliar[1000000];
  
  if(atual.estagios == 4) {
    fprintf(atual.pont_estagios, "Estágio %d: ", atual.estagios + 1);
    fputs(atual.string_de_retorno, atual.pont_estagios);
    return "Fim";
  }
    
  else if (atual.estagios == 1) {
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
    int aux3 = atual.estagios + 1;
    fprintf(atual.pont_estagios, "Estágio %d: \n Quantidade de linhas/Fs: d\n Quantidade de caracteres d\n", aux3);
    fputs(string_auxiliar, atual.pont_estagios);
    fprintf(atual.pont_estagios, "\n");
    atual.estagios++;
    return gerar_sequenciasF(p, atual);
    
  } 
  else {
    for (long int cont = 0; cont <= strlen(atual.string_de_retorno); cont++) {
      if (atual.string_de_retorno[cont] == 'F') {
        for (long int cont2 = 0; cont2 <= strlen(p.Regra); cont2++) {
          string_auxiliar[strlen(string_auxiliar)] = p.Regra[cont2];
        }
      }
      else {
        string_auxiliar[strlen(string_auxiliar)] = atual.string_de_retorno[cont];
      }
    }
    
    if(atual.estagios < 4) {
    fprintf(atual.pont_estagios, " Estágio %d: \n Quantidade de linhas/Fs: d\n Quantidade de caracteres d\n", atual.estagios + 1);
    fputs(string_auxiliar, atual.pont_estagios);
    fprintf(atual.pont_estagios, "\n");
    }
  }
  atual.estagios++;
  return gerar_sequenciasF(p, atual);
}

void analise_estagio(char *estagio)
{

  int Quant_Fs, Quant_Sins;
  for(int i = 0; i < strlen(estagio); i++)
  {
    if(estagio[i] == 'F')
      Quant_Fs++;
    else
      Quant_Sins++;
  }
  
  
}

int main() {
  //declarações de variáveis
  str_frac inicial;
  processamento_frac processamento;
  
  processamento.estagios = 1;
  //onde serão escritas as strings de cada estagio
  //FILE *regras; //tirar na versão final, serve apenas pra teste


    printf("Insira o número do axioma desejado:\n ");
    scanf("%d", &inicial.Id);
    printf("Insira o axioma inial\n ");
    scanf("\n%[^\n]", inicial.Axioma);
    printf("Insira o angulo\n ");
    scanf("%d", &inicial.Ang);
    printf("Insira a regra de repetição\n ");
    scanf("\n%[^\n]", inicial.Regra);
    processamento.pont_estagios = fopen("estagios_fractal1.txt", "w");
    fprintf(processamento.pont_estagios, "Estágio 1: F+F+F+F\n");

    gerar_sequenciasF(inicial, processamento);

  return 0;
  
} 
